#include "header.h"

Manager::Manager(sf::RenderWindow& newWindow) : window(newWindow) {
	screens[0] = new Menu(*this);
	screens[1] = new Game(*this);
}

Manager::~Manager() {
	for (int i = 0; i < 2; i++) {
		delete screens[i];
	}
}

sf::RenderWindow& Manager::getWindow() {
	return window;
}

void Manager::setCurrent(int pos) {
	current = pos;
}

Utils::Screen& Manager::getScreen() {
	return *screens[current];
}

Utils::Screen& Manager::getScreen(int pos) {
	return *screens[pos];
}
