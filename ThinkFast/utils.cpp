#include "header.h"

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

Utils::Screen::Screen() {}
Utils::Screen::~Screen() {}
void Utils::Screen::init() {}
void Utils::Screen::draw(sf::RenderWindow& window) {}
void Utils::Screen::keypress(sf::Event::KeyEvent& key, bool on) {}
void Utils::Screen::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {}
void Utils::Screen::joyaxis(sf::Event::JoystickMoveEvent& move) {}

Utils::Game::Game() {}
Utils::Game::~Game() {}
void Utils::Game::draw(sf::RenderWindow& window) {}
void Utils::Game::keypress(sf::Event::KeyEvent& key, bool on) {}
void Utils::Game::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {}
void Utils::Game::joyaxis(sf::Event::JoystickMoveEvent& move) {}
std::string Utils::Game::getPrompt() {
    return "";
}

// take a base Text element, set font/text/size/style
void Utils::makeText(sf::Text& base, sf::Font& font, std::string str, int size, sf::Color colour, int style) {
    base.setFont(font);
    base.setString(str);
    base.setCharacterSize(size);
    base.setColor(colour);
    base.setStyle(style);
}
// take a base Text element, set font/text/size/style, create outline with multiple offset copies
void Utils::makeText(sf::Text& base, sf::Text* outlines, sf::Font& font, std::string str, int size,
                     sf::Color colour, sf::Color outlineColour, int style) {
    Utils::makeText(base, font, str, size, colour, style);
    for (int i = 0; i < 4; i++) {
        Utils::makeText(outlines[i], font, str, size, outlineColour, style);
    }
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

// correctly position outlines to match base text
void Utils::moveOutlineText(sf::Text& base, sf::Text* outlines, int shift) {
    sf::FloatRect bounds = base.getGlobalBounds();
    for (int i = 0; i < 4; i++) {
        int offX = MOD(i, 2) == 0 ? 2 : -2;
        int offY = i < 2 ? 2 : -2;
        outlines[i].setPosition(bounds.left + offX, bounds.top - shift + offY);
    }
}
