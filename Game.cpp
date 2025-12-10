#include "Game.h"
#include "gamestate.h"
#include <cmath>

static float clampf(float v, float mn, float mx)
{
    return std::max(mn, std::min(mx, v));
}

Game::Game()
    : paletka(320, 540, 100, 20, 16),
      pilka(10, 320, 240.f, 180.f, 8.f)
{
    const int   kolumna = 6;
    const int   rzad = 7;
    const float wys_blok = 25.f;
    const float GAP = 2.f;
    const float OFFY = 50.f;
    const float WIN_W = 800.f;

    float szer_blok = (WIN_W - (kolumna - 1) * GAP) / kolumna;

    for (int y = 0; y < rzad; y++)
        for (int x = 0; x < kolumna; x++)
        {
            float px = x * (szer_blok + GAP);
            float py = OFFY + y * (wys_blok + GAP);
            int hp   = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            bloki.emplace_back(sf::Vector2f(px, py), sf::Vector2f(szer_blok, wys_blok), hp);
        }
}

void Game::update(sf::Time dt)
{
    pilka.move(dt);
    pilka.colide_walls(800.f, 640.f);
    pilka.collidePaddle(paletka);


    if (pilka.getY() - pilka.getRadius() > 640.f)
    {
        throw std::runtime_error("PRZEGRANA");
    }

    
    for (auto &blok : bloki)
    {
        if (blok.isBroken()) continue;

        float blok_x = blok.getPosition().x;
        float blok_y = blok.getPosition().y;
        float blok_szer = blok.getSize().x;
        float blok_wys = blok.getSize().y;

        float pil_x = pilka.getX();
        float pil_y = pilka.getY();
        float r  = pilka.getRadius();
        // najblizszy punkt krawedzi bloku do srodka piiki
        float wall_x = clampf(pil_x, blok_x, blok_x + blok_szer);
        float wall_y = clampf(pil_y, blok_y, blok_y + blok_wys);

        float odl_x = pil_x - wall_x;
        float odl_y = pil_y - wall_y;

        if (odl_x*odl_x + odl_y*odl_y <= r*r)
        {
            blok.trafienie();
            if (std::abs(odl_x) > std::abs(odl_y)) pilka.odbicieX();
            else pilka.odbicieY();
            break;
        }
    }
}
//pierwsze narysowanie
void Game::render(sf::RenderTarget &t)
{
    for (auto &blok : bloki)
        blok.draw(t);

    paletka.draw(t);
    pilka.draw(t);
}
//przywraca zapisane dane
void Game::przywruc(const GameState& state)
{
    paletka.setPosition(state.getPaddlePos().x,
                        state.getPaddlePos().y);

    pilka.setPosition(state.getBallPos().x,
                      state.getBallPos().y);

    pilka.setVelocity(state.getBallVel().x,
                      state.getBallVel().y);

    const auto& dataBloki = state.getBlocks();
    std::size_t n = std::min(dataBloki.size(), bloki.size());

    for (std::size_t i = 0; i < n; i++)
    {
        bloki[i].setPosition(dataBloki[i].x, dataBloki[i].y);
        bloki[i].setHP(dataBloki[i].hp);
    }
}
