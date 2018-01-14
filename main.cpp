// x86Project Alpha Blending
// 14.01.2018
// Bartlomiej Kulik

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "x86_function.h" 
			
int main(void)
{
	// open images
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

	// copying arrays of pixels


	// main body

	

    // SFML


    sf::Texture textureImage1;
	textureImage1.loadFromImage(image1);
	sf::Sprite spriteImage1;
	spriteImage1.setTexture(textureImage1, true);

	sf::Image resultImage;
	sf::Texture textureResult;
	sf::Sprite spriteResult;
	
	sf::RenderWindow window(sf::VideoMode(width, height), "x86Project Alpha Blending");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{	
    			sf::Vector2i position = sf::Mouse::getPosition(window);
    			// do smth with position

    				for (unsigned int i = 0; i < 4 * width * height; ++i)	
	{
		resultImagePtr[i] = image1Ptr[i];
	}
    			
				    // CALL x86_function and make resultImage
					x86_function(resultImagePtr, image2Ptr, position.x, position.y, width, height, 10);
					// save result using resultImagePtr
					
					resultImage.create(width, height, resultImagePtr);
					if (!resultImage.saveToFile("result.png"))
				    {
				    	throw std::logic_error("Bad save to file.");
				    }
				    // END CALL x86_function and make resultImage

				    

				    
					textureResult.loadFromImage(resultImage);
					spriteResult.setTexture(textureResult, true);
					spriteImage1 = spriteResult;
	

			}

			window.clear();
        	window.draw(spriteImage1);
        	window.display();
        }

    }
    // SFML

	return 0;
}