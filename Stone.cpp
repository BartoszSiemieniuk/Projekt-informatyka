#include "Stone.h"

const std::array<sf::Color,4> Stone::LUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};

Stone::Stone(sf::Vector2f pos, sf::Vector2f size, int L)
    : hp(L), broken(false)
{
    setPosition(pos);
    setSize(size);
    setOutlineThickness(2.f);
    setOutlineColor(sf::Color::Black);
    zmiana_kolor();
}

void Stone::setHP(int newHP)
{
    hp = newHP;
    if (hp <= 0)
    {
        hp = 0;
        broken = true;
    }
    else
    {
        broken = false;
    }
    zmiana_kolor();
}

void Stone::trafienie()
{
    if (broken) return;

    hp -= 1;
    if (hp <= 0)
    {
        hp = 0;
        broken = true;
    }
    zmiana_kolor();
}

void Stone::zmiana_kolor()
{
    int id = hp;
    if (id < 0) id = 0;
    if (id > 3) id = 3;
    setFillColor(LUT[id]);
}

bool Stone::isBroken() const
{
    return broken;
}

void Stone::draw(sf::RenderTarget &t) const
{
    if (!broken)
        t.draw((sf::RectangleShape)(*this));
}
