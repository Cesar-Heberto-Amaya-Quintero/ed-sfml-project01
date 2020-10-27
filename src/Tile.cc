#include "Tile.hh"

Tile::Tile(float posX,float posY,float scale,float cropSize, sf::Texture*& texture)
{
    sprite = new sf::Sprite(*texture, *(new sf::IntRect(posX,posY, cropSize, cropSize)));
    sprite->setScale(scale, scale);
}

Tile::~Tile()
{

}

sf::Sprite* Tile::GetSprite() const
{
    return sprite;
}

void Tile::Move(float x, float y)
{
    sprite->move(x,y);
}

void Tile::SetPosition(float x, float y)
{
    sprite->setPosition(x,y);
}