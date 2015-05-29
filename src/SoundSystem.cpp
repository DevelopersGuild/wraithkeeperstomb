#include "SoundSystem.h"


SoundSystem::SoundSystem()
{
}


SoundSystem::~SoundSystem()
{
	if (sound_.getStatus() == sf::SoundSource::Status::Playing || sound_.getStatus() == sf::SoundSource::Status::Paused)
		stopSound();

	sound_.resetBuffer();
}


bool SoundSystem::loadFile(std::string fname)
{
	if (sound_.getBuffer() == NULL) 
		sound_.setBuffer(buffer_);
	if (!buffer_.loadFromFile(fname))
		return false;

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