
#include <iostream>

extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}

#include "LuaBridge/LuaBridge.h"
#include "sol/sol.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Entity.h"
#include "NPCComponent.h"
#include "GraphicsComponent.h"
#include "CollisionComponent.h"
#include "World.h"

// TODO: Move to file.
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

    sol::state lua;
	lua.open_libraries(sol::lib::base);

    lua.script_file("ghost.lua");
    lua.script_file("shaggy.lua");
    lua.script_file("tiles.lua");

    sol::table ghost = lua["ghost"];
    sol::table shaggy = lua["shaggy"];

    World world;

    world.loadEntity(ghost, "ghost");
    world.loadEntity(shaggy, "shaggy");

    sol::table tiles = lua["tiles"];
    for (const auto& key_value_pair : tiles) {
        sol::object key = key_value_pair.first;
        sol::object value = key_value_pair.second;

        world.loadEntity(value, key.as<std::string>());
    }

    world.generateMap(tiles);

    // create the window
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "OpenGL");
    window.setVerticalSyncEnabled(true);
    

    // activate the window
    window.setActive(false);

    bool running = true;
    sf::Thread thread([&] () {
        // activate the window's context
        window.setActive(true);
        char fr[64];
        int frameCount = 0;
        float frameTotal = 0;
        float rate = 0.0f;

        // the rendering loop
        while (window.isOpen())
        {
            if (!running) {
                return;
            }

            frameTotal += 1.f / clock.getElapsedTime().asSeconds();
            clock.restart();

            // Draw Entities
            window.clear(sf::Color::Red);
            for (Entity* e : world.getEntities()) {
                GraphicsComponent* gc = e->get<GraphicsComponent>();
                if (gc) {
                    window.draw(*gc->getSprite());
                    gc->getSprite()->move(1, 0);
                }
            }

            // Draw UI
            if (frameCount >= 10) {
                rate = frameTotal / frameCount;
                frameCount = 0;
                frameTotal = 0;
            }

            sprintf(fr, "%.2f", rate);

            sf::Text text;
            sf::Font font;
            font.loadFromFile("TravelingTypewriter.ttf");
            text.setFont(font);
            text.setString(fr);
            text.setCharacterSize(64);
            text.setFillColor(sf::Color::White);
            window.draw(text);

            // end the current frame
            window.display();

            frameCount++;
        }
    });
    thread.launch();

    world.printEntityMap();

    // run the main loop
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
        }

        world.update();
    }

    // release resources...
    thread.wait();
    window.close();
    std::cout << "Program quit!\n";

    return 0;
}
