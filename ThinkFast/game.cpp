#include "header.h"

#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

Game::Game(Manager& newManager) : manager(newManager) {}

Game::~Game() {}

void Game::draw() {
    sf::Text loading;
    Utils::makeText(loading, "Loading...", 32, sf::Color::Yellow, sf::Text::Bold);
    Utils::centreText(loading, true, true);
    manager.getWindow().draw(loading);
}

void Game::keypress(sf::Event::KeyEvent& key) {
    switch (key.code) {
        case sf::Keyboard::Key::Escape:
            manager.setCurrent(0);
            break;
        default:
            break;
    }
}
