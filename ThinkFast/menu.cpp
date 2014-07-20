#include "header.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void MainMenu::draw() {
    sf::Text title;
    Utils::makeText(title, "Think Fast", 48, sf::Color::Cyan, sf::Text::Bold);
    title.setPosition(0, 120);
    Utils::horizCentreText(title);
    window.draw(title);
    sf::Text opt1;
    Utils::makeText(opt1, "Start", 28, (selIndex == 0 ? sf::Color::Cyan : sf::Color::White), sf::Text::Bold);
    opt1.setPosition(0, 320);
    Utils::horizCentreText(opt1);
    window.draw(opt1);
    sf::Text opt2;
    std::ostringstream playersStr;
    playersStr << "Players: " << players;
    Utils::makeText(opt2, playersStr.str().c_str(), 28, (selIndex == 1 ? sf::Color::Cyan : sf::Color::White), sf::Text::Bold);
    opt2.setPosition(0, 370);
    Utils::horizCentreText(opt2);
    window.draw(opt2);
    sf::Text opt3;
    Utils::makeText(opt3, "Exit", 28, (selIndex == 2 ? sf::Color::Cyan : sf::Color::White), sf::Text::Bold);
    opt3.setPosition(0, 420);
    Utils::horizCentreText(opt3);
    window.draw(opt3);
}

void MainMenu::keypress(sf::Event::KeyEvent& key) {
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
                    // start...
                    break;
                case 2:
                    window.close();
                    break;
            }
            break;
        default:
            break;
    }
}
