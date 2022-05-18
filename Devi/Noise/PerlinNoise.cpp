#include "PerlinNoise.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace Devi
{
	PerlinNoise::PerlinNoise(int textureWidth, int textureHeight, double frequency, int octave, unsigned int seed)
		:m_textureWidth(textureWidth),
		m_textureHeight(textureHeight),
		m_frequency(frequency),
		m_octave(octave),
		m_seed(seed),
		m_data(m_textureHeight * m_textureWidth)
	{
	}

	void PerlinNoise::Generate(const std::string& filePath)
	{
		const siv::PerlinNoise::seed_type seed = m_seed;

		const siv::PerlinNoise perlin{ seed };

		const double fx = (m_frequency / m_textureWidth);
		const double fy = (m_frequency / m_textureHeight);

		for (int y = 0; y < m_textureHeight; ++y)
		{
			for (int x = 0; x < m_textureWidth; ++x)
			{
				RGB color(perlin.octave2D_01((x * fx), (y * fy), m_octave));

				m_data[x + m_textureWidth * y] = color;
			}
		}

		SaveBMP(filePath);
	}

	bool PerlinNoise::SaveBMP(const std::string& filePath)
	{
		const std::int32_t  rowSize = m_textureWidth * 3 + m_textureWidth % 4;
		const std::uint32_t bmpsize = rowSize * m_textureHeight;
		const BMPHeader header =
		{
			0x4d42,
			static_cast<std::uint32_t>(bmpsize + sizeof(BMPHeader)),
			0, 0, sizeof(BMPHeader), 40,
			m_textureWidth, m_textureHeight, 1, 24,
			0, bmpsize, 0, 0, 0, 0
		};

		if (std::ofstream ofs{ filePath, std::ios_base::binary })
		{
			ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));

			std::vector<std::uint8_t> line(rowSize);

			for (std::int32_t y = m_textureHeight - 1; -1 < y; --y)
			{
				size_t pos = 0;

				for (std::int32_t x = 0; x < m_textureWidth; ++x)
				{
					const RGB& col = m_data[static_cast<std::size_t>(y) * m_textureWidth + x];
					line[pos++] = ToUint8(col.b);
					line[pos++] = ToUint8(col.g);
					line[pos++] = ToUint8(col.r);
				}

				ofs.write(reinterpret_cast<const char*>(line.data()), line.size());
			}

			return true;
		}
		else
		{
			return false;
		}
	}
}

