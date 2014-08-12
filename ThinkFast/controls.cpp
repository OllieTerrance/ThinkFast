#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Controls::Controls(Manager& newManager) : manager(newManager) {
    if (!bg.loadFromFile("images/connect.png")) throw ERR_ASSET;
}

Controls::~Controls() {}

void Controls::init() {
    for (int i = 0; i < sf::Joystick::Count; i++) pressed[i] = false;
}

void Controls::draw(sf::RenderWindow& window) {
    sf::Sprite background;
    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 0, 800, 600));
    window.draw(background);
    sf::Text helpText;
    Utils::makeText(helpText, manager.getFont(), "Connect controllers, press a button to test.", 24, sf::Color(192, 192, 192), 0);
    helpText.setPosition(0, 100);
    Utils::centreText(helpText, true, false);
    window.draw(helpText);
    // joystick connection status
    bool* joysticks = manager.getJoysticks();
    for (int i = 0; i < sf::Joystick::Count; i++) {
        sf::Text joy;
        std::ostringstream joyStr;
        joyStr << (i + 1);
        sf::Color colour = joysticks[i] ? (pressed[i] ? sf::Color::Red : sf::Color::Green) : sf::Color(64, 64, 64);
        Utils::makeText(joy, manager.getFont(), joyStr.str(), 64, colour, sf::Text::Bold);
        joy.setPosition(100 + (80 * i), 260);
        window.draw(joy);
    }
    sf::Text backPrompt;
    Utils::makeText(backPrompt, manager.getFont(), "Press Escape to go back.", 24, sf::Color(192, 192, 192), 0);
    backPrompt.setPosition(0, 460);
    Utils::centreText(backPrompt, true, false);
    window.draw(backPrompt);
}

void Controls::keypress(sf::Event::KeyEvent& key, bool on) {
    if (!on) return;
    switch (key.code) {
        case sf::Keyboard::Key::Escape:
            manager.setCurrent(0);
            manager.playSound("menu1");
            break;
        default:
            break;
    }
}

void Controls::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {
    pressed[button.joystickId] = on;
}
