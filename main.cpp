// x86Project Alpha Blending
// 07.01.2018
// Bartlomiej Kulik

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "x86_function.h" 
			
int main(void)
{
	sf::Image image1;
	if (!image1.loadFromFile("image1.png"))
	{
		throw std::invalid_argument("Bad file name.");
	}
	sf::Image image2;
	if (!image2.loadFromFile("image2.png"))
	{
		throw std::invalid_argument("Bad file name.");
	}
	if (image1.getSize() != image2.getSize())
	{
		throw std::logic_error("Different sizes of pictures.");
	}

	const sf::Uint8* image1Ptr = image1.getPixelsPtr(); // read only Ptr
	const sf::Uint8* image2Ptr = image2.getPixelsPtr();

	unsigned int width = image1.getSize().x;
	unsigned int height = image1.getSize().y;

	sf::Uint8* resultImagePtr = new sf::Uint8[4 * width * height]; 
	// every pixel have 4 components - RGBA

	for (unsigned int i = 0; i < 4 * width * height; ++i)	// copying arrays of pixels
	{
		resultImagePtr[i] = image1Ptr[i];
	}

	// CALL x86_function
	std::cout << "RAX: " << x86_function(resultImagePtr, image2Ptr, 250, 250, width, height, 64);
	std::cout << std::endl;
	std::cout << std::endl;

	// print first pixels
	unsigned int pixels = 4;
	
	for (unsigned int i = 0; i < pixels; ++i)
	{
		for (unsigned int j = 0; j < 4; ++j)
		{
			std::cout << (int)resultImagePtr[i * 4 + j] << std::endl;
		}
		std::cout << std::endl;
	}

	// save result using resultImagePtr
	sf::Image resultImage;
	resultImage.create(width, height, resultImagePtr);
	if (!resultImage.saveToFile("result.png"))
    {
    	throw std::logic_error("Bad save to file.");
    }

	return 0;
}