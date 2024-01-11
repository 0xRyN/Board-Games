
#include <Board-Games/BoardGame.hpp>
#include <Board-Games/GameState.hpp>


class IncognitoState : public GameState
{
private:
    /* data */
public:
    IncognitoState(int boardSize, Player* firstPlayer, Player* secondPlayer);
    void initializeGame() override;
    void putRandomSpies();
};


