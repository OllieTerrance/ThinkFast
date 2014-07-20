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

void Menu::draw() {
    sf::Text title;
    Utils::makeText(title, manager.getFont(), "Think Fast", 48, sf::Color::Cyan, sf::Text::Bold);
    title.setPosition(0, 120);
    Utils::centreText(title, true, false);
    manager.getWindow().draw(title);
    sf::Text opt1;
    Utils::makeText(opt1, manager.getFont(), "Start", 28, (selIndex == 0 ? sf::Color::Cyan : sf::Color::White), 0);
    opt1.setPosition(0, 320);
    Utils::centreText(opt1, true, false);
    manager.getWindow().draw(opt1);
    sf::Text opt2;
    std::ostringstream playersStr;
    playersStr << "Players: " << players;
    Utils::makeText(opt2, manager.getFont(), playersStr.str().c_str(), 28, (selIndex == 1 ? sf::Color::Cyan : sf::Color::White), 0);
    opt2.setPosition(0, 370);
    Utils::centreText(opt2, true, false);
    manager.getWindow().draw(opt2);
    sf::Text opt3;
    Utils::makeText(opt3, manager.getFont(), "Exit", 28, (selIndex == 2 ? sf::Color::Cyan : sf::Color::White), 0);
    opt3.setPosition(0, 420);
    Utils::centreText(opt3, true, false);
    manager.getWindow().draw(opt3);
}

void Menu::keypress(sf::Event::KeyEvent& key) {
    switch (key.code) {
        case sf::Keyboard::Key::Left:
            if (selIndex == 1) {
                players = (players - 1) % 4;
                if (players == 0) players = 4;
            }
            break;
        case sf::Keyboard::Key::Right:
            if (selIndex == 1) {
                players = (players + 1) % 4;
                if (players == 0) players = 4;
            }
            break;
        case sf::Keyboard::Key::Up:
            selIndex = (selIndex - 1) % 3;
            break;
        case sf::Keyboard::Key::Down:
            selIndex = (selIndex + 1) % 3;
            break;
        case sf::Keyboard::Key::Return:
            switch (selIndex) {
                case 0:
                    manager.setCurrent(1);
                    break;
                case 2:
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
