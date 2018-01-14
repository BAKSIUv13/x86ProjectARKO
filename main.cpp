// x86Project Alpha Blending
// 14.01.2018
// Bartlomiej Kulik
//-----------------------------------------------------------------------------

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "PicturesToAlphaBlending.h"
#include "x86_function.h" 

int main(void)
{

	PicturesToAlphaBlending pictures("image4.png", "image3.png");

	unsigned int width = pictures.getWidth();
	unsigned int height = pictures.getHeight();
	
	sf::RenderWindow window(sf::VideoMode(width, height), 
		"x86Project Alpha Blending");

	unsigned int sineRatio = 10;
	bool inWindow = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseEntered)
            {
            	inWindow = true;
            }
            if (event.type == sf::Event::MouseLeft)
            {
            	inWindow = false;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && inWindow)
			{	
    			sf::Vector2i position = sf::Mouse::getPosition(window);

    				pictures.resetResultImagePtr();
				    			
				    // CALL x86_function and make resultImage
					x86_function(pictures.getResultImagePtr(), pictures.getImage2Ptr(), 
						position.x, position.y, width, height, sineRatio);
					// save result using resultImagePtr
					
					pictures.setResultImage();

				    // END CALL x86_function and make resultImage
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && inWindow)
			{	
 				   	sf::Vector2i position = sf::Mouse::getPosition(window);

    				//pictures.resetResultImagePtr();
				    			
				    // CALL x86_function and make resultImage
					x86_function(pictures.getResultImagePtr(), pictures.getImage2Ptr(), 
						position.x, position.y, width, height, sineRatio);
					// save result using resultImagePtr
					
					pictures.setResultImage();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (sineRatio >= 2)
				{
					sineRatio -= 1;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
					sineRatio += 1;
			}

			window.clear();
        	window.draw(pictures.getSpriteResult());
        	window.display();
        }

    }
    // SFML


	return 0;
}