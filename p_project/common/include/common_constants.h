//
// Created by couland-q on 21/11/22.
//

#ifndef P_PROJECT_COMMON_CONSTANTS_H
#define P_PROJECT_COMMON_CONSTANTS_H

#include <vector>
#include <SFML/Window.hpp>

std::vector<sf::Event::EventType> MOUSE_EVENTS =
        {sf::Event::MouseButtonPressed,
         sf::Event::MouseButtonReleased,
         sf::Event::MouseMoved,
         sf::Event::MouseWheelMoved};

std::vector<sf::Event::EventType> KEY_EVENTS =
        {sf::Event::KeyPressed};

std::vector<sf::Keyboard::Key> NUMPAD_KEYS =
        {sf::Keyboard::Numpad0};
#endif //P_PROJECT_COMMON_CONSTANTS_H
