#include "Paletka.h"

Paletka::Paletka(float x, float y, float szer, float wys, float v)
    : x(x), y(y), szer(szer), wys(wys), v(v)
{
    shape.setSize({szer, wys});
    shape.setOrigin(szer / 2.f, wys / 2.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Paletka::pal_prawo()
{
    x += v;
    shape.setPosition(x, y);
}

void Paletka::pal_lewo()
{
    x -= v;
    shape.setPosition(x, y);
}

void Paletka::ClampToBounds(float width)
{
    if (x - szer / 2.f < 0.f)
        x = szer / 2.f;
    if (x + szer / 2.f > width)
        x = width - szer / 2.f;

    shape.setPosition(x, y);
}

void Paletka::setPosition(float nx, float ny)
{
    x = nx;
    y = ny;
    shape.setPosition(x, y);
}

void Paletka::draw(sf::RenderTarget &target) const
{
    target.draw(shape);
}
