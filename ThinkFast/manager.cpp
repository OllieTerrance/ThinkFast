#include "header.h"

#include <sstream>

Manager::Manager(sf::RenderWindow& newWindow) : window(newWindow) {
    // create screens
    screens[0] = new Menu(*this);
    screens[1] = new Controls(*this);
    screens[2] = new Play(*this);
    current = 0;
    // load external resources
    if (!font.loadFromFile("fonts/Cantarell.ttf")) throw ERR_ASSET;
    std::string soundNames[] = {"menu1", "menu2", "beep", "buzz", "countdown", "win", "lose"};
    for (std::string name : soundNames) {
        std::ostringstream path;
        path << "sound/" << name << ".wav";
        if (!buffers[name].loadFromFile(path.str())) throw ERR_ASSET;
        sounds[name].setBuffer(buffers[name]);
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
