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
	public:
		Model( const std::string& filename );
		int VertexCount() const;
		int FaceCount() const;
		Vec3 GetVertex( const int index ) const;
		Vec3 GetVertex( const int faceIndex, const int vertexIndex ) const;
		Mat4 GetModelMatrix() const;
	private:
	};
}