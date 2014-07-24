#include "header.h"

Games::PressSpace::PressSpace(Play& newParent) : parent(newParent) {}

Games::PressSpace::~PressSpace() {}

void Games::PressSpace::draw(sf::RenderWindow& window) {}

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
