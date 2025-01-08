#include <iostream>
#include <concepts>

#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "GDPARCM CMake Test");
    window.setFramerateLimit(144);

    std::cout << "C++ Version: " << __cplusplus;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
