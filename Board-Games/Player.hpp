#include <string>
#include <SFML/Graphics.hpp>


class Player {
    public:
        Player(std::string name, Color color);
        std::string getName() const;
        sf::Color getColor() const;
    
    private:
        std::string name;
        sf::Color color;
    };