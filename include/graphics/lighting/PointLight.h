#pragma once

#include "Light.h"

namespace Rasterizer::Graphics::Lighting
{
	class PointLight : public ILight
	{
	public:
	private:
		Vec3 m_position;
	public:
		PointLight( const Vec3& position, const Vec3& color, const float intensity )
			:
			ILight( color, intensity ),
			m_position( position )
		{
			
		}

		Vec3 GetLightDirection( const Vec3& point, const Mat3& viewMatrix ) const override
		{
			Vec3 position = viewMatrix * m_position;
			return (position - point).Normalise();
		}

		float GetAttenuation( const Vec3& point ) const override
		{
			float distance = ( m_position - point ).GetLength();
			return 1.0f / ( distance * distance );
		}
	private:
	};
}