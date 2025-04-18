/*
 * src/Testing/test_PixelFactoryProcessor.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include <gtest/gtest.h>

/* Local inclusions. */
#include "Libs/Time/Elapsed/PrintScopeRealTime.hpp"
#include "Libs/PixelFactory/FileIO.hpp"
#include "Libs/PixelFactory/Pixmap.hpp"
#include "Constants.hpp"

using namespace EmEn::Libs;
using namespace EmEn::Libs::PixelFactory;
using namespace EmEn::Libs::Time::Elapsed;

TEST(PixelFactoryProcessor, scale)
{
	Pixmap< uint8_t > baseImage;

	ASSERT_TRUE(FileIO::read(MediumRGBA, baseImage));
	ASSERT_EQ(baseImage.width(), 512);
	ASSERT_EQ(baseImage.height(), 512);
	ASSERT_EQ(baseImage.colorCount(), 4);

	{
		auto copyImage = baseImage;

		{
			PrintScopeRealTime stat{"Processor::scale(2.0F)"};

			Processor< uint8_t > processor{copyImage};

			ASSERT_TRUE(processor.scaleValue(2.0F));
		}

		ASSERT_TRUE(FileIO::write(copyImage, {RES_BASE_PATH "/test-assets/tmp_scaleAllValue.png"}, true));
	}

	{
		auto copyImage = baseImage;

		{
			PrintScopeRealTime stat{"Processor::scale(1.5F, Channel::Red)"};

			Processor< uint8_t > processor{copyImage};

			ASSERT_TRUE(processor.scaleValue(2.0F, Channel::Red));
		}

		ASSERT_TRUE(FileIO::write(copyImage, {RES_BASE_PATH "/test-assets/tmp_scaleRedValue.png"}, true));
	}
}

TEST(PixelFactoryProcessor, drawing)
{
	Pixmap< uint8_t > newImage{800, 600};

	ASSERT_EQ(newImage.width(), 800);
	ASSERT_EQ(newImage.height(), 600);
	ASSERT_EQ(newImage.colorCount(), 3);

	Processor< uint8_t > processor{newImage};

	{
		PrintScopeRealTime stat{"Processor::drawSegment({10, 16}, {85, 503}, LightBlue)"};

		ASSERT_TRUE(processor.drawSegment({10, 16}, {85, 503}, LightBlue));
	}

	{
		PrintScopeRealTime stat{"Processor::drawCircle({578, 250}, 58, DarkRed)"};

		ASSERT_TRUE(processor.drawCircle({578, 250}, 58, DarkRed));
	}

	{
		PrintScopeRealTime stat{"Processor::drawCircle({64, 128}, 800, Red)"};

		ASSERT_TRUE(processor.drawCircle({64, 128}, 500, Red));
	}

	{
		PrintScopeRealTime stat{"Processor::drawSquare({256, 502, 125, 98}, Green)"};

		ASSERT_TRUE(processor.drawSquare({256, 502, 125, 98}, Green));
	}

	{
		PrintScopeRealTime stat{"Processor::drawCross({64, 96, 256, 128}, Yellow)"};

		ASSERT_TRUE(processor.drawCross({64, 96, 256, 128}, Yellow));
	}

	{
		PrintScopeRealTime stat{"Processor::drawStraightCross({200, 350, 300, 350}, White)"};

		ASSERT_TRUE(processor.drawStraightCross({200, 350, 300, 350}, White));
	}

	ASSERT_TRUE(FileIO::write(newImage, {RES_BASE_PATH "/test-assets/tmp_drawing.png"}, true));
}

TEST(PixelFactoryProcessor, move)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::move(600, -200)"};

		Processor< uint8_t > processor{source};

		ASSERT_TRUE(processor.move(600, -400));
	}

	ASSERT_TRUE(FileIO::write(source, {RES_BASE_PATH "/test-assets/tmp_moved.png"}, true));
}

TEST(PixelFactoryProcessor, shift)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::shift(600, -400)"};

		Processor< uint8_t > processor{source};

		ASSERT_TRUE(processor.shift(600, -400));
	}

	ASSERT_TRUE(FileIO::write(source, {RES_BASE_PATH "/test-assets/tmp_shifted.png"}, true));
}

TEST(PixelFactoryProcessor, shiftTextArea)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::shiftTextArea(100)"};

		Processor< uint8_t > processor{source};

		ASSERT_TRUE(processor.shiftTextArea(-100));
	}

	ASSERT_TRUE(FileIO::write(source, {RES_BASE_PATH "/test-assets/tmp_textShifted.png"}, true));
}

TEST(PixelFactoryProcessor, resize)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::resize(640x480,Nearest)"};

		const auto output = Processor< uint8_t >::resize(source, 640, 480, FilteringMode::Nearest);

		ASSERT_EQ(output.width(), 640);
		ASSERT_EQ(output.height(), 480);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_640x480resizeNearest.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::resize(2560x2560,Linear)"};

		const auto output = Processor< uint8_t >::resize(source, 2560, 2560, FilteringMode::Linear);

		ASSERT_EQ(output.width(), 2560);
		ASSERT_EQ(output.height(), 2560);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_2560x2560resizeLinear.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::resize(2560x1600,Cubic)"};

		const auto output = Processor< uint8_t >::resize(source, 2560, 1600, FilteringMode::Cubic);

		ASSERT_EQ(output.width(), 2560);
		ASSERT_EQ(output.height(), 1600);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_2560x1600resizeCubic.png"}, true));
	}
}

TEST(PixelFactoryProcessor, crop)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::crop(800x600)"};

		const auto output = Processor< uint8_t >::crop(source, {64, 128, 800, 600});

		ASSERT_EQ(output.width(), 800);
		ASSERT_EQ(output.height(), 600);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_800x600cropped.png"}, true));
	}
}

TEST(PixelFactoryProcessor, extractChannel)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::extractChannel(red)"};

		const auto output = Processor< uint8_t >::extractChannel(source, Channel::Red);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 1);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_extractRedChannel.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::extractChannel(green)"};

		const auto output = Processor< uint8_t >::extractChannel(source, Channel::Green);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 1);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_extractGreenChannel.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::extractChannel(blue)"};

		const auto output = Processor< uint8_t >::extractChannel(source, Channel::Blue);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 1);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_extractBlueChannel.png"}, true));
	}
}

TEST(PixelFactoryProcessor, toGrayscale)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(MediumRGBA, source));

	{
		PrintScopeRealTime stat{"Processor::toGrayscale()"};

		const auto output = Processor< uint8_t >::toGrayscale(source);

		ASSERT_EQ(output.width(), 512);
		ASSERT_EQ(output.height(), 512);
		ASSERT_EQ(output.colorCount(), 1);
	}
}

TEST(PixelFactoryProcessor, toRGB)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(MediumRGBA, source));

	{
		PrintScopeRealTime stat{"Processor::toRGB()"};

		const auto output = Processor< uint8_t >::toRGB(source);

		ASSERT_EQ(output.width(), 512);
		ASSERT_EQ(output.height(), 512);
		ASSERT_EQ(output.colorCount(), 3);
	}
}

TEST(PixelFactoryProcessor, toRGBA)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::toRGBA()"};

		const auto output = Processor< uint8_t >::toRGBA(source, 0.5F);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 4);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_RGB2RGBA.png"}, true));
	}
}

TEST(PixelFactoryProcessor, mirror)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::mirror(x)"};

		const auto output = Processor< uint8_t >::mirror(source, MirrorMode::X);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_mirroredX.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::mirror(y)"};

		const auto output = Processor< uint8_t >::mirror(source, MirrorMode::Y);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_mirroredY.png"}, true));
	}

	{
		PrintScopeRealTime stat{"Processor::mirror(both)"};

		const auto output = Processor< uint8_t >::mirror(source, MirrorMode::Both);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_mirroredBoth.png"}, true));
	}
}

TEST(PixelFactoryProcessor, extend)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::extend()"};

		const auto output = Processor< uint8_t >::extend(source, {3, 2, 4, 9}, Red);

		ASSERT_EQ(output.width(), 1207);
		ASSERT_EQ(output.height(), 811);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_extended.png"}, true));
	}

}

TEST(PixelFactoryProcessor, rotateQuarterTurn)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	PrintScopeRealTime stat{"Processor::rotateQuarterTurn()"};

	const auto output = Processor< uint8_t >::rotateQuarterTurn(source);

	ASSERT_EQ(output.width(), 800);
	ASSERT_EQ(output.height(), 1200);
	ASSERT_EQ(output.colorCount(), 3);

	ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_rotated+90.png"}, true));
}

TEST(PixelFactoryProcessor, rotateHalfTurn)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	PrintScopeRealTime stat{"Processor::rotateHalfTurn()"};

	const auto output = Processor< uint8_t >::rotateHalfTurn(source);

	ASSERT_EQ(output.width(), 1200);
	ASSERT_EQ(output.height(), 800);
	ASSERT_EQ(output.colorCount(), 3);

	ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_rotated+180.png"}, true));
}

TEST(PixelFactoryProcessor, rotateThreeQuarterTurn)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	PrintScopeRealTime stat{"Processor::rotateThreeQuarterTurn()"};

	const auto output = Processor< uint8_t >::rotateThreeQuarterTurn(source);

	ASSERT_EQ(output.width(), 800);
	ASSERT_EQ(output.height(), 1200);
	ASSERT_EQ(output.colorCount(), 3);

	ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_rotated+270.png"}, true));
}

TEST(PixelFactoryProcessor, inverseColors)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::inverseColors()"};

		const auto output = Processor< uint8_t >::inverseColors(source);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_colorInversed.png"}, true));
	}
}

TEST(PixelFactoryProcessor, swapChannels)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	{
		PrintScopeRealTime stat{"Processor::swapChannels()"};

		const auto output = Processor< uint8_t >::swapChannels(source);

		ASSERT_EQ(output.width(), 1200);
		ASSERT_EQ(output.height(), 800);
		ASSERT_EQ(output.colorCount(), 3);

		ASSERT_TRUE(FileIO::write(output, {RES_BASE_PATH "/test-assets/tmp_colorSwapped.png"}, true));
	}
}

TEST(PixelFactoryProcessor, blit)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(MediumRGBA, source));
	ASSERT_EQ(source.width(), 512);
	ASSERT_EQ(source.height(), 512);
	ASSERT_EQ(source.colorCount(), 4);

	Pixmap< uint8_t > smallImage;

	ASSERT_TRUE(FileIO::read(SmallRGBA, smallImage));
	ASSERT_EQ(smallImage.width(), 64);
	ASSERT_EQ(smallImage.height(), 64);
	ASSERT_EQ(smallImage.colorCount(), 4);

	Processor< uint8_t > proc{source};

	Pixmap< uint8_t > blitImage;

	ASSERT_TRUE(proc.blit(smallImage, {64, 64}, {0, 0, 64, 64}));
	ASSERT_TRUE(proc.blit(smallImage, {64, 64}, {512-64, 512-64, 64, 64}));
	ASSERT_TRUE(proc.blit(smallImage, {64, 64}, {512-64, 0, 64, 64}));

	ASSERT_TRUE(FileIO::write(source, {RES_BASE_PATH "/test-assets/tmp_64x64-blit.png"}, true));
}

TEST(PixelFactoryProcessor, copy)
{
	Pixmap< uint8_t > source;

	ASSERT_TRUE(FileIO::read(LargeRGB, source));

	Processor< uint8_t > processor{source};

	{
		PrintScopeRealTime stat{"Processor::copy(pixmapSimple)"};

		Pixmap< uint8_t > chunk;

		ASSERT_TRUE(FileIO::read(MediumRGBA, chunk));

		ASSERT_TRUE(processor.copy(chunk, DrawPixelMode::Normal));
	}

	{
		PrintScopeRealTime stat{"Processor::copy(pixmapSimpleClip)"};

		Pixmap< uint8_t > chunk;

		ASSERT_TRUE(FileIO::read(SmallRGBA, chunk));

		ASSERT_TRUE(processor.copy(chunk, 600, 32, DrawPixelMode::Addition));
	}

	{
		PrintScopeRealTime stat{"Processor::copy(pixmap)"};

		Pixmap< uint8_t > chunk;

		ASSERT_TRUE(FileIO::read(MediumGrayscale, chunk));

		ASSERT_TRUE(processor.copy(chunk, {128, 128, 256, 256}, {400, 260, 256, 256}, DrawPixelMode::Multiply));
	}

	{
		PrintScopeRealTime stat{"Processor::copy(color)"};

		ASSERT_TRUE(processor.copy(Red, {640, 600, 200, 16}, DrawPixelMode::Overlay));
	}

	ASSERT_TRUE(FileIO::write(source, {RES_BASE_PATH "/test-assets/tmp_copy.png"}, true));
}

TEST(PixelFactoryProcessor, addAlphaChannel)
{
	Pixmap< uint8_t > source;
	Pixmap< uint8_t > destination;

	ASSERT_TRUE(FileIO::read(MediumRGB, source));

	ASSERT_EQ(source.width(), 512);
	ASSERT_EQ(source.height(), 512);
	ASSERT_EQ(source.colorCount(), 3);

	{
		PrintScopeRealTime stat{"Processor::addAlphaChannel()"};

		ASSERT_TRUE(Processor< uint8_t >::addAlphaChannel(source, destination));

		ASSERT_EQ(destination.width(), 512);
		ASSERT_EQ(destination.height(), 512);
		ASSERT_EQ(destination.colorCount(), 4);
	}

	ASSERT_TRUE(FileIO::write(destination, {RES_BASE_PATH "/test-assets/tmp_addAlphaChannel.png"}, true));
}

TEST(PixelFactoryProcessor, removeAlphaChannel)
{
	Pixmap< uint8_t > source;
	Pixmap< uint8_t > destination;

	ASSERT_TRUE(FileIO::read(MediumRGBA, source));

	ASSERT_EQ(source.width(), 512);
	ASSERT_EQ(source.height(), 512);
	ASSERT_EQ(source.colorCount(), 4);

	{
		PrintScopeRealTime stat{"Processor::removeAlphaChannel()"};

		ASSERT_TRUE(Processor< uint8_t >::removeAlphaChannel(source, destination));

		ASSERT_EQ(destination.width(), 512);
		ASSERT_EQ(destination.height(), 512);
		ASSERT_EQ(destination.colorCount(), 3);
	}

	ASSERT_TRUE(FileIO::write(destination, {RES_BASE_PATH "/test-assets/tmp_removeAlphaChannel.png"}, true));
}
