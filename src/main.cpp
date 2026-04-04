#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "WINDOW_TITLE");
    window.setFramerateLimit(50);
    std::vector<sf::Shape*> shapes;

    while (window.isOpen())
    {
       
         while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return 0;
            }
            
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                sf::CircleShape *shape = new sf::CircleShape(50);
                shape->setPosition({event->getIf<sf::Event::MouseButtonPressed>()->position.x - 25, event->getIf<sf::Event::MouseButtonPressed>()->position.y - 25});
                shape->setFillColor(sf::Color(100, 250, 50));
                shapes.push_back(shape);
            } 
        }

        window.clear();

        for(auto it=shapes.begin();it!=shapes.end();it++)
        {
            window.draw(**it);
        }
        window.display();
    }

    return 0;
}


