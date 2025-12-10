#include "Pilka.h"

Pilka::Pilka(float x, float y, float vx, float vy, float r)
    : x(x), y(y), vx(vx), vy(vy), r(r)
{
    shape.setRadius(r);
    shape.setOrigin(r, r);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::White);
}

void Pilka::move(sf::Time dt)
{
    float dtSec = dt.asSeconds();
    x += vx * dtSec;
    y += vy * dtSec;
    shape.setPosition(x, y);
}

void Pilka::odbicieX()
{
    vx = -vx;
}

void Pilka::odbicieY()
{
    vy = -vy;
}

void Pilka::colide_walls(float width, float height)
{
    if (x - r <= 0.f || x + r >= width)
        odbicieX();

    if (y - r <= 0.f)
        odbicieY();

}

bool Pilka::collidePaddle(const Paletka &p)
{
    float pal_X = p.getX();
    float pal_Y = p.getY();
    float pal_szer = p.getSzer();
    float pal_wys = p.getWys();

    float pal_L = pal_X - pal_szer / 2.f;
    float pal_R = pal_X + pal_szer / 2.f;
    float pal_Up = pal_Y - pal_wys / 2.f;

    bool zakres_pal = (x >= pal_L && x <= pal_R);
    bool odp_gora = (y + r >= pal_Up && y - r < pal_Up);

    if (zakres_pal && odp_gora)
    {
        vy = -std::abs(vy);
        y  = pal_Up - r;
        shape.setPosition(x, y);
        return true;
    }

    return false;
}



void Pilka::setVelocity(float newVX, float newVY)
{
    vx = newVX;
    vy = newVY;
}

void Pilka::setPosition(float nx, float ny)
{
    x = nx;
    y = ny;
    shape.setPosition(x, y);
}

void Pilka::stop()
{
    vx = 0.f;
    vy = 0.f;
}

void Pilka::draw(sf::RenderTarget &target) const
{
    target.draw(shape);
}
