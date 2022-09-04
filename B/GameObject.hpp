# pragma once

class GameObject {
public:
    virtual void draw();
    virtual GameObject* act();
    virtual int getPosX();
    virtual int getPosY();
};
