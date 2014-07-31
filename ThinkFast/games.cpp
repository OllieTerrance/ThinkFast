#include "header.h"

#include <iostream>

const std::string Games::PressButton::images[3] = {"space", "enter", "up"};

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

const std::string Games::ButtonStack::buttons[4] = {"A", "B", "X", "Y"};
const sf::Color Games::ButtonStack::pendingColours[5] = {sf::Color(255, 96, 32), sf::Color(255, 80, 32), sf::Color(255, 64, 32), sf::Color(255, 48, 32), sf::Color(255, 32, 32)};
const sf::Color Games::ButtonStack::doneColours[5] = {sf::Color(96, 255, 32), sf::Color(80, 255, 32), sf::Color(64, 255, 32), sf::Color(48, 255, 32), sf::Color(32, 255, 32)};

Games::ButtonStack::ButtonStack(Play& newParent) : parent(newParent) {
    pos = 0;
    for (int i = 0; i < 5; i++) {
        stack[i] = rand() % 4;
    }
}

Games::ButtonStack::~ButtonStack() {}

void Games::ButtonStack::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 5; i++) {
        sf::RectangleShape stripe(sf::Vector2f(800, 120));
        stripe.setPosition(0, 120 * i);
        stripe.setFillColor(i >= pos ? pendingColours[i] : doneColours[i]);
        window.draw(stripe);
        sf::Text prompt;
        Utils::makeText(prompt, parent.getFont(), buttons[stack[i]], 36, sf::Color::White, sf::Text::Bold);
        prompt.setPosition(0, (120 * i) + 30);
        Utils::centreText(prompt, true, false);
        window.draw(prompt);
    }
    if (parent.getCurrent() == Play::Lose) {
        sf::RectangleShape dark(sf::Vector2f(800, 600));
        dark.setPosition(0, 0);
        dark.setFillColor(sf::Color(0, 0, 0, 128));
        window.draw(dark);
    }
}

void Games::ButtonStack::keypress(sf::Event::KeyEvent& key, bool on) {}

void Games::ButtonStack::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {
    if (!on || button.button >= 4) return;
    if (button.button == stack[pos]) {
        pos++;
        if (pos == 5) parent.win();
        parent.playSound("beep");
    } else {
        parent.lose();
        parent.playSound("buzz");
    }
}

std::string Games::ButtonStack::getPrompt() {
    return "Press in order!";
}
