#include "header.h"

#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Play::Play(Manager& newManager) : manager(newManager) {}

Play::~Play() {}

void Play::init() {
    lives = 3;
    score = 0;
    countdown = 5;
    current = InProgress;
    game = new Games::PressSpace(*this);
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
            Utils::makeText(countText, manager.getFont(), countStr.str().c_str(), 32, sf::Color::Yellow, sf::Text::Bold);
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
        if (current == Win) window.clear(sf::Color::Green);
        if (current == Lose) window.clear(sf::Color::Red);
        int time = clock.getElapsedTime().asMilliseconds();
        if (time <= 750) {
            sf::Text instruction;
            Utils::makeText(instruction, manager.getFont(), "Press Space!", 40, sf::Color::White, sf::Text::Bold);
            Utils::centreText(instruction, true, true);
            window.draw(instruction);
        }
        sf::RectangleShape progressBar(sf::Vector2f(800 * (1 - (time / 2000.0)), 20));
        progressBar.setPosition(0, 580);
        progressBar.setFillColor(sf::Color(32, 32, 32));
        window.draw(progressBar);
        // draw game-specific features
        game->draw(window);
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
        current = InProgress;
        draw(window);
    }
    // always shown
    sf::Text livesText;
    std::ostringstream livesStr;
    livesStr << "Lives: " << lives;
    Utils::makeText(livesText, manager.getFont(), livesStr.str().c_str(), 20, sf::Color(128, 128, 128), 0);
    livesText.setPosition(15, 15);
    window.draw(livesText);
    sf::Text scoreText;
    std::ostringstream scoreStr;
    scoreStr << "Score: " << score;
    Utils::makeText(scoreText, manager.getFont(), scoreStr.str().c_str(), 20, sf::Color(128, 128, 128), 0);
    sf::FloatRect scoreBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(785 - scoreBounds.width, 15);
    window.draw(scoreText);
}

void Play::keypress(sf::Event::KeyEvent& key) {
    switch (key.code) {
        // return to menu
        case sf::Keyboard::Key::Escape:
            manager.setCurrent(0);
            break;
        // pass remaining input to game
        default:
            game->keypress(key);
            break;
    }
}

void Play::win() {
    if (current == InProgress) current = Win;
}

void Play::lose() {
    if (current == InProgress) current = Lose;
}
