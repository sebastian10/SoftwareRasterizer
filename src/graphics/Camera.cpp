
#include "../graphics/Camera.h"
#include <cmath>
#include <numbers>

namespace Rasterizer::Graphics
{
	Camera::Camera( Vec3 position, float fov, float aspectRatio, float nearPlane, float farPlane )
		:
		m_position( position )
	{
		m_fov = fov;
		m_aspectRatio = aspectRatio;
		m_nearPlane = nearPlane;
		m_farPlane = farPlane;

		m_target = Vec3( 0, 0, 0 );
		m_up = Vec3( 0, 1, 0 );

		ComputeProjectionMatrix();
	}

	void Camera::ComputeViewMatrix()
	{
		Vec3 forward = ( m_target - m_position ).Normalise();
		Vec3 right = forward.Cross( m_up ).Normalise();
		Vec3 up = -right.Cross( forward );

		Mat4 rotation = {
			right.x(), right.y(), right.z(), 0,
			up.x(),    up.y(),    up.z(),    0,
			-forward.x(), -forward.y(), -forward.z(), 0,
			0, 0, 0, 1
		};

		Mat4 translation = {
			1, 0, 0, -m_position.x(),
			0, 1, 0, -m_position.y(),
			0, 0, 1, -m_position.z(),
			0, 0, 0, 1
		};

		ViewMatrix = rotation * translation;
	}

	void Camera::ComputeProjectionMatrix() 
	{
		float tanHalfFov = (float)std::tan( m_fov * 0.5f * ( std::numbers::pi / 180 ) );

		ProjectionMatrix = {
			1.0f / ( m_aspectRatio * tanHalfFov ), 0, 0, 0,
			0, 1.0f / tanHalfFov, 0, 0,
			0, 0, -( m_farPlane + m_nearPlane ) / ( m_farPlane - m_nearPlane ), -2.0f * m_farPlane * m_nearPlane / ( m_farPlane - m_nearPlane ),
			0, 0, -1, 0
		};
	}

	Vec3 Camera::PerspectiveDivide( const Vec4& v ) const
	{
		return Vec3( v.x()/v.w(), v.y()/v.w(), v.z()/v.w() );
	}
}