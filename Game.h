#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

class GameState;

class Game
{
private:
    Paletka paletka;
    Pilka   pilka;
    std::vector<Stone> bloki;

public:
    Game();

    void update(sf::Time dt);
    void render(sf::RenderTarget &target);

    Paletka& getPaletka() { return paletka; }
    Pilka&   getPilka()   { return pilka; }
    const std::vector<Stone>& getBloki() const { return bloki; }

    void przywruc(const GameState& state);
};
