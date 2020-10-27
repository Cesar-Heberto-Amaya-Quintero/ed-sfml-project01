#include<iostream>
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <fstream>

#include "Inputs.hh"
#include "Character.hh"
#include "GameObject.hh"
#include "Maze.hh"
#include "Tile.hh"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GAME_NAME "Roguelike game"
#define TILES1 "assets/sprites/tiles1.png"
#define TILES2 "assets/sprites/tiles2.png"
#define TILES3 "assets/sprites/tiles3.png"
#define SPRITE_SCALE 4.f
#define FPS 120
#define PLAYER_MOVESPEED 3.0f

int main()
{
    //esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_NAME);
    //aqui vas a guardar los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    //Physics declaration
    b2Vec2* gravity{new b2Vec2(0.f,0.f)};
    b2World* world{new b2World(*gravity)};

    sf::Clock* clock{new sf::Clock()};
    float deltaTime{};

    window->setFramerateLimit(FPS);

    Inputs* inputs{new Inputs()};

    sf::Texture* tilesTexture1{new sf::Texture()};
    tilesTexture1->loadFromFile(TILES1);

    sf::Texture* tilesTexture2{new sf::Texture()};
    tilesTexture2->loadFromFile(TILES2);

    sf::Texture* tilesTexture3(new sf::Texture());
    tilesTexture3->loadFromFile(TILES3);

    const float tileBaseWidth{16 * SPRITE_SCALE};
    const float tileBaseHeight{16 * SPRITE_SCALE};

    //TILES
    sf::Sprite* floorSpike{new sf::Sprite(*tilesTexture3, * (new sf::IntRect(16*1, 16*11, 16,16)))};
    floorSpike->setScale(SPRITE_SCALE, SPRITE_SCALE);
    floorSpike->setPosition(16*16,16*20);

    //Items
    sf::Sprite* treasureSprite{new sf::Sprite(*tilesTexture3, *(new sf::IntRect(16 * 19,16* 19,16,16)))};
    treasureSprite->setScale(SPRITE_SCALE, SPRITE_SCALE);
    treasureSprite->setPosition(400,400);

    
   /* GameObject* treasureCollider = new GameObject(300,250,new sf::Color(0,255,0,255),16,16,
    new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(400,400),tileBaseWidth/2, tileBaseHeight/2, 1, 0,0),
    treasureSprite); */

     BoxCollider* treasureCollider = new BoxCollider(300,250,new sf::Color(0,255,0,255),16,16,
    new Rigidbody(world, b2BodyType::b2_staticBody, new b2Vec2(400,400),tileBaseWidth/2, tileBaseHeight/2, 1, 0,0),
    treasureSprite);
   
    treasureCollider->GetBoxShape()->setScale(SPRITE_SCALE, SPRITE_SCALE);

    treasureCollider->GetBoxShape()->setPosition(treasureSprite->getPosition());

    Animation* spikeAnimation {new Animation(11, 1,4, floorSpike, 300.f)};

    //La letra w= wall, b= wallB, r= wallR, g=Ground1, f=ground2, s= wallWater, c=floorWater
    // e= wallFire t=floorFire d=floorStairs x=floorBroken


    unsigned int N{10}, M{13};
    Maze* maze1{new Maze(N,M,SPRITE_SCALE,16,tilesTexture3,"assets/mazes/maze1.txt")};

    //Main player
    Character* character1{new Character(tilesTexture2, 16 * 1, 16 * 5, 16, 16, SPRITE_SCALE, SPRITE_SCALE, world,window),};
   
    character1->SetAnimations(
        new Animation*[2]
        {
            new Animation(5, 0, 5, character1->GetSprite(), 40.f),
            new Animation(6, 0, 5, character1->GetSprite(), 80.f)
        }
    );

    
    character1->SetPosition(400, 300);

    //esto es el loop principal, mientras la ventana este abierta, esto se va ejecutar.
    while (window->isOpen())
    {

        //mientras se esten ejecutando eventos dentro de la ventana, esto se va repetir eje: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //si el evento fue la acción de cerrar la ventana, entonces termina la aplicación.
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        
        Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
        Vec2* joystickAxis{inputs->GetJoystickAxis()};

        //UPDATE de física para pintarlo en pantalla

        treasureCollider->UpdatePhysics();
        //character1->GetSprite()->setPosition(playerBody->GetPosition().x, playerBody->GetPosition().y);


        if(sf::Joystick::isConnected(0))
        {
            character1->Move(new b2Vec2(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED));
            //character1->GetSprite()->move(joystickAxis->x * deltaTime * PLAYER_MOVESPEED, joystickAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(joystickAxis->x);
            if (std::abs(joystickAxis->x) > 0 || std::abs(joystickAxis->y)>0)
            {
                //Run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                {
                    //idle
                    character1->GetAnimation(0)->Play(deltaTime);
                }
            }
            
        }
        else
        {
            character1->Move(new b2Vec2(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED));
            //character1->GetSprite()->move(keyboardAxis->x * deltaTime * PLAYER_MOVESPEED, keyboardAxis->y * deltaTime * PLAYER_MOVESPEED);
            character1->FlipSpriteX(keyboardAxis->x);

            if (std::abs(keyboardAxis->x) > 0 || std::abs(keyboardAxis->y)>0)
            {
                //Run
                character1->GetAnimation(1)->Play(deltaTime);
            }
            else
            {
                {
                    //idle
                    character1->GetAnimation(0)->Play(deltaTime);
                }
            }
        }

        
        //treasureSprite->setPosition(treasureBody->GetPosition().x,treasureBody->GetPosition().y);
        //character1->GetAnimation(1)->Play(deltaTime);

        

        window->clear(*(new sf::Color(150, 100, 0, 255)));//limpiar la pantalla
        for (auto& tile: *maze1->GetContainer())
        {
            window->draw(*tile->GetSprite());
        }

        
        character1->Update();       
        spikeAnimation->Play(deltaTime);
        window->draw(*floorSpike);
        window->draw(*treasureSprite);
        window->draw(*treasureCollider->GetBoxShape());
        window->display(); //mostrar en pantalla lo que se va dibujar

        sf::Time timeElapsed = clock->getElapsedTime();
        deltaTime = timeElapsed.asMilliseconds();
        world->ClearForces();
        world->Step(1.f / 100* deltaTime, 8,8);
        clock->restart();

        //std::cout << "delta time: " << deltaTime << std::endl;

        delete keyboardAxis;
        delete joystickAxis;
    }
    
    return 0;
}