# pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"

class Enemy : public GameObject {
private:
    double _x, _y, _side = 20, _angle = 0;
    Triangle _body;
public:
    Enemy( double x = 400, double y = 0 ) {
        _x = x;
        _y = y;
        _body = Triangle{ _x, _y, _side };
    }
    GameObject* act() {
        _y += 3;
        _angle += 2;
        return NULL;
    }
    void draw() {
        _body = Triangle{ _x, _y, _side }.rotated(_angle);
        _body.draw();
    }
    int getPosX() { return _x; }
    int getPosY() { return _y; }
};
