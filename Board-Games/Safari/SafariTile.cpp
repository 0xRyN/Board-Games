#include "SafariTile.hpp"

SafariTile::SafariTile(bool dark, int x, int y, bool northBarrier, bool eastBarrier, bool southBarrier, bool westBarrier) : Tile(dark, x, y)
{
    this->northBarrier = northBarrier;
    this->eastBarrier = eastBarrier;
    this->southBarrier = southBarrier;
    this->westBarrier = westBarrier;
}

bool SafariTile::getNorthBarrier()
{
    return northBarrier;
}

bool SafariTile::getEastBarrier()
{
    return eastBarrier;
}

bool SafariTile::getSouthBarrier()
{
    return southBarrier;
}

bool SafariTile::getWestBarrier()
{
    return westBarrier;
}

void SafariTile::setNorthBarrier(bool northBarrier)
{
    this->northBarrier = northBarrier;
}


void SafariTile::setEastBarrier(bool eastBarrier)
{
    this->eastBarrier = eastBarrier;
}

void SafariTile::setSouthBarrier(bool southBarrier)
{
    this->southBarrier = southBarrier;
}

void SafariTile::setWestBarrier(bool westBarrier)
{
    this->westBarrier = westBarrier;
}

