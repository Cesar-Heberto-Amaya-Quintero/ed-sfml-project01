#include <SFML/Graphics.hpp>
#include "Animation.hh"

class Character
{
    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float cropPosX, cropPosY, cropWidth, cropHeight;
        float scaleX, scaleY;
        Animation** animations;

        void InitSprite();
        
        
    public:
        Character(sf::Texture*&, float, float, float, float, float, float);
        ~Character();
        sf::Sprite* GetSprite() const;
        void FlipSpriteX(float x);
        void SetAnimations(Animation**);
        Animation* GetAnimation(int) const;
        
};


