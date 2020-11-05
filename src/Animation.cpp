#include "Animation.hpp"

Animation::Animation(unsigned int timeLaps) {
	Animation::timeLaps = timeLaps;
	clck.restart();
}

Animation::~Animation() {
	//dtor
}

void Animation::add(const sf::Texture texture) {
	frames.push_back(texture);
	return;
}

void Animation::draw(sf::RenderWindow &window) {
	if(frames.size() == 0 || status == Stopped)
		return;

	if(firstTime) {
		firstTime = false;
		sprite.setTexture(frames[0]);
		ptr = 1;
	}
	if(clck.getElapsedTime().asMilliseconds() > timeLaps) {
		clck.restart();
		sprite.setTexture(frames[ptr < frames.size() ? ptr++ : 0]);
		if(ptr >= frames.size())
			status = Stopped;
	}
	window.draw(sprite);
	return;
}

Animation::Status Animation::getStatus() {
	return status;
}

void Animation::stop() {
	status = Stopped;
}

void Animation::play() {
	ptr = 0;
	status = Playing;
}
