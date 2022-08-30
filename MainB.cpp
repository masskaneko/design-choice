# include <Siv3D.hpp>
# include <list>

class GameObject {
private:
    String _type = U"general";
public:
    virtual void draw(){};
    virtual GameObject* act(){};
    virtual int getPosX(){};
    virtual int getPosY(){};
};

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

        if ( _x > 800 ) { _x = 800; }
        if ( _x < 0 ) { _x = 0; }
        if ( _y > 600 ) { _y = 600; }
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
        return NULL;
    }
    void draw() {
        _angle += 2;
        _body = Triangle{ _x, _y, _side }.rotated(_angle);
        _body.draw();
    }
    int getPosX() { return _x; }
    int getPosY() { return _y; }
};

class GameMain {
private:
    std::list<GameObject*> _gameObjects;
    GameObject* _player;
    Stopwatch _stopwatch;
    bool isInside(int x, int y) {
        if( (x < 0) || (x > 800) || (y < 0) || (y > 600) ) {
            return false;
        }
        return true;
    }
    void addEnemy() {
        if( _stopwatch.s() % 2 == 0 ) {
            GameObject* enemy = new Enemy(Random<int>(0, 800), 0);
            _gameObjects.push_back(enemy);
        }
    }
    void printStatus() {
        ClearPrint();
        Print << U"PlayerPos: " << _player->getPosX() << U"," << _player->getPosY();
        Print << U"objs: " << _gameObjects.size();
        Print << U"time: " << _stopwatch.s();
    }
public:
    GameMain() {
        _player = new Player();
        _gameObjects.push_back(_player);
        _stopwatch.start();
    }
    void runOneDelta() {
        printStatus();
        addEnemy();

        std::list<GameObject*> dyingObjects;

        for ( auto o : _gameObjects ) {
            GameObject* generatedObj = o->act();
            if ( generatedObj != NULL ) { _gameObjects.push_back(generatedObj); }
            o->draw();
            if ( !isInside(o->getPosX(), o->getPosY()) ) {
                dyingObjects.push_back(o);
            }
        }

        for ( auto o : dyingObjects ) {
            _gameObjects.remove(o);
            delete o;
        }
    }
};

void Main()
{
    GameMain gm;
    while (System::Update()) {
        gm.runOneDelta();
    }
}
