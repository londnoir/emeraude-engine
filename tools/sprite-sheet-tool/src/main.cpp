/* STL inclusions. */
#include <cstdint>
#include <iostream>

/* Local inclusions. */
#include "Arguments.hpp"
#include "Libs/PixelFactory/Pixmap.hpp"
#include "Libs/PixelFactory/FileIO.hpp"
#include "Libs/PixelFactory/Processor.hpp"

using namespace Emeraude;
using namespace EmEn::Libs;

int
main (int argc, char * * argv)
{
	Arguments arguments{argc, argv};
	arguments.initialize();

	auto split = arguments.get("--split");
	auto size = arguments.get("--size");
	auto resize = arguments.get("--resize");
	auto filename = arguments.get("--output-name");

	if ( !split.isPresent() || !size.isPresent() )
	{
		std::cout << "Usage : SpriteSheetTool --split={filepath} --size={px} [--resize={px}] [--output-name={string}]" "\n";

		return EXIT_SUCCESS;
	}

	const std::filesystem::path sourceFilepath{split.value()};
	const auto spriteSize = static_cast< size_t >(stoi(size.value()));
	const auto spriteResize = resize.isPresent() ? static_cast< size_t >(stoi(resize.value())) : 0;
	const auto baseName = filename.isPresent() ? filename.value() : sourceFilepath.stem().string();

	std::cout <<
		"Input filepath to split : " << sourceFilepath << "\n"
		"Split size : " << spriteSize << " px" "\n"
		"Output directory : " << sourceFilepath.parent_path() << "\n";

	/* Read the input files. */
	PixelFactory::Pixmap< uint8_t > sourceImage;

	if ( !PixelFactory::FileIO::read(sourceFilepath, sourceImage) )
	{
		return EXIT_FAILURE;
	}

	const auto xFrame = static_cast< size_t >(sourceImage.width() / spriteSize);
	const auto yFrame = static_cast< size_t >(sourceImage.height() / spriteSize);

	auto frameNumber = 1;

	for ( size_t y = 0; y < yFrame; ++y )
	{
		for ( size_t x = 0; x < xFrame; ++x )
		{
			std::stringstream frameFilename;
			frameFilename << baseName << '_' << std::setfill('0') << std::setw(2) << frameNumber << sourceFilepath.extension().string();

			const PixelFactory::Area< size_t > area{
				x * spriteSize,
				y * spriteSize,
				spriteSize,
				spriteSize
			};

			/* Process the frame. */
			auto frameImage = PixelFactory::Processor< uint8_t >::crop(sourceImage, area);

			if ( spriteResize > 0 )
			{
				frameImage = PixelFactory::Processor< uint8_t >::resize(frameImage, spriteResize, spriteResize, PixelFactory::FilteringMode::Linear);
			}

			/* Saving the frame. */
			auto frameFilepath = sourceFilepath.parent_path();
			frameFilepath.append(frameFilename.str());

			if ( !PixelFactory::FileIO::write(frameImage, frameFilepath, true) )
			{
				return EXIT_FAILURE;
			}

			frameNumber++;
		}
	}

	return EXIT_SUCCESS;
}
