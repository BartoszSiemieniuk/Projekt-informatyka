#include "Menu.h"

Menu::Menu(float width, float height)
{
    //wczytuje czcionke z pliku
    font.loadFromFile("arial.ttf");

    //generuje pozycje w menu
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Cyan);
    menu[0].setString("Nowa gra");
    menu[0].setPosition(width / 3.f, height / 6.f);


    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Wczytaj gre");
    menu[1].setPosition(width / 3.f, height / 6.f * 2.f);

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(width / 3.f, height / 6.f * 3.f);
}

void Menu::draw(sf::RenderWindow &window)
{
    for (int i = 0; i < LICZBA_POZYCJI; i++)
        window.draw(menu[i]);
}
//opcje przemieszczania sie po menu
void Menu::menu_up()
{
    menu[selectedItem].setFillColor(sf::Color::White);
    selectedItem--;
    if (selectedItem < 0)
        selectedItem = LICZBA_POZYCJI - 1;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
}

void Menu::menu_down()
{
    menu[selectedItem].setFillColor(sf::Color::White);
    selectedItem++;
    if (selectedItem >= LICZBA_POZYCJI)
        selectedItem = 0;
    menu[selectedItem].setFillColor(sf::Color::Cyan);
}
