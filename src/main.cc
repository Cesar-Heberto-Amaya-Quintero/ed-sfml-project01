#include <iostream>
#include <SFML/Graphics.hpp>

#include "Inputs.hh"

#define WINDOW_WIDTH 800
#define WINDOW_HEIHGT 600
#define GAME_NAME "RogueLike game"

int main ()
{
    
    //Esto es la ventana de tu grafico
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIHGT), GAME_NAME);
    //Aqui se guardan los eventos dentro de la ventana, eje: teclado, mouse, etc.
    sf::Event event;

    Inputs* inputs = new Inputs();

    //declaramos variable de tipo texture
    sf::Texture texture;

    //Comprobamos que nuestra variable obtenga la imagen que le estamos dando
    if(!texture.loadFromFile ("sprites/megaman.png")) 
    {
        //Si no va a mandar mensaje de error
        std::cout << "Load failed" << std::endl;

        system("pause");
    }

    //Si exede el tamaño se repite la textura
    texture.setRepeated(true);

    //Creamos variable sprite
    sf::Sprite sprite;
    //Asignamos nuestra textura a la variable sprite
    sprite.setTexture(texture);
    //Seleccionamos parte de la imagen
    sprite.setTextureRect(sf::IntRect(0,0,400,400));

    //Cambiamos el color del sprite, se puede agregar un cuarto valor el cual es el alpha
    //sprite.setColor(const sf::Color(0,0,255));

    //Con esto movemos el sprite de lugar
    sprite.move(100,100);

    //Aquí le asignamos un nuevo centro al sprite, creando un vector2 que tiene sentido en x y y
    sf::Vector2f centro;
    centro.x = sprite.getTextureRect().width /2.f;
    centro.y = sprite.getTextureRect().height /2.f;
    sprite.setOrigin(centro);



    //Esto es el loop principal, mientras la ventana este abierta, esto se va a ejecutar.
    while (window->isOpen())
    {
        //Mientras se esten ejecutando eventos dentro de la ventana, esto se va a repetir, ej: teclado, joystick, mouse, etc
        while (window->pollEvent(event))
        {
            //Si el evento fue la acción de cerrar la ventana, entonces cierra la aplicación
            if(event.type == sf::Event::Closed)
            {
                window->close();
            }
        }

    Vec2* keyboardAxis{inputs->GetKeyboardAxis()};
    Vec2* joystickAxis{inputs->GetJoystickAxis()};
    //std::cout << "keyboard axis x: " << keyboardAxis->x << " keyboard axis y: " << keyboardAxis->y << std::endl;
        
    std::cout << "joystic axis x: " << joystickAxis->x << " joystic axis y: " << joystickAxis->y << std::endl;

    delete keyboardAxis;
    delete joystickAxis;

    window->clear(sf::Color(100, 150, 30));

    window->draw(sprite); 

    window->display();
        
    }
    
    return 0;
}