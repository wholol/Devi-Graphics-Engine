#pragma once
#include <memory>
#include "../Dependencies/Siv/PerlinNoise.hpp"
#include "../src/FrameBuffer.h"

namespace Devi
{
	struct RGB
	{
		double r, g, b;
		explicit constexpr RGB() = default;
		explicit constexpr RGB(double rgb) noexcept
			: r{ rgb }, g{ rgb }, b{ rgb } {}
		constexpr RGB(double r, double g, double b) noexcept
			: r{ r }, g{ g }, b{ b } {}
	};

	struct BMPHeader
	{
		std::uint16_t bfType;
		std::uint32_t bfSize;
		std::uint16_t bfReserved1;
		std::uint16_t bfReserved2;
		std::uint32_t bfOffBits;
		std::uint32_t biSize;
		std::int32_t  biWidth;
		std::int32_t  biHeight;
		std::uint16_t biPlanes;
		std::uint16_t biBitCount;
		std::uint32_t biCompression;
		std::uint32_t biSizeImage;
		std::int32_t  biXPelsPerMeter;
		std::int32_t  biYPelsPerMeter;
		std::uint32_t biClrUsed;
		std::uint32_t biClrImportant;
	};

	class PerlinNoise
	{
	public:

		PerlinNoise(int textureWidth, int textureHeight, double frequency = 8.0, int octave = 8, unsigned int seed = 123456u);

		void Generate(const std::string& filePath);

	private:
		int m_textureWidth;
		int m_textureHeight;
		double m_frequency;
		int m_octave;
		unsigned int m_seed;
		std::vector<RGB> m_data;
		bool SaveBMP(const std::string& filePath);

		static constexpr std::uint8_t ToUint8(double x) noexcept
		{
			return (x <= 0.0) ? 0 : (1.0 <= x) ? 255 : static_cast<std::uint8_t>(x * 255.0 + 0.5);
		}
	};

}