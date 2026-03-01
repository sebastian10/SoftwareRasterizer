
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
		ComputeNormals();

		std::cout << "Total #vertices: " << VertexCount() << " #faces " << FaceCount() << std::endl;
		std::cout << "Total #vertex normals " << (int) m_vertexNormals.size() << " #face normals: " << (int)m_faceNormals.size() << std::endl;
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

	Vec3 Model::GetVertexNormal( const int index ) const
	{
		assert( index >= 0 );
		assert( index < m_vertexNormals.size() );
		return m_vertexNormals[index];
	}

	Vec3 Model::GetVertexNormal( const int faceIndex, const int vertexIndex ) const
	{
		assert( faceIndex >= 0 );
		assert( faceIndex < FaceCount() );
		assert( vertexIndex >= 0 );
		assert( vertexIndex < 3 );
		return m_vertexNormals[m_vertex_indices[faceIndex * 3 + vertexIndex]];
	}

	Vec3 Model::GetFaceNormal( const int index ) const
	{
		assert( index >= 0 );
		assert( index < m_faceNormals.size() );
		return m_faceNormals[index];
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

	void Model::ComputeNormals()
	{
		m_vertexNormals.resize( VertexCount(), Vec3( 0, 0, 0 ) );

		for ( int i = 0; i < FaceCount(); i++ )
		{
			Vec3 faceNormal = GetFaceNormal( { GetVertex( i, 0 ), GetVertex( i, 1 ), GetVertex( i, 2 ) } );
			m_faceNormals.emplace_back( faceNormal );

			int idx0 = m_vertex_indices[i * 3 + 0];
			int idx1 = m_vertex_indices[i * 3 + 1];
			int idx2 = m_vertex_indices[i * 3 + 2];
			ComputeVertexNormals( { idx0, idx1, idx2 }, faceNormal );
		}

		for ( Vec3& v : m_vertexNormals )
		{
			v.Normalise();
		}
	}

	Vec3 Model::GetFaceNormal( const std::array<Vec3, 3>& triangle ) const
	{
		Vec3 e1 = triangle[1] - triangle[0];
		Vec3 e2 = triangle[2] - triangle[0];

		return e1.Cross(e2);
	}

	void Model::ComputeVertexNormals( const std::array<int, 3>& indices, const Vec3& faceNormal )
	{
		for ( auto i : indices )
		{
			m_vertexNormals[i] += faceNormal;
		}
	}
}