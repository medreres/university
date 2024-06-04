
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;
int const W = 2000;
int const H = 768;

class Dot
{
public:
    CircleShape shape;
    
    Dot(float radius = 2)
    {
        shape.setRadius(2);
        shape.setFillColor(Color::Red);
        shape.setPosition(0, H / 2);
    }
};

int main(int, char const **)
{
    
    sf::RenderWindow renderWindow(sf::VideoMode(W, H), "Cycloid");
    sf::Event event;
    
    //Graphic
    double x(0), y, r, t(0), x1(0), y1(0);
    r = 150;
    
    //dot
    CircleShape dot;
    dot.setRadius(5);
    dot.setFillColor(Color::Red);
    dot.setPosition(0,H/2);
    vector<Dot> dots;
    x=r*t-r*sin(t);
    y=r-r*cos(t);
    
    //horizontal line
    RectangleShape line;
    line.setFillColor(Color::Black);
    line.setPosition(0, H/2);
    line.setSize(Vector2f(W,4));
    
    //circle
    CircleShape circle(r);
    circle.setOutlineThickness(4);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(0, H/2-r);
    circle.setOutlineColor(Color::Black);
    
    //circle radius
    sf::VertexArray lines(sf::LinesStrip, 2);
    lines[0].position = sf::Vector2f(W/2, H/2);
    lines[0].color = Color::Black;
    lines[1].position = sf::Vector2f(W/2+200, H/2+500);
    lines[1].color = Color::Black;
    
    
    while (renderWindow.isOpen())
    {
       while (renderWindow.pollEvent(event))
        {
            if (event.type == sf::Event::EventType::Closed)
                renderWindow.close();
        }
        
        //physics graphic
        
        
        
        
        if(x<W&&x1+r<W)
        {
            t+=0.0004;
            x1+=0.0603;
            x=r*t-r*sin(t);
            y=r+r*cos(t)+80;
            dot.setPosition(x,y);
            cout << x << " "<<y << endl;
            //x1=x-sqrt(pow(r,2)+pow((y-H/2),2 ));
            lines[1].position = sf::Vector2f(dot.getPosition().x, y);
            lines[0].position = sf::Vector2f(x1, H/2-r);
            circle.setPosition(x1, H/2-r);
            
            Dot d1;
            d1.shape.setPosition(x, y);
            dots.push_back(d1);
        }
        
        
        
        
        //Render
        renderWindow.clear(sf::Color::White);
        
        renderWindow.draw(line);
        
        renderWindow.draw(circle);
        
        renderWindow.draw(dot);
        
        for (int i = 0; i < dots.size(); i+=150) {
            
            renderWindow.draw(dots[i].shape);
        }
        
        renderWindow.draw(lines);
        
        renderWindow.display();
    }
}
