#include "header.h"

#include <sstream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Menu::Menu(Manager& newManager) : manager(newManager) {
    selIndex = 0;
    if (!bg.loadFromFile("images/bg.png")) throw ERR_ASSET;
    bg.setRepeated(true);
}

Menu::~Menu() {}

void Menu::init() {
    clock.restart();
}

void Menu::draw(sf::RenderWindow& window) {
    int time = clock.getElapsedTime().asMilliseconds();
    int offX = MOD(-time / 25, 32);
    int offY = MOD(time / 40, 32);
    sf::Sprite background;
    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(offX - 32, offY - 32, 800 + offX, 600 + offY));
    window.draw(background);
    // joystick connection status
    int joysticks = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        sf::Text joy;
        std::ostringstream joyStr;
        joyStr << (i + 1);
        Utils::makeText(joy, manager.getFont(), joyStr.str(), 16, (sf::Joystick::isConnected(i) ? sf::Color::Green : sf::Color(96, 96, 96)), sf::Text::Bold);
        joy.setPosition(15 + (15 * i), 565);
        window.draw(joy);
        if (sf::Joystick::isConnected(i)) joysticks++;
    }
    // main menu options
    sf::Text title;
    Utils::makeText(title, manager.getFont(), "Think Fast", 48, sf::Color::Cyan, sf::Text::Bold);
    title.setPosition(0, 120);
    Utils::centreText(title, true, false);
    window.draw(title);
    sf::Text opt1;
    std::ostringstream startStr;
    startStr << "Start";
    if (joysticks > 0) startStr << ": " << joysticks << "P";
    sf::Color colour1 = (joysticks == 0 ? (selIndex == 0 ? sf::Color(0, 96, 96) : sf::Color(96, 96, 96)) : (selIndex == 0 ? sf::Color::Cyan : sf::Color::White));
    Utils::makeText(opt1, manager.getFont(), startStr.str(), 28, colour1, 0);
    opt1.setPosition(0, 320);
    Utils::centreText(opt1, true, false);
    window.draw(opt1);
    sf::Text opt2;
    Utils::makeText(opt2, manager.getFont(), "Controllers", 28, (selIndex == 1 ? sf::Color::Cyan : sf::Color::White), 0);
    opt2.setPosition(0, 370);
    Utils::centreText(opt2, true, false);
    window.draw(opt2);
    sf::Text opt3;
    Utils::makeText(opt3, manager.getFont(), "Exit", 28, (selIndex == 2 ? sf::Color::Cyan : sf::Color::White), 0);
    opt3.setPosition(0, 420);
    Utils::centreText(opt3, true, false);
    window.draw(opt3);
}

void Menu::keypress(sf::Event::KeyEvent& key, bool on) {
    if (!on) return;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    int joysticks = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (sf::Joystick::isConnected(i)) joysticks++;
    }
    switch (key.code) {
        case sf::Keyboard::Key::Up:
            selIndex = MOD(selIndex - 1, 3);
            manager.playSound("menu2");
            break;
        case sf::Keyboard::Key::Down:
            selIndex = MOD(selIndex + 1, 3);
            manager.playSound("menu2");
            break;
        case sf::Keyboard::Key::Return:
            switch (selIndex) {
                case 0:
                    if (joysticks > 0) manager.setCurrent(2);
                    break;
                case 1:
                    manager.setCurrent(1);
                    manager.playSound("menu1");
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

void Menu::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {}
