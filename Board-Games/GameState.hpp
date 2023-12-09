#if !defined(GAME_STATES_HPP_)
#define GAME_STATES_HPP_

#include <vector>

class GameState {
protected:
    bool isActionInProgress;
    std::vector<std::pair<int, int>> availableActions;

public:
    GameState() {};
    virtual void startActionSequence();
    virtual void endActionSequence();
    bool actionInProgress() const;
    void setAvailableActions(const std::vector<std::pair<int, int>>& actions);
    const std::vector<std::pair<int, int>>& getAvailableActions() const;
};


#endif // 
