# pragma once
# include <Siv3D.hpp>
# include "GameObject.hpp"
# include "Constants.hpp"

class Player : public GameObject {
private:
    int _x, _y, _radius, _speed;
    Circle _body;
    int _shotInterval;
    void move() {
        if ( KeyUp.pressed() ) { _y -= _speed; }
        if ( KeyDown.pressed() ) { _y += _speed; }
        if ( KeyRight.pressed() ) { _x += _speed; }
        if ( KeyLeft.pressed() ) { _x -= _speed; }

        if ( _x > Constants::GameWidth ) { _x = Constants::GameWidth; }
        if ( _x < 0 ) { _x = 0; }
        if ( _y > Constants::GameHeight ) { _y = Constants::GameHeight; }
        if ( _y < 0 ) { _y = 0; }
    }
public:
    Player(int x = 400, int y = 500, int radius = 15, int speed = 2) {
        _x = x;
        _y = y;
        _radius = radius;
        _speed = speed;
        _shotInterval = 11;
    }
    GameObject* act() {
        this->move();
        if ( KeyZ.pressed() && (_shotInterval > 10)) {
            _shotInterval = 0;
            auto bullet = new Bullet( _x, _y - _radius, _radius/2 );
            return (GameObject*)bullet;
        }
        else {
            _shotInterval++;
            return NULL;
        }
    }
    void draw() {
        _body = Circle{ _x, _y, _radius};
        _body.draw();
    }
    int getPosX() { return _x; }
    int getPosY() { return _y; }
};
