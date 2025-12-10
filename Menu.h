#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define LICZBA_POZYCJI 4  

class Menu
{
private:
    sf::Font font;
    sf::Text menu[LICZBA_POZYCJI];
    int selectedItem = 0;

public:
    Menu(float width, float height);
    ~Menu() {}

    void menu_up();
    void menu_down();
    int getWybrane() const { return selectedItem; }

    void draw(sf::RenderWindow &window);
};
