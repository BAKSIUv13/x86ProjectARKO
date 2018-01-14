// class PicturesToAlphaBlending
// 14.01.2018
// Bartlomiej Kulik

#ifndef PicturesToAlphaBlending_H_
#define PicturesToAlphaBlending_H_

#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

class PicturesToAlphaBlending
{
private:

 	typedef unsigned int uInt;

	sf::Image image1;
	sf::Image image2;
	sf::Image resultImage;

	uInt width;
	uInt height;
	uInt size;

	const sf::Uint8* image1Ptr;
	const sf::Uint8* image2Ptr;

	sf::Uint8* resultImagePtr;

	sf::Texture textureImage1;
	sf::Texture textureImage2;
	sf::Texture textureResult;

	sf::Sprite spriteImage1;
	sf::Sprite spriteImage2;
	sf::Sprite spriteResult;

	bool loadFromFiles(const std::string& fileNameP1 = "image1.png", 
					   const std::string& fileNameP2 = "image2.png")
	{
		if (this->image1.loadFromFile(fileNameP1) == false)
		{
			throw std::invalid_argument("Bad fileNameP1\n");
		}
		if (this->image2.loadFromFile(fileNameP2) == false)
		{
			throw std::invalid_argument("Bad fileNameP2\n");
		}

		if (this->image1.getSize() != this->image2.getSize())
		{
			throw std::logic_error("Different sizes of pictures\n");
		}

		return true;

	}

	void copyTable(sf::Uint8* resultImagePtr, const sf::Uint8* sourceImagePtr, 
					const uInt& size)
	{
		for (uInt i = 0; i < size; ++i)	
		{
			resultImagePtr[i] = sourceImagePtr[i];
		}
	}


public:

	PicturesToAlphaBlending(const std::string& fileNameP1 = "image1.png", 
							const std::string& fileNameP2 = "image2.png")
	{
		loadFromFiles(fileNameP1, fileNameP2);

		this->image1Ptr = image1.getPixelsPtr(); // read only Ptr
		this->image2Ptr = image2.getPixelsPtr();

		this->width = this->image1.getSize().x;
		this->height = this->image1.getSize().y;

		this->size = 4 * this->width * this->height;
		this->resultImagePtr = new sf::Uint8[this->size];
		copyTable(this->resultImagePtr, this->image1Ptr, this->size);

		this->textureImage1.loadFromImage(this->image1);
		this->textureImage2.loadFromImage(this->image2);

		this->spriteImage1.setTexture(textureImage1, true);
		this->spriteImage2.setTexture(textureImage2, true);

		this->spriteResult = this->spriteImage1;
	}

	virtual ~PicturesToAlphaBlending()
	{
		delete[] resultImagePtr;
	}

	void resetResultImagePtr()
	{
		copyTable(this->resultImagePtr, this->image1Ptr, this->size);
	}

	void setResultImage()
	{
		this->resultImage.create(this->width, this->height, 
									this->resultImagePtr);
		if (resultImage.saveToFile("result.png") == false)
	    {
	    	throw std::logic_error("Bad save to file.");
	    }

		this->textureResult.loadFromImage(this->resultImage);
		this->spriteResult.setTexture(this->textureResult, true);
	}

	sf::Uint8* getResultImagePtr() const
	{
		return this->resultImagePtr;
	}

	uInt getWidth() const
	{
		return this->width;
	}

	uInt getHeight() const
	{
		return this->height;
	}

	uInt getSize() const
	{
		return this->size;
	}

	const sf::Uint8* getImage1Ptr() const
	{
		return this->image1Ptr;
	}

	const sf::Uint8* getImage2Ptr() const
	{
		return this->image2Ptr;
	}

	sf::Sprite getSpriteResult() const
	{
		return this->spriteResult;
	}

	
};

#endif // PicturesToAlphaBlending_H_
