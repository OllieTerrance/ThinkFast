#include "header.h"

Games::PressButton::PressButton(Play& newParent) : parent(newParent) {
    index = rand() % 3;
    if ((index == 0 && !bg.loadFromFile("images/PressButton/space.png"))
        || (index == 1 && !bg.loadFromFile("images/PressButton/enter.png"))
        || (index == 2 && !bg.loadFromFile("images/PressButton/up.png"))) throw -1;
    bg.setRepeated(true);
}

Games::PressButton::~PressButton() {}

void Games::PressButton::draw(sf::RenderWindow& window) {
    sf::Sprite background;
    background.setTexture(bg);
    int time = parent.getTime().asMilliseconds();
    int offX = Utils::mod(time / 10, widths[index]);
    int offY = Utils::mod(time / 25, heights[index]);
    background.setTextureRect(sf::IntRect(offX - widths[index], offY - heights[index], 800 + offX, 600 + offY));
    window.draw(background);
}

void Games::PressButton::keypress(sf::Event::KeyEvent& key) {
    Button selected = static_cast<Button>(index);
    if ((key.code == sf::Keyboard::Key::Space && selected == Space)
        || (key.code == sf::Keyboard::Key::Return && selected == Enter)
        || (key.code == sf::Keyboard::Key::Up && selected == Up)) parent.win();
    else parent.lose();
}

char* Games::PressButton::getPrompt() {
    return "Press the button!";
}
