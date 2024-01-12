#ifndef INCOGNITO_HPP
#define INCOGNITO_HPP

#include <Board-Games/BoardGame.hpp>

class Incognito : public BoardGame
{   
public:
    Incognito();
    void loadTextures();
    bool handleTurn(Move& move) override;
};

#endif // INCOGNITO_HPP

