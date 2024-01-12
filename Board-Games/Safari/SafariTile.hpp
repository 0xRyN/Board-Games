#ifndef SAFARITILE_HPP
#define SAFARITILE_HPP

#include <Board-Games/Tile.hpp>
#include <string.h>

class SafariTile : public Tile
{
private:
    bool northBarrier;
    bool eastBarrier;
    bool southBarrier;
    bool westBarrier;

public:
    SafariTile(bool dark, int x, int y, bool northBarrier, bool eastBarrier, bool southBarrier, bool westBarrier);

    ~SafariTile();

    //getters
    bool getNorthBarrier();
    bool getEastBarrier();
    bool getSouthBarrier();
    bool getWestBarrier();

    //setters
    void setNorthBarrier(bool northBarrier);
    void setEastBarrier(bool eastBarrier);
    void setSouthBarrier(bool southBarrier);
    void setWestBarrier(bool westBarrier);

};

#endif // SAFARITILE_HPP
