#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>
#include <string>

using namespace std;

// prototype
void drawBoard(sf::RenderWindow *window, Game *game);
void drawFinishedScreen(sf::RenderWindow *window, Game *game);

bool clicked = false;
bool finished = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(770, 770), "Connect 4");
    sf::RenderWindow finishedWindow(sf::VideoMode(405, 200), "Connect 4 - Winner Screen");
    window.setFramerateLimit(60);
    finishedWindow.setFramerateLimit(60);

    Game game;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                finishedWindow.close();
            }
        }
        while (finishedWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                finishedWindow.close();
            }
        }

        window.clear();
        drawBoard(&window, &game);
        window.display();
        if (!finished)
        {
            finishedWindow.setVisible(false);
        }
        else
        {
            finishedWindow.setVisible(true);
            finishedWindow.clear();
            drawFinishedScreen(&finishedWindow, &game);
            finishedWindow.display();
        }
    }

    return 0;
}

void drawBoard(sf::RenderWindow *window, Game *game)
{
    sf::RectangleShape bg(sf::Vector2f(window->getSize().x, window->getSize().y - 100));
    bg.setFillColor(sf::Color::Blue);
    bg.setPosition(0, 100);
    sf::CircleShape shape(45);
    shape.setFillColor(sf::Color::White);

    window->draw(bg);

    for (int i = 0; i < 7; i++)
    {
        sf::IntRect colBox(sf::Vector2(110 * i, 0), sf::Vector2(110, (int)window->getSize().y));

        for (int k = 0; k < 6; k++)
        {
            int chipX = 10 + 110 * i;
            shape.setPosition(chipX, window->getSize().y - 110 * (k + 1) + 10);

            switch (game->board[i][k])
            {
            case (chip::Yellow):
                shape.setFillColor(sf::Color::Yellow);
                break;
            case (chip::Red):
                shape.setFillColor(sf::Color::Red);
                break;
            default:
                if (!finished)
                {
                    if (colBox.contains(sf::Mouse::getPosition(*window)))
                    {
                        // preview the chip if hovering over a column
                        if ((!finished) && ((game->board[i][0] == chip::Empty && k == 0) || (k > 0 && game->board[i][k - 1] != chip::Empty)))
                        {
                            sf::CircleShape previewChip(45);
                            previewChip.setPosition(chipX, 10);

                            switch (game->turn)
                            {
                            case (turn::Yellow):
                                previewChip.setFillColor(sf::Color(255, 253, 150));
                                break;
                            case (turn::Red):
                                previewChip.setFillColor(sf::Color(255, 105, 97));
                                break;
                            }

                            window->draw(previewChip);
                        }

                        // checking for click
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked != sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            clicked = true;
                            Move move = game->play(i);
                            if (move.success)
                            {
                                bool won = game->checkWin(move.col, move.row);
                                bool tied = game->isTied();
                                if (!won && !tied)
                                {
                                    game->turn = static_cast<turn::Turn>((game->turn + 1) % (turn::Red + 1));
                                }
                                else
                                {
                                    finished = true;
                                }
                            }
                        }
                        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            clicked = false;
                        }
                    }
                }
                shape.setFillColor(sf::Color::White);
                break;
            };

            window->draw(shape);
        }
    }
}

void drawFinishedScreen(sf::RenderWindow *window, Game *game)
{
    sf::RectangleShape bg(sf::Vector2f(window->getSize()));
    bg.setFillColor(sf::Color::Black);

    sf::Font font;
    if (!font.loadFromFile("./Montserrat-Regular.otf"))
    {
        cout << "Error loading font.\n";
    }

    sf::Text winText;

    string winnerText = "";

    if (game->isTied())
    {
        winnerText += "Tied!";
    }
    else
    {

        switch (game->turn)
        {
        case (turn::Yellow):;
            winnerText += "Yellow won!";
            break;
        case (turn::Red):
            winnerText += "Red won!";
            break;
        };
    }

    winText.setFont(font);
    winText.setString(winnerText);
    winText.setCharacterSize(20);
    winText.setFillColor(sf::Color::White);
    winText.setPosition(145, 50);
    winText.setStyle(sf::Text::Bold);

    sf::RectangleShape playAgainBox(sf::Vector2f(365, 55));
    playAgainBox.setFillColor(sf::Color::Black);
    playAgainBox.setOutlineThickness(10);
    playAgainBox.setPosition(20, 90);

    sf::Text playAgainText;
    playAgainText.setFont(font);
    playAgainText.setString("PLAY AGAIN");
    playAgainText.setCharacterSize(52);
    playAgainText.setPosition(35, 85);
    playAgainText.setStyle(sf::Text::Bold);

    sf::Rect playAgainButton(playAgainBox.getGlobalBounds());

    if (playAgainButton.contains(sf::Vector2<float>(sf::Mouse::getPosition(*window))))
    {
        playAgainBox.setOutlineColor(sf::Color::Yellow);
        playAgainText.setFillColor(sf::Color::Yellow);

        // checking for click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked != sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicked = true;
            finished = false;
            game->resetGame();
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            clicked = false;
        }
    }
    else
    {
        playAgainBox.setOutlineColor(sf::Color::White);
        playAgainText.setFillColor(sf::Color::White);
    }

    window->draw(bg);
    window->draw(playAgainBox);
    window->draw(winText);
    window->draw(playAgainText);
}