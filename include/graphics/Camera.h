#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace Rasterizer::Graphics
{
	class Camera
	{
	public:
		Mat4 ViewMatrix;
		Mat4 ProjectionMatrix;
	private:
		// Position and orientation
		Vec3 m_position;
		Vec3 m_target;
		Vec3 m_up;

		// Projection parameters
		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
	public:
		Camera( Vec3 position, float fov = 45.0f, float aspectRatio = 1.0f, float nearPlane = 0.1f, float farPlane = 100.0f );
		void ComputeViewMatrix();
		void ComputeProjectionMatrix();
		Vec3 PerspectiveDivide( const Vec4& v ) const;
	private:
	};
}