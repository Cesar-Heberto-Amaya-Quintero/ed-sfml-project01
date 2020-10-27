//Pragma once permite importar una cabecera (un archivo h o hh) muchas veces pero solo lo carga una vez.
#pragma once
#include <SFML/Graphics.hpp>

class Tile
{
private:
    sf::Sprite* sprite;
public:
    Tile(float,float,float,float, sf::Texture*&);
    ~Tile();
    void Move(float,float);
    void SetPosition(float,float);
    sf::Sprite* GetSprite() const;
};

