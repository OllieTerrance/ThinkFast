#include "header.h"

#include <iostream>

Games::PressButton::PressButton(Play& newParent) : parent(newParent) {
    index = rand() % 3;
    if ((index == 0 && !bg.loadFromFile("images/PressButton/space.png"))
        || (index == 1 && !bg.loadFromFile("images/PressButton/enter.png"))
        || (index == 2 && !bg.loadFromFile("images/PressButton/up.png"))) throw ERR_ASSET;
    bg.setRepeated(true);
}

Games::PressButton::~PressButton() {}

void Games::PressButton::draw(sf::RenderWindow& window) {
    sf::Sprite background;
    background.setTexture(bg);
    int time = parent.getTime().asMilliseconds();
    int offX = MOD(time / 10, widths[index]);
    int offY = MOD(time / 25, heights[index]);
    background.setTextureRect(sf::IntRect(offX - widths[index], offY - heights[index], 800 + offX, 600 + offY));
    window.draw(background);
}

void Games::PressButton::keypress(sf::Event::KeyEvent& key, bool on) {
    if (!on) return;
    Button selected = static_cast<Button>(index);
    if ((key.code == sf::Keyboard::Key::Space && selected == Space)
        || (key.code == sf::Keyboard::Key::Return && selected == Enter)
        || (key.code == sf::Keyboard::Key::Up && selected == Up)) parent.win();
    else parent.lose();
}

void Games::PressButton::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {}

std::string Games::PressButton::getPrompt() {
    return "Press the button!";
}
