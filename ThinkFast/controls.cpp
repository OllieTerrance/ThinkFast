#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Controls::Controls(Manager& newManager) : manager(newManager) {}

Controls::~Controls() {}

void Controls::init() {
    for (int i = 0; i < MAXPLAYERS; i++) {
        pressed[i] = false;
    }
}

void Controls::draw(sf::RenderWindow& window) {
    // main Controls options
    sf::Text backPrompt;
    Utils::makeText(backPrompt, manager.getFont(), "Press Esc to go back.", 24, sf::Color::White, 0);
    backPrompt.setPosition(0, 200);
    Utils::centreText(backPrompt, true, false);
    window.draw(backPrompt);
    // joystick connection status
    for (int i = 0; i < MAXPLAYERS; i++) {
        sf::Text joy;
        std::ostringstream joyStr;
        joyStr << (i + 1);
        sf::Color colour = sf::Joystick::isConnected(i) ? (pressed[i] ? sf::Color::Red : sf::Color::Green) : sf::Color(64, 64, 64);
        Utils::makeText(joy, manager.getFont(), joyStr.str().c_str(), 48, colour, sf::Text::Bold);
        joy.setPosition(170 + (60 * i), 340);
        window.draw(joy);
    }
}

void Controls::keypress(sf::Event::KeyEvent& key, bool on) {
    if (!on) return;
    switch (key.code) {
        case sf::Keyboard::Key::Escape:
            manager.setCurrent(0);
            break;
        default:
            break;
    }
}

void Controls::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {
    pressed[button.joystickId] = on;
}
