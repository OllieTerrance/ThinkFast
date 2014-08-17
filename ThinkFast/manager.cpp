#include "header.h"

#include <sstream>

Manager::Manager(sf::RenderWindow& newWindow) : window(newWindow) {
    // create screens
    screens[SCR_MENU] = new Menu(*this);
    screens[SCR_CONTROLS] = new Controls(*this);
    screens[SCR_PLAY] = new Play(*this);
    current = SCR_MENU;
    // load external resources
    if (!font.loadFromFile("fonts/Cantarell.ttf")) throw ERR_ASSET;
    std::string soundNames[] = {"menu1", "menu2", "menu3", "beep", "buzz", "countdown", "win", "lose"};
    for (std::string name : soundNames) {
        std::ostringstream path;
        path << "sound/" << name << ".wav";
        if (!buffers[name].loadFromFile(path.str())) throw ERR_ASSET;
        sounds[name].setBuffer(buffers[name]);
    }
    // set joystick status
    for (int i = 0; i < sf::Joystick::Count; i++) joysticks[i] = sf::Joystick::isConnected(i);
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

bool* Manager::getJoysticks() {
    return joysticks;
}

Manager& Manager::setPlayers(bool* joysticks) {
    int ptr = 0;
    for (int i = 0; i < sf::Joystick::Count; i++) {
        if (joysticks[i]) {
            players[ptr] = i;
            ptr++;
        }
    }
    playerCount = ptr;
    for (int i = ptr; i < sf::Joystick::Count; i++) players[i] = -1;
    return *this;
}

Manager& Manager::setCurrent(int pos) {
    current = pos;
    screens[current]->init();
    return *this;
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

Manager& Manager::playSound(std::string name) {
    sounds[name].play();
    return *this;
}
