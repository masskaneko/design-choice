# pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"

class Bullet : public GameObject {
private:
    int _x, _y, _radius;
    Circle _body;
    void move() {
        _y -= 5;
    }
public:
    Bullet(int x, int y, int radius = 7) {
        _x = x;
        _y = y;
        _radius = radius;
    }
    GameObject* act() {
        this->move();
        return NULL;
    }
    void draw() {
        _body = Circle{ _x, _y, _radius};
        _body.draw();
    }
    int getPosX() { return _x; }
    int getPosY() { return _y; }
};
