#include "header.h"

Manager::Manager(sf::RenderWindow& newWindow) : window(newWindow) {
	// create screens
	screens[0] = new Menu(*this);
	screens[1] = new Controls(*this);
	screens[2] = new Play(*this);
	current = 0;
	// load external resources
    if (!font.loadFromFile("fonts/Cantarell.ttf")) throw ERR_ASSET;
    if (!buffers["beep1"].loadFromFile("sound/beep1.wav")) throw ERR_ASSET;
    if (!buffers["beep2"].loadFromFile("sound/beep2.wav")) throw ERR_ASSET;
	for (std::map<std::string, sf::SoundBuffer>::iterator iter = buffers.begin(); iter != buffers.end(); iter++) {
		sounds[iter->first].setBuffer(iter->second);
	}
	// init current screen
	screens[current]->init();
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
	screens[current]->init();
}

Utils::Screen& Manager::getScreen() {
	return *screens[current];
}

Utils::Screen& Manager::getScreen(int pos) {
	return *screens[pos];
}

sf::Font& Manager::getFont() {
	return font;
}

void Manager::playSound(std::string name) {
	sounds[name].play();
}
