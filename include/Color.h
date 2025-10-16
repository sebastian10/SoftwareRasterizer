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
};