#include "header.h"

#include <iostream>

const std::string Games::ButtonStack::buttons[4] = {"A", "B", "X", "Y"};
const sf::Color Games::ButtonStack::pendingColours[5] =
        {sf::Color(255, 96, 32), sf::Color(255, 80, 32), sf::Color(255, 64, 32), sf::Color(255, 48, 32), sf::Color(255, 32, 32)};
const sf::Color Games::ButtonStack::doneColours[5] =
        {sf::Color(96, 255, 32), sf::Color(80, 255, 32), sf::Color(64, 255, 32), sf::Color(48, 255, 32), sf::Color(32, 255, 32)};

Games::ButtonStack::ButtonStack(Play& newPlay, Manager& newManager) : play(newPlay), manager(newManager), pos{0} {
    for (int i = 0; i < 5; i++) {
        stack[i] = rand() % 4;
    }
}

Games::ButtonStack::~ButtonStack() {}

void Games::ButtonStack::draw(sf::RenderWindow& window) {
    for (int i = 0; i < manager.getPlayerCount(); i++) {
        for (int j = 0; j < 5; j++) {
            sf::RectangleShape stripe(sf::Vector2f(800 / manager.getPlayerCount(), 120));
            stripe.setPosition(i * (800 / manager.getPlayerCount()), 120 * j);
            stripe.setFillColor(j >= pos[i] ? pendingColours[j] : doneColours[j]);
            window.draw(stripe);
            sf::Text prompt;
            Utils::makeText(prompt, manager.getFont(), buttons[stack[j]], 36, sf::Color::White, sf::Text::Bold);
            prompt.setPosition(0, (120 * j) + 30);
            Utils::centreText(prompt, true, false);
            window.draw(prompt);
        }
        if (play.getCurrent(i) == Play::Lose) {
            sf::RectangleShape dark(sf::Vector2f(800 / manager.getPlayerCount(), 600));
            dark.setPosition(i * (800 / manager.getPlayerCount()), 0);
            dark.setFillColor(sf::Color(0, 0, 0, 128));
            window.draw(dark);
        }
    }
}

void Games::ButtonStack::joybutton(sf::Event::JoystickButtonEvent& event, bool on) {
    if (!on || event.button >= 4) return;
    int player = manager.joyToPlayer(event.joystickId);
    if (event.button == stack[pos[player]]) {
        pos[player]++;
        if (pos[player] == 5) play.win(player);
        manager.playSound("beep");
    } else {
        play.lose(player);
        manager.playSound("buzz");
    }
}

std::string Games::ButtonStack::getPrompt() {
    return "Press in order!";
}
