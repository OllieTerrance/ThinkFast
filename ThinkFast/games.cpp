#include "header.h"

#include <iostream>

const std::string Games::ButtonStack::buttons[4] = {"A", "B", "X", "Y"};
const sf::Color Games::ButtonStack::pendingColours[5] =
        {sf::Color(255, 96, 32), sf::Color(255, 80, 32), sf::Color(255, 64, 32), sf::Color(255, 48, 32), sf::Color(255, 32, 32)};
const sf::Color Games::ButtonStack::doneColours[5] =
        {sf::Color(96, 255, 32), sf::Color(80, 255, 32), sf::Color(64, 255, 32), sf::Color(48, 255, 32), sf::Color(32, 255, 32)};

Games::ButtonStack::ButtonStack(Play& newPlay, Manager& newManager) : play(newPlay), manager(newManager) {
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
        Utils::makeText(prompt, manager.getFont(), buttons[stack[i]], 36, sf::Color::White, sf::Text::Bold);
        prompt.setPosition(0, (120 * i) + 30);
        Utils::centreText(prompt, true, false);
        window.draw(prompt);
    }
    if (play.getCurrent() == Play::Lose) {
        sf::RectangleShape dark(sf::Vector2f(800, 600));
        dark.setPosition(0, 0);
        dark.setFillColor(sf::Color(0, 0, 0, 128));
        window.draw(dark);
    }
}

void Games::ButtonStack::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {
    if (!on || button.button >= 4) return;
    if (button.button == stack[pos]) {
        pos++;
        if (pos == 5) play.win();
        manager.playSound("beep");
    } else {
        play.lose();
        manager.playSound("buzz");
    }
}

std::string Games::ButtonStack::getPrompt() {
    return "Press in order!";
}
