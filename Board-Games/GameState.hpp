#if !defined(GAME_STATES_HPP_)
#define GAME_STATES_HPP_

#include <vector>
#include "Tile.hpp"
#include "Player.hpp"
class GameState {
protected:
    bool isActionInProgress;
    std::vector<std::pair<int, int>> availableActions;
    Player* currentPlayer;

    //board
    int boardSize;
    std::vector<std::vector<Tile>> board; 
    

public:
    GameState() : isActionInProgress(false){}

    void startActionSequence();
    void endActionSequence();
    bool actionInProgress() const;
     
    virtual void initializeGame() = 0;
    virtual void creatBoard() = 0;
    //getters
    const std::vector<std::pair<int, int>>& getAvailableActions() const;
    const std::vector<std::vector<Tile>>& getBoard() const;
    Player* getCurrentPlayer() const;
    int getBoardSize() const;

    //setters
    void setBoardSize(int size);
    void setBoard(const std::vector<std::vector<Tile>>& board);

};


#endif // 
