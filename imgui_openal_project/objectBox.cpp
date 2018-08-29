#include "objectBox.h"

objectBox::objectBox()	
{
}

objectBox::~objectBox()
{
	as.~AudioSource();
}


AudioSource *objectBox::getAudioSource(){
	return &as;
}
