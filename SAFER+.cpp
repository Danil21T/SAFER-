#include <iostream>
#include "Shifr.h"

int main()
{
	const char* originImage = "large.png";
	const char* encriptionImage = "coding.png";
	const char* decriptionImage = "decoding.png";


	Shifr s(16, originImage);
	s.safer(encriptionImage);
	s.desafer(encriptionImage,decriptionImage);
	s.resultkey();
	
}