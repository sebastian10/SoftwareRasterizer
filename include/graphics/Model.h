#pragma once

#include <string>
#include <vector>
#include "../maths/Vector.h"

namespace Rasterizer::Graphics
{
	class Model
	{
	public:
	private:
		std::vector<Vec3> m_vertices = {};
		std::vector<int> m_vertex_indices = {};
	public:
		Model( const std::string& filename );
		int VertexCount() const;
		int FaceCount() const;
		Vec3 GetVertex( const int index ) const;
		Vec3 GetVertex( const int faceIndex, const int vertexIndex ) const;
	private:
	};
}