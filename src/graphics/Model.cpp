
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "graphics/Model.h"

namespace Rasterizer::Graphics
{
	Model::Model( const std::string& filename )
		:
		Scale( 1.0f, 1.0f, 1.0f )
	{
		std::ifstream file;
		file.open( filename, std::ios_base::in );

		if ( !file )
		{
			std::cerr << "Unable open file - " << filename;
			return;
		}

		std::string line;
		char trash;

		while ( std::getline( file, line ) )
		{
			std::istringstream iss( line );

			if ( line.size() >= 2 && line[0] == 'v' && line[1] == ' ' )
			{
				float x, y, z;
				if ( !( iss >> trash >> x >> y >> z ) )
				{
					std::cerr << "[ERROR] Malformed vertex line: " << line << "\n";
					continue;
				}
				m_vertices.emplace_back( x, y, z );
			}
			else if ( line.size() >= 2 && line[0] == 'f' && line[1] == ' ' )
			{
				int f, t, n;
				iss >> trash;
				while ( iss >> f >> trash >> t >> trash >> n )
				{
					m_vertex_indices.emplace_back( --f );
				}

				if ( m_vertex_indices.size() % 3 != 0 )
				{
					std::cerr << "[ERROR] Non-triangle face detected\n";
				}
			}
		}

		CentreModel();

		std::cout << "Total #vertices: " << VertexCount() << " #faces " << FaceCount() << std::endl;
	}

	int Model::VertexCount() const
	{
		return (int) m_vertices.size();
	}

	int Model::FaceCount() const
	{
		return (int) m_vertex_indices.size() / 3;
	}

	Vec3 Model::GetVertex( const int index ) const
	{
		assert( index >= 0 );
		assert( index < m_vertices.size() );
		return m_vertices[index];
	}

	Vec3 Model::GetVertex( const int faceIndex, const int vertexIndex ) const
	{
		assert( faceIndex >= 0 );
		assert( faceIndex < FaceCount() );
		assert( vertexIndex >= 0 );
		assert( vertexIndex < 3 );
		return m_vertices[m_vertex_indices[faceIndex * 3 + vertexIndex]];
	}

	void Model::CentreModel()
	{
		Vec3 min = m_vertices[0];
		Vec3 max = m_vertices[0];

		for ( const auto& v : m_vertices )
		{
			min.x() = std::min( min.x(), v.x() );
			min.y() = std::min( min.y(), v.y() );
			min.z() = std::min( min.z(), v.z() );

			max.x() = std::max( max.x(), v.x() );
			max.y() = std::max( max.y(), v.y() );
			max.z() = std::max( max.z(), v.z() );
		}

		Vec3 center = ( min + max ) * 0.5f;

		for ( auto& v : m_vertices )
		{
			v -= center;
		}
	}

	Mat4 Model::GetModelMatrix() const
	{
		Mat4 T = Mat4::Translation( Position );
		Mat4 R = Mat4::Rotation( Rotation.z() ) * Mat4::Rotation( Rotation.y() ) * Mat4::Rotation( Rotation.x() );
		Mat4 S = Mat4::Scale( Scale );

		return T * R * S;
	}
}