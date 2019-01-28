#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

//game const
    const double windowWidth=800;
    const double windowHeigth=600;
    const int borderLeft=140;
    const int borderRight=660;
    const int playerWidth=40;
    const int playerHeight=70;
    string stringscore="";
    int score=0;
    double gameSpeed=0.3;

//Create Main Windows
RenderWindow app(VideoMode(windowWidth, windowHeigth), "Run Billah Run");

//Creat random Number for game loop
int getnumber(int a, int b);

// Create gameover screen
int gameOver();

int main()
{
    //Game music
    SoundBuffer gameSoundBuffer;
        gameSoundBuffer.loadFromFile("data/sound/pubg3.wav");
    Sound GameSound;
        GameSound.setBuffer(gameSoundBuffer);

    //variable for loading file
    Texture background, player, obs1, obs2, obs3, obs4,gameover;

    //text font
    Font txtfont;
    txtfont.loadFromFile("data/font/xirod.ttf");

    //Load all images
    background.loadFromFile("data/images/road.png");
    player.loadFromFile("data/images/player2.png");
    obs1.loadFromFile("data/images/obj1.png");
    obs2.loadFromFile("data/images/obj2.png");
    obs3.loadFromFile("data/images/obj1.png");
    obs4.loadFromFile("data/images/obj2.png");

    //sprite
    Sprite backgroundsprite(background),backgroundsprite1(background),
    playersprite(player),Obs1(obs1),Obs2(obs2),Obs3(obs3),Obs4(obs4),Gameover(gameover);
    playersprite.setTextureRect({120,300,60,100});
    double playerX=400, playerY=70,Obs1X, Obs1Y,Obs2X,Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y;

    //player and obj position
	playerX=windowWidth/2;
	playerY=windowHeigth-playerHeight;
	Obs1X=getnumber(borderLeft,borderRight);
	Obs2X=getnumber(borderLeft,borderRight);
	Obs3X=getnumber(borderLeft,borderRight);
	Obs4X=getnumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300;
    double backgroundY1=0;
    double backgroundY2=-600;

    GameSound.play();
    GameSound.setLoop(true);

    while (app.isOpen())
    {
        //counting score
        stringscore="SCORE:"+to_string(score);
        Text text(stringscore, txtfont, 15);
        text.setPosition(5,0);

        //set player and obstacles position
        playersprite.setPosition(playerX,playerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);

        //Infinite road creation
        backgroundsprite.setPosition(0,backgroundY1);
        backgroundsprite1.setPosition(0,backgroundY2);
        if (backgroundY2>0)
        {
            backgroundY1=0;
            backgroundY2=backgroundY1-500;
        }
        backgroundY1+=0.1;
        backgroundY2+=0.1;

        //setting the position of obstacles
        if (Obs1Y>windowHeigth)
                {Obs1Y=0;Obs1X=getnumber(borderLeft,borderRight);score++;}
            else
                {Obs1Y=Obs1Y+gameSpeed;}
        if (Obs2Y>windowHeigth)
                {Obs2Y=0;Obs2X=getnumber(borderLeft,borderRight);score++;}
            else
                {Obs2Y=Obs2Y+gameSpeed;}
        if (Obs3Y>windowHeigth)
                {Obs3Y=0;Obs3X=getnumber(borderLeft,borderRight);score++;}
            else
                {Obs3Y=Obs3Y+gameSpeed;}
        if (Obs4Y>windowHeigth)
                {Obs4Y=0;Obs4X=getnumber(borderLeft,borderRight);score++;}
            else
                {Obs4Y=Obs4Y+gameSpeed;}

        //Game level && Increasing speed
        if(score>10 && score<18) {gameSpeed=0.3;}
        if(score>18 && score<25) {gameSpeed=0.4;}
        if(score>25 && score<35) {gameSpeed=0.4;}

        //Keyboard instructions
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        {if(playerX>borderLeft) {playerX=playerX-50;}}
                    if (event.key.code == sf::Keyboard::Right)
                        {if(playerX<borderRight){playerX=playerX+50;}}
                    if (event.key.code == sf::Keyboard::Up)
                        {if(playerY>0){playerY=playerY-50;}}
                    if (event.key.code == sf::Keyboard::Down)
                        {if(playerY<windowHeigth-70){playerY=playerY+50;}}
                }
        }

        //Collusion detection
        if (((playerX>=(Obs1X-30)) &&(playerX<=(Obs1X+30)))&&((playerY>=(Obs1Y-30))
                                                              &&(playerY)<=(Obs1Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((playerX>=(Obs2X-30)) &&(playerX<=(Obs2X+30)))&&((playerY>=(Obs2Y-30))
                                                              &&(playerY)<=(Obs2Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((playerX>=(Obs3X-30)) &&(playerX<=(Obs3X+30)))&&((playerY>=(Obs3Y-30))
                                                               &&(playerY)<=(Obs3Y+30)))
            {
                GameSound.stop();gameOver();
            };
        if (((playerX>=(Obs4X-30)) &&(playerX<=(Obs4X+30)))&&((playerY>=(Obs4Y-30))
                                                              &&(playerY)<=(Obs4Y+30)))
            {
                GameSound.stop();gameOver();
            };

        //draw all
        app.clear();
        app.draw(backgroundsprite);
        app.draw(backgroundsprite1);
        app.draw(playersprite);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        app.display();
    }
    return EXIT_SUCCESS;
}

//Game over
int gameOver()
{
    Texture gameover,troll;
        gameover.loadFromFile("data/images/over.png");
        troll.loadFromFile("data/images/troll.png");

    Sprite Gameover(gameover);
    Sprite Troll(troll);
    Troll.setPosition(10,350);

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
        }
        Font txtfont;
            txtfont.loadFromFile("data/font/xirod.ttf");
            stringscore="YOUR SCORE:"+to_string(score);
        Text text(stringscore, txtfont, 30);
            text.setPosition(210,450);
        app.clear();
        app.draw(Gameover);
        app.draw(text);
        app.draw(Troll);
        app.display();

    }

}
int getnumber(int a, int b)
    {
        static bool first = true;
        if (first)
            {
                srand( time(NULL) );
                first = false;
            }
        int result=a + rand() % (( b + 1 ) - a);
        result=(result/10)*10;
        return result;
}
