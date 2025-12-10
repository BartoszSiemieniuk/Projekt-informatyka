#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class Stone : public sf::RectangleShape
{
private:
    int  hp;
    bool broken;

    static const std::array<sf::Color, 4> LUT;

public:
    Stone(sf::Vector2f pos, sf::Vector2f size, int L);

    int  getHP() const { return hp; }
    void setHP(int newHP);

    void trafienie();
    void zmiana_kolor();
    bool isBroken() const;

    void draw(sf::RenderTarget &t) const;
};
