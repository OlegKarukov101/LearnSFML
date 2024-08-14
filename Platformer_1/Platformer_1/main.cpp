#include "OwnGCF.h"

using namespace std;
using namespace sf;

int sz = 100;
vector<string> infmapa{     "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,  // *  cube 100*100
                            "############.............................................................................................###################################" ,
                            "############..o..........................................................................................###################################" ,
                            "############................................1.....................................################.......########..............#############" ,
                            "##################################################################################################.......########.....###......#############" ,
                            "####################################################################################################................######.....#############" ,
                            "###########..................................................2....................#########################################.......##########" ,
                            "###########.......................................................................##################..............##########......##########" ,
                            "###########.....########################################################..........############....................######......##############" ,
                            "#############....#########################################################........##########......###########..................#############" ,
                            "##############......########################################################...................#############################################" ,
                            "################.......#####################################################################################################################" ,
                            "##################..................................................................................................########################" ,
                            "###################...........2..................................................................################...............1###########" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" };
vector<vector<RectangleShape>> mapa(300, vector<RectangleShape>(300, InitialRectangleShape(Vector2f(sz, sz), Color(130, 255, 255), Vector2f(0, 0))));
pair<pair<int, int>, pair<int, int>> tep1(pair<int, int>(0, 0), pair<int, int>(0, 0));
pair<pair<int, int>, pair<int, int>> tep2(pair<int, int>(0, 0), pair<int, int>(0, 0));


void UpdateMapa(cellka globalposmapa, Vector2f localposHero) {

    //cout << globalposmapa.i <<"--"<< globalposmapa.j << endl;
    for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 14; j++) {
            mapa[i+globalposmapa.i-4][j+globalposmapa.j-7].setPosition(-localposHero.x + sz*(1+j), -localposHero.y + sz * (1 + i));
            
        }
    }
}
void DrawMapa(cellka globalposmapa) {
    for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 14; j++) {
            window.draw(mapa[i + globalposmapa.i - 4][j + globalposmapa.j - 7]);
        }
    }
}
class Hero {
private:
    cellka globalposmapa = cellka(0,0);
    bool isGround = true;
    RectangleShape shape = InitialRectangleShape(Vector2f(90, 90), Color(0, 0, 0), Vector2f(750, 450), 10, Color(220, 50, 50));
    Vector2f speed=Vector2f(0,0);
    Vector2f localpos=Vector2f(sz/2,sz/2);
public:
    Hero() {

    }
    RectangleShape getShape() {return shape;   }
    Vector2f getLocalPos()    {return localpos;}
    cellka getGlobalPosMapa(){ return globalposmapa; }
    void setSpeed(Vector2f speed)  { this->speed = speed;}
    void setGlobalPosMapa(cellka pos) { 
        globalposmapa = pos; 
    }
    void AddSpeedx(float speedx)   { 
        speed.x += speedx;  
        if (abs(speed.x) > 15) 
            speed.x -= speedx;
    }
    void AddSpeedy(float speedy)   { 
        speed.y += speedy;  
        if (abs(speed.y) > 14) speed.y -= speedy;
    }
    bool isGround_() { return isGround; }
    void Collision() {

        if (mapa[globalposmapa.i + 1][globalposmapa.j].getFillColor() == Color(255, 255, 255) && localpos.y >= sz/2) {
            isGround = true;
        }
        else isGround = false;

        //if (mapa[globalposmapa.i][globalposmapa.j + 1].getFillColor() == Color(255, 255, 255)) cout << "#"; else cout << ".";
        //if (mapa[globalposmapa.i - 1][globalposmapa.j].getFillColor() == Color(255, 255, 255)) cout << "#"; else cout << ".";
        //cout << localpos.x<<"--"<<globalposmapa.j << endl;


        if (mapa[globalposmapa.i][globalposmapa.j + 1].getFillColor() == Color(255, 255, 255) && localpos.x > sz/2 && speed.x>0) { speed.x = 0; }
        if (mapa[globalposmapa.i][globalposmapa.j - 1].getFillColor() == Color(255, 255, 255) && localpos.x < sz/2 && speed.x<0) { speed.x = 0; }
        if (mapa[globalposmapa.i - 1][globalposmapa.j].getFillColor() == Color(255, 255, 255) && localpos.y < sz/2 && speed.y<0) { speed.y = 0; }
        if (isGround && speed.y > 0) { speed.y = 0; };
    }
    void UpdateHero() {

        Collision();
        if (!isGround) speed.y += 0.2;
        else {
            if (speed.x > 0) speed.x -= 0.1;
            if (speed.x < 0) speed.x += 0.1;
        }
        Vector2f pos(0, 0);
        pos.x += speed.x; pos.y += speed.y;
        if (speed.x < 0) {

        }
        if(pos.x>0) {
            globalposmapa.j += (int)(pos.x + localpos.x) / sz; }
        else { globalposmapa.j += (int)(pos.x + -(sz-localpos.x)) / sz; }
        if (pos.y > 0) { globalposmapa.i += (int)(pos.y + localpos.y) / sz; }
        else { globalposmapa.i += (int)(pos.y + -(sz - localpos.y)) / sz; }
        float signx=0, signy=0;
        if (pos.x != 0)  signx = (pos.x / abs(pos.x));  if(pos.y!=0) signy = (pos.y / abs(pos.y)); 
        localpos.x += pos.x + signx*(sz * floor((pos.x) / sz));  localpos.x = localpos.x - sz*floor(localpos.x/sz); 
        localpos.y += pos.y + signy*(sz * floor((pos.y) / sz));  localpos.y = localpos.y - sz*floor(localpos.y/sz); 
        
        pair<int, int> pr(globalposmapa.i, globalposmapa.j);
        if (tep1.first == pr) { 
            globalposmapa.i = tep1.second.first;
            globalposmapa.j = tep1.second.second;
        }
        //else if (tep1.second == pr) { shape.setPosition(mapa[tep1.first.first][tep1.first.second].getPosition()); }
        else if (tep2.first == pr) { 
            globalposmapa.i = tep2.second.first;
            globalposmapa.j = tep2.second.second;
        }
        //else if (tep2.second == pr) { shape.setPosition(mapa[tep2.first.first][tep2.first.second].getPosition()); }*/
    }
    ~Hero() {

    }
};

int main()
{

    
    window.setVerticalSyncEnabled(true);
    srand((unsigned int)time(0));
    RectangleShape fon = InitialRectangleShape(Vector2f(1300, 700),Color(130,255,255,0),Vector2f(750,450),sz,Color(50,220,50));
    Hero hero;



    
    Font fontDays2, fontImpact2;
    if (fontDays2.loadFromFile("days2.ttf")) cout << "YEES fontDays2\n";
    if (fontImpact2.loadFromFile("impact2.ttf")) cout << "YEES fontImpact2\n";
    Texture texture1;
    //if (texture1.loadFromFile("texture1.jpeg",IntRect(10,10,128,128))) cout << "YEEES texture \n";
    if (texture1.loadFromFile("texture2.jpeg",IntRect(0,10,128,128))) cout << "YEEES texture \n";
    //if (texture1.loadFromFile("texture1.jpeg",IntRect(10,10,128,128))) cout << "YEEES texture \n";
    texture1.setSmooth(true);


    
    for (int i = 0; i < infmapa.size(); i++) {
        for (int j = 0; j < infmapa[i].size(); j++) {
            if (infmapa[i][j] == '#') {
                mapa[i][j].setFillColor(Color(255, 255, 255));
                mapa[i][j].setTexture(&texture1);
            }
            if (infmapa[i][j] == 'o') {
                hero.setGlobalPosMapa(cellka(i, j));
            }
            if (infmapa[i][j] == '1') {
                if (tep1.first == pair<int, int>(0, 0))
                    tep1.first = pair<int, int>(i, j);
                else tep1.second = pair<int, int>(i, j);
                mapa[i][j].setFillColor(Color(220, 50, 50));
            }
            if (infmapa[i][j] == '2') {
                if (tep2.second == pair<int, int>(0, 0))
                    tep2.second = pair<int, int>(i, j);
                else tep2.first = pair<int, int>(i, j);
                mapa[i][j].setFillColor(Color(50, 50, 220));
            }
        }
    }
    


    
    


    //commit 2
    //tugtjgutur
    //capusta 3
    Clock clock;
    double time = clock.getElapsedTime().asSeconds();

    int frame = 0;
    while (window.isOpen())
    {
        frame %= 100000;
        frame++;
        time = clock.getElapsedTime().asSeconds();
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Left) {
                    
                }
                break;
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
             if(hero.isGround_()) 
             hero.AddSpeedx(-0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            if(hero.isGround_()) 
            hero.AddSpeedx(0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            hero.AddSpeedy(0.5);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (hero.isGround_())
            hero.AddSpeedy(-5);
        }
        hero.UpdateHero();
        UpdateMapa(hero.getGlobalPosMapa(), hero.getLocalPos());

        DrawMapa(hero.getGlobalPosMapa());
        window.draw(hero.getShape());
        window.draw(fon);
        window.display();
    }
    return 0;
}