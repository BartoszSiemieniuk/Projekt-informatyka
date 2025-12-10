#include <SFML/Graphics.hpp>
#include <iostream>

#include "Menu.h"
#include "Game.h"
#include "gamestate.h"


enum class Tryb
{
    Menu,
    Playing,
    Pauza,
    Porazka,
    Exiting
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState szyb_zapis;

    Tryb state = Tryb::Menu;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (state == Tryb::Menu)
                {
                    if (event.key.code == sf::Keyboard::Up)
                        menu.menu_up();
                    else if (event.key.code == sf::Keyboard::Down)
                        menu.menu_down();
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int sel = menu.getWybrane();

                        if (sel == 0)
                        {
                            game = Game();
                            state = Tryb::Playing;
                        }
                        else if (sel == 1)
                        {
                            GameState loaded;
                            if (loaded.odczyt_plik("zapis.txt"))
                            {
                                game.przywruc(loaded);
                                std::cout << "Wczytano gre!\n";
                                state = Tryb::Playing;
                            }
                            else
                            {
                                std::cout << "Blad: brak pliku zapis.txt\n";
                            }
                        }

                        else if (sel == 2) 
                            window.close();
                    }
                }


                else if (state == Tryb::Playing)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        game.getPaletka().pal_lewo();
                    else if (event.key.code == sf::Keyboard::Right)
                        game.getPaletka().pal_prawo();

                    game.getPaletka().ClampToBounds(800.f);


                    if (event.key.code == sf::Keyboard::P)
                    {
                        szyb_zapis.capture(game.getPaletka(),
                                         game.getPilka(),
                                         game.getBloki());
                        game.getPilka().stop();
                        state = Tryb::Pauza;
                    }


                    if (event.key.code == sf::Keyboard::U)
                        game.przywruc(szyb_zapis);


                    if (event.key.code == sf::Keyboard::F5)
                    {
                        GameState save;
                        save.capture(game.getPaletka(), game.getPilka(), game.getBloki());

                        if (save.zapis_plik("zapis.txt"))
                            std::cout << "Zapisano!\n";
                        else
                            std::cout << "Nie udalo sie zapisac!\n";
                    }
                }


                else if (state == Tryb::Pauza)
                {
                    if (event.key.code == sf::Keyboard::P)
                    {
                        auto v = szyb_zapis.getBallVel();
                        game.getPilka().setVelocity(v.x, v.y);
                        state = Tryb::Playing;
                    }

                    if (event.key.code == sf::Keyboard::Z)
                        game.przywruc(szyb_zapis);

                    if (event.key.code == sf::Keyboard::Escape)
                        state = Tryb::Menu;
                }

                else if (state == Tryb::Porazka)
                {
                    if (event.key.code == sf::Keyboard::Num1)
                    {
                        game = Game();
                        state = Tryb::Playing;
                    }
                    else if (event.key.code == sf::Keyboard::Num2)
                    {
                        state = Tryb::Menu;
                    }
                    else if (event.key.code == sf::Keyboard::Num3)
                    {
                        window.close();
                    }
                }
            }
        }
        //pomiar czasu
        sf::Time dt = clock.restart();
        //czyszczenie klatek
        window.clear();


        if (state == Tryb::Menu)
        {
            menu.draw(window);
        }
        else if (state == Tryb::Playing)
        {
            //pruba aktualizacji
            try
            {
                game.update(dt);
            }
            catch(...)
            {
                state = Tryb::Porazka;
            }

            game.render(window);
        }
        else if (state == Tryb::Pauza)
        {
            game.render(window);

            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text pauza("Pauza - P=Wznow, Z=Szybki Zapis, F5=Staly Zapis", font, 24);
            pauza.setFillColor(sf::Color::Yellow);
            pauza.setPosition(40, 300);
            window.draw(pauza);
        }
        else if (state == Tryb::Porazka)
        {
            sf::Font font;
            font.loadFromFile("arial.ttf");

            sf::Text t("PRZEGRALES!", font, 60);
            t.setFillColor(sf::Color::Red);
            t.setPosition(180, 200);

            sf::Text opcja_1("1. Nowa gra", font, 32);
            opcja_1.setPosition(220, 340);

            sf::Text opcja_2("2. Wroc do menu", font, 32);
            opcja_2.setPosition(220, 390);

            sf::Text opcja_3("3. Wyjscie", font, 32);
            opcja_3.setPosition(220, 440);

            window.draw(t);
            window.draw(opcja_1);
            window.draw(opcja_2);
            window.draw(opcja_3);
        }

        window.display();
    }

    return 0;
}
