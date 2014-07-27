#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Play::Play(Manager& newManager) : manager(newManager) {
    if (!heart.loadFromFile("images/heart.png")) throw ERR_ASSET;
}

Play::~Play() {}

void Play::init() {
    lives = 3;
    score = 0;
    countdown = 5;
    current = Countdown;
    game = new Games::PressButton(*this);
}

void Play::draw(sf::RenderWindow& window) {
    // countdown steps
    if (countdown == 5 || (countdown > 0 && clock.getElapsedTime().asMilliseconds() >= 500)) {
        countdown--;
        clock.restart();
    }
    // print countdown or show game over
    if (countdown > 0) {
        if (lives > 0) {
            sf::Text countText;
            std::ostringstream countStr;
            countStr << countdown << "...";
            Utils::makeText(countText, manager.getFont(), countStr.str(), 32, sf::Color::Yellow, sf::Text::Bold);
            Utils::centreText(countText, true, true);
            window.draw(countText);
        } else {
            sf::Text gameOver;
            Utils::makeText(gameOver, manager.getFont(), "Game over!", 40, sf::Color::Red, sf::Text::Bold);
            Utils::centreText(gameOver, true, true);
            window.draw(gameOver);
        }
    // game over, return to menu
    } else if (lives == 0) {
        manager.setCurrent(0);
    // game in progress
    } else if (clock.getElapsedTime().asMilliseconds() < 2000) {
        if (current == Countdown) current = InProgress;
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
        sf::Color bar1(current == Win ? sf::Color::Green : (current == Lose ? sf::Color::Red : sf::Color(96, 96, 96)));
        sf::Color bar2(current == Win ? sf::Color(0, 64, 0) : (current == Lose ? sf::Color(64, 0, 0) : sf::Color(24, 24, 24)));
        progBar1.setFillColor(bar1);
        progBar2.setFillColor(bar2);
        window.draw(progBar1);
        window.draw(progBar2);
    // game finished
    } else if (clock.getElapsedTime().asMilliseconds() < 3000) {
        // if neither won nor lost, set to lose
        if (current == InProgress) current = Lose;
        window.clear(sf::Color::Black);
        sf::Text result;
        if (current == Win) Utils::makeText(result, manager.getFont(), "Win!", 48, sf::Color::Green, sf::Text::Bold);
        if (current == Lose) Utils::makeText(result, manager.getFont(), "Lose!", 48, sf::Color::Red, sf::Text::Bold);
        Utils::centreText(result, true, true);
        window.draw(result);
    // reset for next game
    } else {
        if (current == Win) score++;
        if (current == Lose) lives--;
        countdown = 5;
        current = Countdown;
        game = new Games::PressButton(*this);
        draw(window);
    }
    // always shown
    sf::Sprite hearts[3];
    if (lives >= 1) {
        hearts[0].setTexture(heart);
        hearts[0].setPosition(2, 2);
        window.draw(hearts[0]);
        if (lives >= 2) {
            hearts[1].setTexture(heart);
            hearts[1].setPosition(17, 2);
            window.draw(hearts[1]);
            if (lives >= 3) {
                hearts[2].setTexture(heart);
                hearts[2].setPosition(32, 2);
                window.draw(hearts[2]);
            }
        }
    }
    sf::Text scoreText;
    sf::Text scoreOutlines[4];
    std::ostringstream scoreStr;
    scoreStr << score;
    Utils::makeText(scoreText, scoreOutlines, manager.getFont(), scoreStr.str().c_str(), 28, sf::Color::White, sf::Color::Black, sf::Text::Bold);
    sf::FloatRect scoreBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(790 - scoreBounds.width, 5);
    Utils::moveOutlineText(scoreText, scoreOutlines, 6);
    for (int i = 0; i < 4; i++) {
        window.draw(scoreOutlines[i]);
    }
    window.draw(scoreText);
}

void Play::keypress(sf::Event::KeyEvent& key, bool on) {
    // return to menu
    if (key.code == sf::Keyboard::Key::Escape && on) manager.setCurrent(0);
    // pass remaining input to game
    else if (current == InProgress) game->keypress(key, on);
}

void Play::joybutton(sf::Event::JoystickButtonEvent& button, bool on) {
    // pass input to game
    if (current == InProgress) game->joybutton(button, on);
}

sf::Time Play::getTime() {
    return clock.getElapsedTime();
}

void Play::win() {
    if (current == InProgress) current = Win;
}

void Play::lose() {
    if (current == InProgress) current = Lose;
}
