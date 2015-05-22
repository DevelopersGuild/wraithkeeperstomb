#include "SoundSystem.h"


SoundSystem::SoundSystem()
{
}


SoundSystem::~SoundSystem()
{
}


bool SoundSystem::loadFile(std::string fname)
{
	if (!buffer_.loadFromFile(fname))
		return false;

	if (sound_.getBuffer() == NULL) sound_.setBuffer(buffer_);

	return true;
}


void SoundSystem::playSound()
{
	sound_.play();
}

void SoundSystem::stopSound()
{
	sound_.stop();
}