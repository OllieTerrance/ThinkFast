#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Play::Play(Manager& newManager) : manager(newManager) {
    if (!heart.loadFromFile("images/heart.png")) throw ERR_ASSET;
}

Play::~Play() {}

void Play::init() {
    for (int i = 0; i < manager.getPlayerCount(); i++) {
        lives[i] = 3;
        score[i] = 0;
    }
    counting = true;
    countdown = 5;
    game = new Games::ButtonStack(*this, manager);
    manager.playSound("countdown");
}

void Play::draw(sf::RenderWindow& window) {
    // countdown steps
    if (countdown == 5 || (countdown > 0 && clock.getElapsedTime().asMilliseconds() >= 500)) {
        countdown--;
        clock.restart();
        if (countdown > 0 && getActiveCount() > 0) manager.playSound("countdown");
    }
    // print countdown or show game over
    if (countdown > 0) {
        // show scores on left
        for (int i = 0; i < manager.getPlayerCount(); i++) {
            int top = 310 - (20 * manager.getPlayerCount()) + (40 * i);
            sf::Text playerText;
            std::ostringstream playerStr;
            playerStr << "Player " << (i + 1);
            Utils::makeText(playerText, manager.getFont(), playerStr.str(), 20, sf::Color::White, 0);
            playerText.setPosition(25, top + 5);
            window.draw(playerText);
            sf::Text scoreText;
            std::ostringstream scoreStr;
            scoreStr << score[i];
            Utils::makeText(scoreText, manager.getFont(), scoreStr.str(), 32, sf::Color::White, 0);
            scoreText.setPosition(112, top - 3);
            window.draw(scoreText);
            sf::Sprite hearts[3];
            if (lives[i] >= 1) {
                hearts[0].setTexture(heart);
                hearts[0].setPosition(140, top);
                window.draw(hearts[0]);
                if (lives[i] >= 2) {
                    hearts[1].setTexture(heart);
                    hearts[1].setPosition(155, top);
                    window.draw(hearts[1]);
                    if (lives[i] >= 3) {
                        hearts[2].setTexture(heart);
                        hearts[2].setPosition(170, top);
                        window.draw(hearts[2]);
                    }
                }
            }
        }
        if (lives[0] > 0) {
            sf::Text countText;
            std::ostringstream countStr;
            countStr << countdown;
            Utils::makeText(countText, manager.getFont(), countStr.str(), 40, sf::Color::Yellow, sf::Text::Bold);
            Utils::centreText(countText, true, true);
            window.draw(countText);
        } else {
            sf::Text gameOver;
            Utils::makeText(gameOver, manager.getFont(), "Game over!", 40, sf::Color::Red, sf::Text::Bold);
            Utils::centreText(gameOver, true, true);
            window.draw(gameOver);
        }
    // game over, return to menu
    } else if (getActiveCount() == 0) {
        manager.setCurrent(SCR_MENU);
    // game in progress
    } else if (clock.getElapsedTime().asMilliseconds() < 2000) {
        if (counting) {
            counting = false;
            for (int i = 0; i < manager.getPlayerCount(); i++) state[i] = Progress;
        }
        // draw game-specific features
        game->draw(window);
        int time = clock.getElapsedTime().asMilliseconds();
        if (time <= 750) {
            sf::Text infoText;
            sf::Text infoOutlines[4];
            Utils::makeText(infoText, infoOutlines, manager.getFont(), game->getPrompt(), 40, sf::Color::White, sf::Color::Black, sf::Text::Bold);
            Utils::centreText(infoText, true, true);
            Utils::moveOutlineText(infoText, infoOutlines, 8);
            for (int i = 0; i < 4; i++) {
                window.draw(infoOutlines[i]);
            }
            window.draw(infoText);
        }
        sf::RectangleShape progBar1(sf::Vector2f(800 * (1 - (time / 2000.0)), 20));
        sf::RectangleShape progBar2(sf::Vector2f(800 * (time / 2000.0), 20));
        progBar1.setPosition(0, 580);
        progBar2.setPosition(800 * (1 - (time / 2000.0)), 580);
        progBar1.setFillColor(sf::Color(96, 96, 96));
        progBar2.setFillColor(sf::Color(24, 24, 24));
        window.draw(progBar1);
        window.draw(progBar2);
    // game finished, reset for next game
    } else {
        for (int i = 0; i < manager.getPlayerCount(); i++) {
            if (state[i] == Win) score[i]++;
            else lives[i]--;
        }
        counting = true;
        countdown = 5;
        game = new Games::ButtonStack(*this, manager);
        draw(window);
    }
}

void Play::keypress(sf::Event::KeyEvent& event, bool on) {
    // return to menu
    if (event.code == sf::Keyboard::Key::Escape && on) manager.setCurrent(SCR_MENU);
    // pass remaining input to game
    else if (!counting) game->keypress(event, on);
}

void Play::joybutton(sf::Event::JoystickButtonEvent& event, bool on) {
    // pass input to game
    int player = manager.joyToPlayer(event.joystickId);
    if (!counting && state[player] == Progress) game->joybutton(event, on);
}

void Play::joyaxis(sf::Event::JoystickMoveEvent& event) {
    // pass input to game
    int player = manager.joyToPlayer(event.joystickId);
    if (!counting && state[player] == Progress) game->joyaxis(event);
}

int Play::getActiveCount() {
    int active = 0;
    for (int i = 0; i < manager.getPlayerCount(); i++) {
        if (lives[i] > 0) active++;
    }
    return active;
}

int Play::playerActive(int player) {
    int active = 0;
    for (int i = 0; i < manager.getPlayerCount(); i++) {
        if (lives[i] > 0) {
            if (i == player) return active;
            else active++;
        }
    }
    return -1;
}

sf::Time Play::getTime() {
    return clock.getElapsedTime();
}

Play::State Play::getState(int player) {
    return state[player];
}

void Play::win(int player) {
    if (!counting && state[player] == Progress) state[player] = Win;
}

void Play::lose(int player) {
    if (!counting && state[player] == Progress) state[player] = Lose;
}
