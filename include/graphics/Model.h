#pragma once

#include <string>
#include <vector>
#include "../maths/Vector.h"
#include "Matrix.h"

namespace Rasterizer::Graphics
{
	class Model
	{
	public:
		Vec3 Position;
		Vec3 Rotation;
		Vec3 Scale;
	private:
		std::vector<Vec3> m_vertices = {};
		std::vector<int> m_vertex_indices = {};
		std::vector<Vec3> m_faceNormals = {};
		std::vector<Vec3> m_vertexNormals = {};
	public:
		Model( const std::string& filename );
		int VertexCount() const;
		int FaceCount() const;
		Vec3 GetVertex( const int index ) const;
		Vec3 GetVertex( const int faceIndex, const int vertexIndex ) const;
		Vec3 GetVertexNormal( const int index ) const;
		Vec3 GetVertexNormal( const int faceIndex, const int vertexIndex ) const;
		Vec3 GetFaceNormal( const int index ) const;
		Mat4 GetModelMatrix() const;
	private:
		void ComputeNormals();
		Vec3 GetFaceNormal( const std::array<Vec3, 3>& triangle ) const;
		void ComputeVertexNormals( const std::array<int, 3>& indices, const Vec3& faceNormal );
		void CentreModel();
	};
}