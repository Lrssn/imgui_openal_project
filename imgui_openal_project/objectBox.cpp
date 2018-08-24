#include "objectBox.h"

objectBox::objectBox()	
{
	this->audiosource = "./res/audio/clang.wav";
	this->audioname = this->audiosource;
	this->setit();
}

objectBox::objectBox(const char* _src, const char* _name)
{
	this->audiosource = _src;
	this->audioname = _name;
	this->setit();
}

objectBox::~objectBox()
{
	as.~AudioSource();
}

void objectBox::setit()
{
	as.setSource(audiosource);
	as.setName(audioname);
}

AudioSource objectBox::getAudioSource()
{
	return as;
}
