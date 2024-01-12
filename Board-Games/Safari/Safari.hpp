#ifndef SAFARI_HPP
#define SAFARI_HPP

#include "BoardGame.hpp"

class Safari : public BoardGame {
public:
    Safari();
    void loadTextures();
    bool handleTurn(Move& move) override;
};




#endif // SAFARI_HPP
