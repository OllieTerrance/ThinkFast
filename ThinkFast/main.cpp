#include "header.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    // create the window and manager
    sf::RenderWindow window(sf::VideoMode(800, 600), "Think Fast", sf::Style::Titlebar | sf::Style::Close);
    Manager* manager;
    try {
        manager = new Manager(window);
    } catch (int err) {
        return err;
    }
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all events since last iteration
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    // quit on close
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                    // pass keypress to current screen
                    manager->getScreen().keypress(event.key, event.type == sf::Event::KeyPressed);
                    break;
                case sf::Event::JoystickButtonPressed:
                case sf::Event::JoystickButtonReleased:
                    // pass button press to current screen
                    manager->getScreen().joybutton(event.joystickButton, event.type == sf::Event::JoystickButtonPressed);
                    break;
                default:
                    break;
            }
        }
        // start all black
        window.clear(sf::Color::Black);
        // draw from screen
        manager->getScreen().draw(window);
        // end the current frame
        window.display();
    }
    return 0;
}
