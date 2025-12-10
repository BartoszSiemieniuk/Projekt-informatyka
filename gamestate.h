#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include "Paletka.h"
#include "Pilka.h"
#include "Stone.h"

// Zachowuje dane bloku
struct BlockData {
    float x, y;
    int hp;
};

class GameState
{
private:
    sf::Vector2f paddlePos;
    sf::Vector2f ballPos;
    sf::Vector2f ballVel;

    std::vector<BlockData> blocks;

public:
    GameState() = default;

    // Zapis bierzących informacji do zmiennych
    void capture(const Paletka& paddle,
                 const Pilka& ball,
                 const std::vector<Stone>& stoneList)
    {
        paddlePos = sf::Vector2f(paddle.getX(), paddle.getY());
        ballPos   = sf::Vector2f(ball.getX(), ball.getY());
        ballVel   = sf::Vector2f(ball.getVX(), ball.getVY());

        blocks.clear();
        blocks.reserve(stoneList.size());

        for (const auto& s : stoneList)
        {
            BlockData block_inf;
            block_inf.x  = s.getPosition().x;
            block_inf.y  = s.getPosition().y;
            block_inf.hp = s.getHP();
            blocks.push_back(block_inf);
        }
    }

    //zapis z zmiennych do pliku
    bool zapis_plik(const std::string& filename) const
    {
        std::ofstream file(filename);
        if (!file.is_open())
            return false;

        file << "PADDLE " << paddlePos.x << " " << paddlePos.y << "\n";
        file << "BALL "   << ballPos.x << " " << ballPos.y << " "
             << ballVel.x << " " << ballVel.y << "\n";
        file << "BLOCKS_COUNT " << blocks.size() << "\n";

        for (auto& b : blocks)
            file << b.x << " " << b.y << " " << b.hp << "\n";

        return true;
    }


    bool odczyt_plik(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            return false;

        std::string tag;
        //Sprawdza opis (tag) jeśli nie znajdzie to wyrzuca błąd
        if (!(file >> tag) || tag != "PADDLE") return false;
        file >> paddlePos.x >> paddlePos.y;

        if (!(file >> tag) || tag != "BALL") return false;
        file >> ballPos.x >> ballPos.y
             >> ballVel.x >> ballVel.y;

        int count;
        if (!(file >> tag) || tag != "BLOCKS_COUNT") return false;
        if (!(file >> count)) return false;

        blocks.clear();
        blocks.reserve(count);
        //sprawdza pozycje i hp każdego bloku
        for (int i = 0; i < count; i++)
        {
            BlockData bd;
            file >> bd.x >> bd.y >> bd.hp;
            blocks.push_back(bd);
        }

        return true;
    }

    //getery do pól prywatnych
    const sf::Vector2f& getPaddlePos() const { return paddlePos; }
    const sf::Vector2f& getBallPos()   const { return ballPos;   }
    const sf::Vector2f& getBallVel()   const { return ballVel;   }
    const std::vector<BlockData>& getBlocks() const { return blocks; }
};
