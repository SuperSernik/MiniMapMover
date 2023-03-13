#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include "Player.h"


#define LOG(x) std::cout<<x<<std::endl 


float lerp(float v0, float v1, float t) {
    return (1 - t) * v0 + t * v1;
}

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window", sf::Style::Default);
    
    float mainViewZoom = 2.f;
    //Player instance
    game::Player player1;
    

    // view of the game (camera)
    sf::View view(sf::FloatRect(0, 0, 1600.f, 900.f));                          //RECTANGLE
    //sf::View view(sf::Vector2f(350.f, 300.f), sf::Vector2f(1000.f, 1000.f));  // CENTER AND SIZE

    //view.setCenter(1.f, 1.f)                                          // sets center      
    //view.move(100.f, 100.f);                                          // move view
    //view.rotate(5.f);                                                 // rotate view
    //view.setSize(1200.f, 800.f);                                      // resize the view to show a 1200x800 area (we see a bigger area, so this is a zoom out)
    view.zoom(mainViewZoom);                                                   // zoom the view relatively to its current size (apply a factor 0.5, so its final size is 600x400)
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));         // define a centered viewport, with half the size of the window
    //window.setView(view);


    //MINIMAP
    sf::View minimap(sf::FloatRect(0, 0, 10000.f, 4000.f));
    minimap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
    //window.setView(minimap);

    //MINIMAP VIEW WINDOW RECT
    sf::RectangleShape minimapwindow_rect(sf::Vector2f(1600.f * mainViewZoom, 900.f * mainViewZoom));
    minimapwindow_rect.setPosition(sf::Vector2f(0, 0));
    minimapwindow_rect.setOutlineThickness(50.f);
    minimapwindow_rect.setOutlineColor(sf::Color::Blue);
    minimapwindow_rect.setFillColor(sf::Color::Transparent);

    // background IMG
    sf::Texture background;
    background.loadFromFile("assets\\bg.jpg");
    sf::Sprite background_s(background);

    // background COLOR
    sf::Texture background_color;
    background_color.loadFromFile("assets\\1600x900bg.png");
    sf::Sprite background_s_color(background_color);

    // quads
    sf::Texture texture;
    texture.loadFromFile("assets\\ball.png");
    sf::VertexArray quad(sf::Quads, 4);

    // define it as a rectangle, located at (10, 10) and with size 100x100
    quad[0].position = sf::Vector2f(600.f, 0.f);
    quad[1].position = sf::Vector2f(800.f, 0.f);
    quad[2].position = sf::Vector2f(800.f, 200.f);
    quad[3].position = sf::Vector2f(600.f, 200.f);
    // define its texture area to be a 25x50 rectangle starting at (0, 0)
    quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    quad[1].texCoords = sf::Vector2f(25.f, 0.f);
    quad[2].texCoords = sf::Vector2f(25.f, 70.f);
    quad[3].texCoords = sf::Vector2f(0.f, 50.f);

    //Text
    sf::Font arial;
    if (!arial.loadFromFile("fonts\\arial.ttf"))
        return EXIT_FAILURE;

    sf::Text text;
    text.setFont(arial);
    text.setString("Hello World");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(sf::Vector2f(100.f, 100.f));

    
    // Triangle with colored gradient
    sf::VertexArray triangle(sf::Triangles, 3);
    // define the position of the triangle's points
    triangle[0].position = sf::Vector2f(900.f, 50.f);
    triangle[1].position = sf::Vector2f(1400.f, 50.f);
    triangle[2].position = sf::Vector2f(1400.f, 550.f);
    // define the color of the triangle's points
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Blue;
    triangle[2].color = sf::Color::Green;

    

    // Start the game loop
    while (window.isOpen())
    {

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            /*
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            */

        }
        // Clear screen
        window.clear(sf::Color::Color(200, 200, 200));
        // ALL OF THE CONTENT WE WANT TO DRAW WE PLACE AFTER HERE 


        int x1 = 1600;
        int x2 = 1000 - 1600;
        int y1 = 900;
        int y2 = 4000 - 900;

        if (player1._sprite.getPosition().x < x1) {
            view.setCenter(x1, player1._sprite.getPosition().y);
        }
        if (player1._sprite.getPosition().x > x2) {
            view.setCenter(x2, player1._sprite.getPosition().y);
        }
        if (player1._sprite.getPosition().y < y1) {
            view.setCenter(player1._sprite.getPosition().x, y1);
        }
        if (player1._sprite.getPosition().y > y2) {
            view.setCenter(player1._sprite.getPosition().x, y2);
        }

        else {
            view.setCenter(player1._sprite.getPosition().x, player1._sprite.getPosition().y);

        }





        //view.setCenter(player1._sprite.getPosition().x, player1._sprite.getPosition().y);

        //GAME VIEW
        window.setView(view);
        window.draw(background_s);
        window.draw(background_s_color);
        window.draw(text);
        window.draw(player1._sprite);

        window.draw(triangle);
        window.draw(quad, &texture);

        player1.MovePlayer(window);
        //player1.MovePlayer(window);


        //MINIMAP VIEW
        window.setView(minimap);
        window.draw(background_s);
        window.draw(background_s_color);
        window.draw(text);
        window.draw(player1._sprite);

        window.draw(triangle);
        window.draw(quad, &texture);

        player1.ControlPlayerWithMouse(window);

        minimapwindow_rect.setPosition(player1._sprite.getPosition().x - 800*mainViewZoom, player1._sprite.getPosition().y - 450* mainViewZoom);
        window.draw(minimapwindow_rect);
        

        // AND BEFORE HERE
        // Update the window
        window.display();
        

    }
    return EXIT_SUCCESS;



    std::cin.get();
}