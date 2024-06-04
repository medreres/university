
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
#include <vector>
#include "ResourcePath.hpp"
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
const int height = 768;
const int width = 1366;
int loop_pause = 130;
int Score = 0;
bool loose = 0;
bool pause = 0;
class Button{
    
public:
    Button(){};
    Button(string t,Font& font,int size = 128)
    {
        text.setString(t);
        text.setFillColor(Color::White);
        text.setCharacterSize(size);
        text.setFont(font);
        
        shape.setSize(Vector2f(text.getLocalBounds().width,text.getLocalBounds().height));
        shape.setFillColor(Color::Blue);
    }
    void setTextColor(Color color)
    {
        text.setFillColor(color);
    }
    void setPosition(Vector2f pos)
    {
        shape.setPosition(pos);
        float xPos = pos.x+shape.getLocalBounds().width/2 - text.getLocalBounds().width/2;
        float yPos = pos.y+shape.getLocalBounds().height/2 - text.getLocalBounds().height;
        text.setPosition(xPos, yPos);
    }
    void drawTo(RenderWindow &window)
    {
        window.draw(text);
        
    }
    bool isMouserOver(RenderWindow &window)
    {
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;
        
        float btnPosX = shape.getPosition().x;
        float btnPosY = shape.getPosition().y;
        
        float btnPosWidth = btnPosX + shape.getGlobalBounds().width;
        float btnPosHeight = btnPosY + shape.getGlobalBounds().height;
        
        if(mouseX < btnPosWidth && mouseX > btnPosX && mouseY<btnPosHeight && mouseY>btnPosY)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    RectangleShape shape;
    Text text;
};
bool if_collapse(RectangleShape& player,RectangleShape& fruit){
    if(abs(player.getPosition().x - fruit.getPosition().x)<(player.getSize().x+fruit.getSize().x)/2 && abs(player.getPosition().y-fruit.getPosition().y)<(player.getSize().y+fruit.getSize().y)/2)
    {
        return 1;
    }
    else return 0;
    
}
bool if_collapse(RectangleShape& player,vector<RectangleShape>& tails){
    for (int i = 0; i < tails.size(); i++) {
        if(player.getPosition() == tails[i].getPosition())
        {
            return 1;
        }
        
    }
    return 0;
    
}
void if_eat(RectangleShape& player,RectangleShape& fruit,RectangleShape& tail,vector<RectangleShape>& tails){
    if(if_collapse(player,fruit))
    {
        tail.setPosition(player.getPosition());
        tails.push_back(tail);
        fruit.setPosition(rand()%(width/50)*50, rand()%(height/50)*50);
        loop_pause = (loop_pause<100)? loop_pause-1:loop_pause-3;
        Score+=10;
    }
}
static void showLooseScreen(int &direcion, sf::Text &score, const sf::Text &text) {
    direcion = -1;
    loose = 1;
    string temp;
    temp = "Your score : ";
    temp.append(to_string(Score));
    score = text;
    score.setString(temp);
    score.setPosition(width/2 - score.getLocalBounds().width/2,height/2-score.getLocalBounds().height/2);
}
int main(int, char const**)
{
    srand(time(NULL));
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Snake");
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    Font font;
    if(!font.loadFromFile(resourcePath()+"sansation.ttf"))
    {
        return EXIT_FAILURE;
    }
    
    Text text,score;
    text.setFont(font);
    text.setString("You loose!");
    text.setCharacterSize(128);
    text.setPosition(width/2-text.getLocalBounds().width/2   , height/2-text.getLocalBounds().height/2-128);
    
    
    
    //Restart button
    Button button("Restart",font,128);
    button.setPosition(Vector2f(width/2-button.shape.getLocalBounds().width/2,height/2+128));
    
    //Pause screen
    Button yes_btn("Yes",font,64);
    yes_btn.setPosition(Vector2f(width/2-yes_btn.shape.getLocalBounds().width/2-64,height/2+50));
    Button no_btn("No",font,64);
    no_btn.setPosition(Vector2f(width/2+no_btn.shape.getLocalBounds().width/2+64,height/2+50));
    Text pause_txt;
    pause_txt.setString("Would you like to quit?");
    pause_txt.setFont(font);
    pause_txt.setCharacterSize(64);
    pause_txt.setPosition(width/2-pause_txt.getLocalBounds().width/2, height/2-pause_txt.getLocalBounds().height/2-128);
    bool is_pause = 0;
   
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    //physics
    int direcion = -1;//0 upwards1 downwards,3 right,4 left
    Clock clock;
    
    
    //player
    sf::RectangleShape player (sf::Vector2f(40,40));
    player.setFillColor(Color(70,115,232));
    player.setPosition(rand()%(width/40)*40, rand()%(height/40)*40);
    
    
    //body
    RectangleShape tail (sf::Vector2f(40,40));
    tail.setFillColor(Color(70,115,232));
    vector<RectangleShape> tails;
    int last = tails.size()-1;
    
    
    
    //fruit
    RectangleShape fruit(sf::Vector2f(50,50));
    fruit.setFillColor(Color(231, 71, 29));
    fruit.setPosition(width/2+40, height/2+40);
    
    // Start the game loop
    while (window.isOpen())
    {
        
        Vector2f temp_only; // for snake with 10 scores
        sleep(Time(milliseconds(loop_pause)));
        Time elapsed = clock.getElapsedTime();
        
        
        // Process events
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if(event.type == Event::MouseMoved){ // restart
                if(button.isMouserOver(window))
                {
                    button.setTextColor(Color::Red);
                }
                else
                {
                    button.setTextColor(Color::White);
                }
            }
            if(!loose) //pause menu
            {
                if(event.type == Event::MouseMoved && pause){
                    if(yes_btn.isMouserOver(window))
                    {
                        yes_btn.setTextColor(Color::Red);
                    }
                    else
                    {
                        yes_btn.setTextColor(Color::White);
                    }
                }
                if(event.type == Event::MouseMoved && pause){
                    if(no_btn.isMouserOver(window))
                    {
                        no_btn.setTextColor(Color::Red);
                    }
                    else
                    {
                        no_btn.setTextColor(Color::White);
                    }
                }
                if(pause && event.type == Event::MouseButtonPressed && yes_btn.isMouserOver(window))
                {
                    window.close();
                }
                if( pause && event.type == Event::MouseButtonPressed && no_btn.isMouserOver(window))
                {
                    pause = 0;
                }
                if(event.KeyPressed && event.key.code == Keyboard::Escape)
                {
                    pause = 1;
                    is_pause = 1;
                }
            }
            if( (loose && (event.type == Event::MouseButtonPressed && button.isMouserOver(window)))   //if loose
               || ( loose && event.type == Event::KeyPressed && event.key.code == sf::Keyboard::Enter)){
                
                loose = 0;
                direcion = -1;
                tails.clear();
                Score = 0;
                player.setPosition(rand()%(width/40)*40, rand()%(height/40)*40);
                fruit.setPosition(rand()%(width/50)*50, rand()%(height/50)*50);
                loop_pause = 130;
                last = tails.size()-1;
                
            }
            
            
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::W) {
                direcion = 0;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::S){
                direcion = 1;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::D){
                direcion = 2;
            }
            if(event.type == Event::KeyPressed && event.key.code ==
               Keyboard::A){
                direcion = 3;
            }
        } //processing physics
        
        if(!(loose || pause)){
            //moving player
            if_eat(player, fruit, tail, tails);
            if(last<0 && tails.size()!=0)
            {
                last = tails.size()-1;
            }
            if(tails.size()!=0)
            {
                temp_only = tails[last].getPosition();
                tails[last--].setPosition(player.getPosition());
            }
            switch(direcion)
            {
                case 0:
                    player.move(0, -player.getSize().y);
                    
                    break;
                case 1:
                    player.move(0, player.getSize().y);
                    break;
                case 2:
                    player.move(player.getSize().x,0);
                    break;
                case 3:
                    player.move(-player.getSize().x,0);
                    break;
                default:
                    break;
            }
            if(player.getPosition() == temp_only)
            {
                showLooseScreen(direcion, score, text);
            }
            if(player.getPosition().x<0 || player.getPosition().x>width || player.getPosition().y>height || player.getPosition().y<0)
            {
                showLooseScreen(direcion, score, text);
            }
            if(if_collapse(player, tails)&&!loose)
            {
                showLooseScreen(direcion, score, text);
            }
        }
        // Clear screen
        
        window.clear(Color(170, 215, 81));
        window.draw(fruit);
        window.draw(player);
        for (int i  = 0; i<tails.size(); i++)
        {
            window.draw(tails[i]);
        }
        if(loose){
            window.draw(text);
            window.draw(score);
            button.drawTo(window);
        }
        if(pause)
        {
            yes_btn.drawTo(window);
            no_btn.drawTo(window);
            window.draw(pause_txt);
        }
        //             Update the window
        window.display();
        
        
    }
    
    return EXIT_SUCCESS;
}
