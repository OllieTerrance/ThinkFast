#include "header.h"

#include <SFML/Graphics.hpp>

Utils::Screen::Screen() {}

Utils::Screen::~Screen() {}

void Utils::Screen::init() {}
void Utils::Screen::draw() {}
void Utils::Screen::keypress(sf::Event::KeyEvent& key) {}

// take a base Text element, set font/text/size/style
void Utils::makeText(sf::Text& base, sf::Font& font, const char* str, int size, sf::Color colour, int style) {
    base.setFont(font);
    base.setString(str);
    base.setCharacterSize(size);
    base.setColor(colour);
    base.setStyle(style);
}

// take a base Text element, centre horizontally and/or vertically
void Utils::centreText(sf::Text& base, bool horiz, bool vert) {
    sf::FloatRect bounds = base.getGlobalBounds();
    if (horiz) base.setPosition(400 - (bounds.width / 2), bounds.top);
    if (vert) {
        if (horiz) bounds = base.getGlobalBounds();
        base.setPosition(bounds.left, 300 - (bounds.height / 2));
    }
}

// return a positive modulo
int Utils::mod(int a, int b) {
    return ((a % b) + b) % b;
}
