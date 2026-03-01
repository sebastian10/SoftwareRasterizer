#pragma once

#include "Vector.h"
#include "Color.h"
#include <array>

namespace Rasterizer::Graphics::Shapes
{
	struct Triangle
	{
		std::array<Vec4, 3> vertices;
		std::array<Vec4, 3> vertexNormals;
		Color colour;
		Vec4 faceNormal;

		Triangle( std::array<Vec4, 3> vertices, std::array<Vec4, 3> normals, Color colour, Vec4 faceNormal )
			:
			vertices( vertices ),
			vertexNormals( normals ),
			colour( colour ),
			faceNormal( faceNormal )
		{

		}
	};
}