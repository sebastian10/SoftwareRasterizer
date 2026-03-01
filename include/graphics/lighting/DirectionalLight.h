#pragma once

#include "Light.h"

namespace Rasterizer::Graphics::Lighting 
{
	class DirectionalLight : public ILight
	{
	public:
	private:
		Vec3 m_direction;
	public:
		DirectionalLight( const Vec3& direction, const Vec3& color, const float intensity )
			:
			ILight( color, intensity ),
			m_direction(direction)
		{
			m_direction.Normalise();
		}

		Vec3 GetLightDirection( const Vec3& point, const Mat3& viewMatrix ) const override
		{
			return -( viewMatrix * m_direction ).Normalise();
		}

		float GetAttenuation( const Vec3& point ) const override
		{
			return 1.0f;
		}
	private:
	};
}