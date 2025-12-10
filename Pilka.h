#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Paletka.h"

class Pilka
{
private:
    float x, y;
    float vx, vy; 
    float r;
    sf::CircleShape shape;

public:
    Pilka(float x, float y, float vx, float vy, float r);

    void move(sf::Time dt);
    void odbicieX();
    void odbicieY();
    void colide_walls(float width, float height);

    bool collidePaddle(const Paletka &p);

   
    void setVelocity(float newVX, float newVY);
    void setPosition(float nx, float ny);
    void stop();
    void draw(sf::RenderTarget &t) const;

    float getX()      const { return x; }
    float getY()      const { return y; }
    float getRadius() const { return r; }
    float getVX()     const { return vx; }
    float getVY()     const { return vy; }
};
