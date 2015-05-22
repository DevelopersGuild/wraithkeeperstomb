#ifndef __H_SOUND_SYSTEM
#define __H_SOUND_SYSTEM

#include <SFML\Audio.hpp>

class SoundSystem
{
private:
	sf::Sound sound_;
	sf::Music music_;

	sf::SoundBuffer buffer_;
public:
	SoundSystem();
	virtual ~SoundSystem();

	bool loadFile(std::string fname);
	void playSound();
	void stopSound();
};

#endif