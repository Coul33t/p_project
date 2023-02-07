//
// Created by couland-q on 07/02/23.
//

#ifndef P_PROJECT_TYPES_H
#define P_PROJECT_TYPES_H

#include <SDL.h>

template <typename T>
struct Point {
    T x, y;

    Point() {
        x = 0;
        y = 0;
    }

    Point(T x, T y): x(x), y(y) {}

    template <class Archive>
    void serialize(Archive & archive) {
        archive & x;
        archive & y;
    }
};

template <typename T>
struct Position {
    T x, y;

    Position() {
        x = 0;
        y = 0;
    }

    Position(T x, T y): x(x), y(y) {}

    template <class Archive>
    void serialize(Archive & archive) {
        archive & x;
        archive & y;
    }
};

template <typename T>
struct Size {
    T w, h;

    Size() {
        w = 0;
        h = 0;
    }

    Size(T w, T h): w(w), h(h) {}

    template <class Archive>
    void serialize(Archive & archive) {
        archive & w;
        archive & h;
    }
};


struct Rectangle {
    int x, y, w, h, x2, y2;
    SDL_Rect rect;

    Rectangle() = default;

    Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {
        x2 = x + w;
        y2 = y + h;
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
    }

    Rectangle(const Rectangle& other_rect) {
        x = other_rect.x;
        y = other_rect.y;
        w = other_rect.w;
        h = other_rect.h;
        x2 = other_rect.x2;
        y2 = other_rect.y2;
        rect.x = other_rect.rect.x;
        rect.y = other_rect.rect.y;
        rect.w = other_rect.rect.w;
        rect.h = other_rect.rect.h;
    }

    template <class Archive>
    void serialize(Archive & archive) {
        archive & x;
        archive & y;
        archive & w;
        archive & h;
        archive & x2;
        archive & y2;
    }
};

#endif //P_PROJECT_TYPES_H
