#include "header.h"

Games::PressSpace::PressSpace(Play& newParent) : parent(newParent) {
    if (!bg.loadFromFile("images/space.png")) {
        printf("Failed to load space.png.");
    }
    bg.setRepeated(true);
}

Games::PressSpace::~PressSpace() {}

void Games::PressSpace::draw(sf::RenderWindow& window) {
    sf::Sprite background;
    background.setTexture(bg);
    int time = parent.getTime().asMilliseconds();
    int offX = Utils::mod(time / 10, 110);
    int offY = Utils::mod(time / 25, 55);
    background.setTextureRect(sf::IntRect(-110 + offX, -55 + offY, 800 + offX, 600 + offY));
    window.draw(background);
}

void Games::PressSpace::keypress(sf::Event::KeyEvent& key) {
    switch (key.code) {
        case sf::Keyboard::Key::Space:
            parent.win();
            break;
        default:
            parent.lose();
            break;
    }
}
