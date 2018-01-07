#ifndef X86_FUNCTION_H_
#define X86_FUNCTION_H_

extern "C" 
int x86_function(sf::Uint8* pixelsToEditImage1, const sf::Uint8* pixelsImage2, 
	const int mouseX, const int mouseY, const unsigned int width, const unsigned int height, 
	const unsigned int sinusRatio);	
	// pixelsToEditImage1 is the result - not save
	// sinus ratio ~~ 50

#endif // X86_FUNCTION_H_