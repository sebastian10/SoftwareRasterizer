
#include "graphics/Renderer.h"
#include "graphics/shapes/Rectangle.h"
#include <assert.h>
#include <algorithm>
#include <numbers>

#include <random>

namespace Rasterizer::Graphics
{
	Renderer::Renderer( const HWND& hWnd )
		:
		m_framebuffer( hWnd ),
		m_depthbuffer( ScreenWidth, ScreenHeight ),
		m_camera( Vec3( 0,0,-3 ) )
	{
		m_camera.ComputeProjectionMatrix();
	}

	void Renderer::BeginFrame()
	{
		m_framebuffer.Flush();
		m_depthbuffer.Clear( 0 );

		m_camera.ComputeViewMatrix();	
	}

	void Renderer::EndFrame()
	{
		m_framebuffer.Display();
	}

	void Renderer::DrawLine( Vei2 start, Vei2 end, const Color colour )
	{
		bool steep = std::abs( start.x() - end.x() ) < std::abs( start.y() - end.y() );
		// transpose the image for steep lines
		if ( steep )
		{
			std::swap( start.x(), start.y() );
			std::swap( end.x(), end.y() );
		}

		// make it left-to-right
		if ( start.x() > end.x() )
		{
			std::swap( start, end );
		}

		int y = start.y();
		int ierror = 0;

		for ( int x = (int) start.x(); x <= end.x(); x++ )
		{
			// if transposed: de-transpose
			if ( steep )
			{
				m_framebuffer.PutPixel( y, x, colour );
			}
			else
			{
				m_framebuffer.PutPixel( x, y, colour );
			}

			ierror += 2 * std::abs( end.y() - start.y() );
			if ( ierror > ( end.x() - start.x() ) )
			{
				y += end.y() > start.y() ? 1 : -1;
				ierror -= 2 * ( end.x() - start.x() );
			}
		}
	}

	void Renderer::DrawTriangleWireframe( Vei2 a, Vei2 b, Vei2 c, const Color colour )
	{
		DrawLine( a, b, colour );
		DrawLine( b, c, colour );
		DrawLine( c, a, colour );
	}

	// Scanline rasterization
	void Renderer::DrawTriangleScanline( Vei2 a, Vei2 b, Vei2 c, const Color colour )
	{
		if ( a.y() > b.y() ) std::swap( a, b );
		if ( a.y() > c.y() ) std::swap( a, c );
		if ( b.y() > c.y() ) std::swap( b, c );

		assert( a.y() <= b.y() && b.y() <= c.y() );

		// Loop line by line
		for ( int y = a.y(); y <= c.y(); y++ )
		{
			int x_short;
			// Top half or bottom half
			if ( y < b.y() )
				x_short = Intersect( a, b, y );
			else
				x_short = Intersect( b, c, y );

			int x_long = Intersect( a, c, y );

			int x_start = min( x_short, x_long );
			int x_end = max( x_short, x_long );

			for ( int x = x_start; x <= x_end; x++ )
			{
				if ( x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight )
					continue;

				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}

	void Renderer::DrawTriangle( const Vei3& a, const Vei3& b, const Vei3& c, const Color colour )
	{
		int top = min( min( a.y(), b.y() ), c.y() );
		int bottom = max( max( a.y(), b.y() ), c.y() );
		int left = min( min( a.x(), b.x() ), c.x() );
		int right = max( max( a.x(), b.x() ), c.x() );

		top = max( 0, top );
		bottom = min( Renderer::ScreenHeight - 1, bottom );
		left = max( 0, left );
		right = min( Renderer::ScreenWidth - 1, right );

		auto Edge = []( const Vei3& a, const Vei3& b, const Vei3& p )
		{
			Vei3 a_int = Vei3( a );
			Vei3 b_int = Vei3( b );
			Vei3 p_int = Vei3( p );

			return ( b_int - a_int ).Cross( p_int - a_int ).z();
		};

		int area = Edge( a, b, c );
		if ( area >= 0 ) // positive area pointing backwards
			return;

		#pragma omp parallel for
		for ( int y = top; y < bottom; y++ )
		{
			for ( int x = left; x < right; x++ )
			{
				Vei3 p( x, y, 0 );
				float alpha = (float) Edge( a, b, p ) / area;
				float beta = (float) Edge( b, c, p ) / area;
				float gamma = (float) Edge( c, a, p ) / area;

				if ( alpha < 0 || beta < 0 || gamma < 0 )
					continue;
				
				unsigned char depth = static_cast<unsigned char>( alpha * a.z() + beta * b.z() + gamma * c.z() );

				if ( depth <= m_depthbuffer.Get( x, y ) )
					continue;

				m_depthbuffer.Set( x, y, depth );
				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}

	void Renderer::Rasterize( const std::array<Vec4, 3> clip, const Color colour)
	{
		Vec4 ndc[3] = {
			clip[0] / clip[0].w(),
			clip[1] / clip[1].w(),
			clip[2] / clip[2].w(),
		};

		Vec2 screen[3] = {
			( m_framebuffer.ViewportMatrix * ndc[0] ).xy(),
			( m_framebuffer.ViewportMatrix * ndc[1] ).xy(),
			( m_framebuffer.ViewportMatrix * ndc[2] ).xy(),
		};

		float top = min( min( screen[0].y(), screen[1].y()), screen[2].y());
		float bottom = max( max( screen[0].y(), screen[1].y() ), screen[2].y() );
		float left = min( min( screen[0].x(), screen[1].x() ), screen[2].x() );
		float right = max( max( screen[0].x(), screen[1].x() ), screen[2].x() );

		top = max( 0, top );
		bottom = min( Renderer::ScreenHeight - 1, bottom );
		left = max( 0, left );
		right = min( Renderer::ScreenWidth - 1, right );

		Mat3 ABC = {
			screen[0].x(), screen[1].x(), screen[2].x(),
			screen[0].y(), screen[1].y(), screen[2].y(),
			1.0f, 1.0f, 1.0f
		};

		// backface culling and removal of tiny triangles
		float determinant = ABC.Determinant();
		if ( std::abs( determinant ) < 1 )
			return;

		Mat3 ABCinv = ABC.Inversed( determinant );

		#pragma omp parallel for
		for ( int y = (int)top; y <= bottom; y++ )
		{
			for ( int x = (int)left; x <= right; x++ )
			{
				// barycentric coordinates of {x,y}
				Vec3 baryCoords = ABCinv * Vec3( static_cast<double>( x ), static_cast<double>( y ), 1.0f ); 
				if ( baryCoords.x() < 0 || baryCoords.y() < 0 || baryCoords.z() < 0 ) 
					continue;     

				double depth = baryCoords.Dot( Vec3( ndc[0].z(), ndc[1].z(), ndc[2].z() ) );

				if ( depth <= m_depthbuffer.Get( x, y ) )
					continue;

				m_depthbuffer.Set( x, y, depth );
				m_framebuffer.PutPixel( x, y, colour );
			}
		}
	}


	void Renderer::DrawWireframe( const Model& model, const Color colour )
	{
		for ( int i = 0; i < model.FaceCount(); i++ )
		{
			for ( int point = 0; point < 3; point++ )
			{
				Vei3 start( Project( model.GetVertex( i, point ) ) );
				Vei3 end = {};

				if ( point == 2 )
				{
					end = Vei3( Project( model.GetVertex( i, 0 ) ) );
				}
				else
				{
					end = Vei3( Project( model.GetVertex( i, point + 1 ) ) );
				}

				DrawLine( Vei2( start.x(), start.y()), Vei2(end.x(), end.y()), colour);
			}
		}

		for ( int i = 0; i < model.VertexCount(); i++ )
		{
			Vei3 vertex = Project( model.GetVertex( i ) );
			m_framebuffer.PutPixel( vertex.x(), vertex.y(), Colors::White);
		}
	}

	void Renderer::DrawModel( const Model& model, const Color colour )
	{
		std::mt19937 rng( std::random_device{}() );
		std::uniform_int_distribution<int> colorDist( 0, 255 );

		Mat4 modelMatrix = model.GetModelMatrix();
		Mat4 v = m_camera.ViewMatrix;
		Mat4 p = m_camera.ProjectionMatrix;
		Mat4 compositionMatrix = m_camera.ProjectionMatrix * m_camera.ViewMatrix * modelMatrix;
		
		for ( int i = 0; i < model.FaceCount(); i++ )
		{
			std::array<Vec4, 3> clip;

			for ( int j : { 0, 1, 2 } )
			{
				Vec3 vertex = model.GetVertex( i, j );
				clip[j] = compositionMatrix * Vec4( vertex.x(), vertex.y(), vertex.z(), 1.0f );
			}

			//Rasterize( clip, colour );
			auto clippedTriangles = ClipTriangleNearPlane( clip );

			for ( const auto& tri : clippedTriangles )
			{
				Rasterize( tri, Colors::MakeRGB( colorDist( rng ), colorDist( rng ), colorDist( rng ) ) );
			}

			//DrawTriangle( a, b, c, Colors::MakeRGB( colorDist( rng ), colorDist( rng ), colorDist( rng ) ) );
			//DrawTriangle( a, b, c, colour );
		}
	}

	Vei3 Renderer::Project( const Vec3& v ) const
	{
		// from [-1, 1], to [0, ScreenWidth/ScreenHeight)
		float scaleX = ( ScreenWidth - 1 ) * 0.5f;
		float scaleY = ( ScreenHeight - 1 ) * 0.5f;
		float scale = min( scaleX, scaleY );

		float offsetX = ScreenWidth * 0.5f;
		float offsetY = ScreenHeight * 0.5f;

		int x = (int) ( ( v.x() ) * scale + offsetX );
		int y = (int) ( ( v.y() ) * scale + offsetY );
		int z = (int) ( ( v.z() + 1.0f ) * 255 * 0.5f ); // mapped to [0,255]

		// std::cout << "Original: " << v.x << ", " << v.y << " Projection: " << x << ", " << y << std::endl;

		// ScreenHeight - y because of inverted y direction
		return Vei3( x, ScreenHeight - 1 - y, z );
	}

	Vec3 Renderer::Perspective( const Vec3& v ) const
	{
		constexpr float c = 10.0f;
		return v / ( 1 - v.z() / c );
	}

	Vec3 Renderer::Rotate( const Vec3& v, float theta ) const
	{
		Mat3 Ry = {
			std::cos( theta ), 0, std::sin( theta ),
			0, 1, 0,
			-std::sin( theta ), 0, std::cos(theta)
		};

		return Ry * v;
	}

	int Renderer::Intersect( Vei2 v0, Vei2 v1, int step ) const
	{
		float t = (float)( step - v0.y() ) / ( v1.y() - v0.y() ); // [0,1]
		float x = v0.x() + t * ( v1.x() - v0.x() );

		return (int)x;
	}

	void Renderer::VisualizeDepth()
	{
		for ( int y = 0; y < m_depthbuffer.GetHeigth(); y++ )
		{
			for ( int x = 0; x < m_depthbuffer.GetWidth(); x++ )
			{
				//m_framebuffer.PutPixel( x, y, Colors::Grayscale( m_depthbuffer.Get( x, y ) ) );
			}
		}
	}

	std::vector<std::array<Vec4, 3>> Renderer::ClipTriangleNearPlane( const std::array<Vec4, 3>& tri ) const
	{
		const Vec4& v0 = tri[0];
		const Vec4& v1 = tri[1];
		const Vec4& v2 = tri[2];

		auto inside = []( const Vec4& v ) { return v.z() <= v.w(); };
		//auto inside = []( const Vec4& v ) { return v.z() + v.w() >= 0.0; };

		bool in0 = inside( v0 );
		bool in1 = inside( v1 );
		bool in2 = inside( v2 );

		std::vector<std::array<Vec4, 3>> out;

		// all outside
		if ( !in0 && !in1 && !in2 ) return out;

		// all inside
		if ( in0 && in1 && in2 )
		{
			out.push_back( { v0,v1,v2 } );
			return out;
		}

		auto intersect = []( const Vec4& inside, const Vec4& outside )
		{
			float fIn = inside.z() + inside.w();
			float fOut = outside.z() + outside.w();
			float t = fIn / ( fIn - fOut );
			return inside + ( outside - inside ) * t;
		};

		// 1 inside, 2 outside
		if ( in0 && !in1 && !in2 ) out.push_back( { v0, intersect( v0,v1 ), intersect( v0,v2 ) } );
		else if ( in1 && !in0 && !in2 ) out.push_back( { v1, intersect( v1,v0 ), intersect( v1,v2 ) } );
		else if ( in2 && !in0 && !in1 ) out.push_back( { v2, intersect( v2,v0 ), intersect( v2,v1 ) } );
		// 2 inside, 1 outside
		else if ( !in0 && in1 && in2 )
		{
			out.push_back( { v1,v2,intersect( v1,v0 ) } );
			out.push_back( { v2, intersect( v1,v0 ), intersect( v2,v0 ) } );
		}
		else if ( in0 && !in1 && in2 )
		{
			out.push_back( { v0,v2,intersect( v0,v1 ) } );
			out.push_back( { v2, intersect( v0,v1 ), intersect( v2,v1 ) } );
		}
		else if ( in0 && in1 && !in2 )
		{
			out.push_back( { v0,v1,intersect( v0,v2 ) } );
			out.push_back( { v1, intersect( v0,v2 ), intersect( v1,v2 ) } );
		}
		return out;
	}
}