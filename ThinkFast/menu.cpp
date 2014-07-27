#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Menu::Menu(Manager& newManager) : manager(newManager) {}

Menu::~Menu() {}

void Menu::init() {
    selIndex = 0;
    players = 1;
}

void Menu::draw(sf::RenderWindow& window) {
    // main menu options
    sf::Text title;
    Utils::makeText(title, manager.getFont(), "Think Fast", 48, sf::Color::Cyan, sf::Text::Bold);
    title.setPosition(0, 100);
    Utils::centreText(title, true, false);
    window.draw(title);
    sf::Text opt1;
    Utils::makeText(opt1, manager.getFont(), "Start", 28, (selIndex == 0 ? sf::Color::Cyan : sf::Color::White), 0);
    opt1.setPosition(0, 300);
    Utils::centreText(opt1, true, false);
    window.draw(opt1);
    sf::Text opt2;
    std::ostringstream playersStr;
    playersStr << "Players: " << players;
    Utils::makeText(opt2, manager.getFont(), playersStr.str().c_str(), 28, (selIndex == 1 ? sf::Color::Cyan : sf::Color::White), 0);
    opt2.setPosition(0, 350);
    Utils::centreText(opt2, true, false);
    window.draw(opt2);
    sf::Text opt3;
    Utils::makeText(opt3, manager.getFont(), "Controllers", 28, (selIndex == 2 ? sf::Color::Cyan : sf::Color::White), 0);
    opt3.setPosition(0, 400);
    Utils::centreText(opt3, true, false);
    window.draw(opt3);
    sf::Text opt4;
    Utils::makeText(opt4, manager.getFont(), "Exit", 28, (selIndex == 3 ? sf::Color::Cyan : sf::Color::White), 0);
    opt4.setPosition(0, 450);
    Utils::centreText(opt4, true, false);
    window.draw(opt4);
    // joystick connection status
    for (int i = 0; i < MAXPLAYERS; i++) {
        sf::Text joy;
        std::ostringstream joyStr;
        joyStr << (i + 1);
        Utils::makeText(joy, manager.getFont(), joyStr.str().c_str(), 16, (sf::Joystick::isConnected(i) ? sf::Color::Green : sf::Color(64, 64, 64)), 0);
        joy.setPosition(15 + (20 * i), 565);
        window.draw(joy);
    }
}

void Menu::keypress(sf::Event::KeyEvent& key, bool on) {
    if (!on) return;
    switch (key.code) {
        case sf::Keyboard::Key::Left:
            if (selIndex == 1) {
                players = MOD(players - 1, MAXPLAYERS);
                if (players == 0) players = MAXPLAYERS;
            }
            break;
        case sf::Keyboard::Key::Right:
            if (selIndex == 1) {
                players = MOD(players + 1, MAXPLAYERS);
                if (players == 0) players = MAXPLAYERS;
            }
            break;
        case sf::Keyboard::Key::Up:
            selIndex = MOD(selIndex - 1, 4);
            break;
        case sf::Keyboard::Key::Down:
            selIndex = MOD(selIndex + 1, 4);
            break;
        case sf::Keyboard::Key::Return:
            switch (selIndex) {
                case 0:
                    manager.setCurrent(2);
                    break;
                case 2:
                    manager.setCurrent(1);
                    break;
                case 3:
                    manager.getWindow().close();
                    break;
            }
            break;
        case sf::Keyboard::Key::Escape:
            manager.getWindow().close();
            break;
        default:
            break;
    }
}

void Menu::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {}
