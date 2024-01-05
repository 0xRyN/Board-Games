#include <Board-Games/BoardGame.hpp>


class Incognito : public BoardGame
{   
public:
    Incognito();
    void loadTextures();
    bool handleTurn(Move& move) override;
};


