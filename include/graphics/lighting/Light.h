#pragma once

#include "Vector.h"
#include "Color.h"

namespace Rasterizer::Graphics::Lighting
{
	class ILight
	{
	public:
	private:
		Vec3 m_color;
		float m_intensity;
	public:
		ILight( const Vec3& color, const float intensity )
			:
			m_color( color ),
			m_intensity( intensity )
		{}
		virtual ~ILight() = default;
		virtual Vec3 GetLightDirection( const Vec3& point, const Mat3& viewMatrix ) const = 0;
		virtual float GetAttenuation( const Vec3& point ) const = 0;
		Vec3 GetColor() const
		{
			return m_color;
		}
		float GetIntensity() const
		{
			return m_intensity;
		}
	private:

	};
}