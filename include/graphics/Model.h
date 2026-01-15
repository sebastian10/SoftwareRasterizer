#pragma once

#include <string>
#include <vector>
#include "../maths/Vector3.h"

namespace Rasterizer::Graphics
{
	class Model
	{
	public:
	private:
		std::vector<Vector3> m_vertices;
		std::vector<int> m_face_verts;
	public:
		Model( const std::string& filename );
		int VertexCount() const;
		int FaceCount() const;
	private:
	};
}