#pragma once

class Color
{
public:
	unsigned int color;
public:
	constexpr Color() : color() {}
	constexpr Color( const Color& other )
		:
		color( other.color )
	{
	}
	constexpr Color( unsigned int other )
		:
		color( other )
	{
	}
	constexpr Color( const unsigned char r, const unsigned char g, const unsigned char b )
	{
		color = ( ( r << 16u ) | ( g << 8u ) | b );
	}
	constexpr Color( const unsigned char a, const unsigned char r, const unsigned char g, const unsigned char b )
	{
		color = ( ( a << 24u ) | ( r << 16u ) | ( g << 8u ) | b );
	}
	Color& operator=( Color other )
	{
		color = other.color;
		return *this;
	}
	constexpr unsigned char GetA() const
	{
		return color >> 24u;
	}
	constexpr unsigned char GetR() const
	{
		return ( color >> 16u ) & 0xFFu;
	}
	constexpr unsigned char GetG() const
	{
		return ( color >> 8u ) & 0xFFu;
	}
	constexpr unsigned char GetB() const
	{
		return color & 0xFFu;
	}
	void SetA( unsigned char a )
	{
		color = ( color & 0xFFFFFFu ) | ( a << 24u );
	}
	void SetR( unsigned char r )
	{
		color = ( color & 0xFF00FFFFu ) | ( r << 16u );
	}
	void SetG( unsigned char g )
	{
		color = ( color & 0xFFFF00FFu ) | ( g << 8u );
	}
	void SetB( unsigned char b )
	{
		color = ( color & 0xFFFFFF00u ) | b;
	}
};

namespace Colors
{
	static constexpr Color MakeRGB( unsigned char r, unsigned char g, unsigned char b )
	{
		return ( r << 16 ) | ( g << 8 ) | b;
	}
	static constexpr Color White = MakeRGB( 255u, 255u, 255u );
	static constexpr Color Black = MakeRGB( 0u, 0u, 0u );
	static constexpr Color Gray = MakeRGB( 0x80u, 0x80u, 0x80u );
	static constexpr Color LightGray = MakeRGB( 0xD3u, 0xD3u, 0xD3u );
	static constexpr Color Red = MakeRGB( 255u, 0u, 0u );
	static constexpr Color Green = MakeRGB( 0u, 255u, 0u );
	static constexpr Color Blue = MakeRGB( 0u, 0u, 255u );
	static constexpr Color Yellow = MakeRGB( 255u, 255u, 0u );
	static constexpr Color Cyan = MakeRGB( 0u, 255u, 255u );
	static constexpr Color Magenta = MakeRGB( 255u, 0u, 255u );
}