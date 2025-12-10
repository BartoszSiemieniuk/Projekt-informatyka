#pragma once
#include <SFML/Graphics.hpp>

class Paletka
{
private:
    float x, y;
    float szer, wys;
    float v;
    sf::RectangleShape shape;

public:
    Paletka(float x, float y, float szer, float wys, float v);
    
    void pal_prawo();
    void pal_lewo();
    void ClampToBounds(float width);

    void setPosition(float nx, float ny);

    void draw(sf::RenderTarget &target) const;

    float getX()   const { return x;    }
    float getY()   const { return y;    }
    float getSzer() const { return szer; }
    float getWys() const { return wys;  }
};
