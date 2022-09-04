# pragma once
# include <Siv3D.hpp>
# include <list>
# include "GameObject.hpp"
# include "Bullet.hpp"
# include "Player.hpp"
# include "Enemy.hpp"
# include "Constants.hpp"

class GameMain {
private:
    std::list<GameObject*> _gameObjects;
    GameObject* _player;
    Stopwatch _stopwatch;
    bool isInside(int x, int y) {
        if( (x < 0) || (x > Constants::GameWidth) || (y < 0) || (y > Constants::GameHeight) ) {
            return false;
        }
        return true;
    }
    void addEnemy() {
        if( _stopwatch.s() % 2 == 0 ) {
            GameObject* enemy = new Enemy(Random<int>(0, Constants::GameWidth), 0);
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
