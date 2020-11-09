#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Animation {
public:
    Animation(unsigned int timeLaps);
    ~Animation();

    enum Status {Stopped = 0, Playing};

    void add(const sf::Texture texture);

    void draw(sf::RenderWindow &window);
    Status getStatus();
    void stop();
    void play();

    sf::Sprite sprite;

private:

    std::vector<sf::Texture> frames;
    unsigned int ptr = 0;
    Status status = Stopped;

    sf::Clock clck;
    sf::Int32 interval = 0;
    bool firstTime = true;
};

#endif // ANIMATION_HPP
