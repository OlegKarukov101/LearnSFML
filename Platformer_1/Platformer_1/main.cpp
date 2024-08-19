#include "OwnGCF.h"
#include "Physics.h"
#include "ParametrsGame.h"
#include "ObjectMapa.h"

using namespace std;
using namespace sf;



vector<string> infmapa{     "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,  // *  cube 100*100 
                            "############.............................................................................................###################################" ,
                            "############.............................................................................................###################################" ,
                            "############................................1.....................................################.......########..............#############" ,
                            "########################################........######.......#####################################.......########.....###......#############" ,
                            "########################################.....................#######################################................######.....#############" ,
                            "###########................................###..........###..2....................#########################################.......##########" ,
                            "###########.......................................................................##################..............##########......##########" ,
                            "###########.....#########################.....#####.........############..........############....................######......##############" ,
                            "#############....######################...#............###################........##########......###########..................#############" ,
                            "##############......###################....#.............####################...................#############################################" ,
                            "################......o################.........#####....###################################################################################" ,
                            "##################.......................####.......................................................................########################" ,
                            "###################...........2..................................................................################...............1###########" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" ,
                            "############################################################################################################################################" };

vector<vector<Block>> mapa(300, vector<Block>(300,Block(Color(130,255,255))));
pair<pair<int, int>, pair<int, int>> tep1(pair<int, int>(0, 0), pair<int, int>(0, 0));
pair<pair<int, int>, pair<int, int>> tep2(pair<int, int>(0, 0), pair<int, int>(0, 0));


void UpdateMapa(cellka globalposmapa, Vector2f localposHero) {

    //cout << globalposmapa.i <<"--"<< globalposmapa.j << endl;
    for (int i = 0; i <= Pr::lengthi; i++) { //9 16
        for (int j = 0; j <= Pr::lengthj; j++) {
            mapa[i + globalposmapa.i - (Pr::lengthi)/2][j + globalposmapa.j - (Pr::lengthj-1)/2].setPosition(Vector2f(-localposHero.x + Pr::sz * (1 + j), -localposHero.y + Pr::sz * (1 + i)));
            
        }
    }
}
void DrawMapa(shared_ptr<RenderWindow> window, cellka globalposmapa) {
    for (int i = 0; i <= Pr::lengthi; i++) {
        for (int j = 0; j <= Pr::lengthj; j++) {
            if(mapa[i + globalposmapa.i - (Pr::lengthi) / 2][j + globalposmapa.j - (Pr::lengthj) / 2].getFillColor()==Color(255,255,255))
            (*window).draw(mapa[i + globalposmapa.i - (Pr::lengthi) / 2][j + globalposmapa.j - (Pr::lengthj) / 2].getShape());
        }
    }
}
class Hero {
private:
    shared_ptr<RenderWindow> window;
    cellka globalposmapa = cellka(0,0);
    bool isGround = true;
    Vector2f size=Vector2f(Pr::sz/2-5,Pr::sz/2-5);
    RectangleShape shape = InitialRectangleShape(Vector2f(Pr::sz-10, Pr::sz-10), Color(0, 0, 0), Vector2f(((Pr::lengthj-1)/2) * Pr::sz+size.x, ((Pr::lengthi) / 2) * Pr::sz+size.y), 10, Color(220, 50, 50));
    Vector2f speed=Vector2f(0,0);
    Vector2f localpos=Vector2f(Pr::sz/2,Pr::sz/2);
public:
    Hero(shared_ptr<RenderWindow> window) {
        this->window = window;
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
        if (abs(speed.x) > Physics::maxSpeedx) 
            speed.x -= speedx;
    }
    void AddSpeedy(float speedy)   { 
        speed.y += speedy;  
        if (abs(speed.y) > Physics::maxSpeedy) speed.y -= speedy;
    }
    bool isGround_() { return isGround; }
    void Collision() {
        cellka gl = globalposmapa;
        Vector2f loc = localpos;
        //Vector2f touchTL(localpos.x - size.x, localpos.y - size.y), touchTR(localpos.x + size.x, localpos.y - size.y);
        //Vector2f touchBL(localpos.x - size.x, localpos.y + size.y), touchBR(localpos.x + size.x, localpos.y + size.y);
        cellka glTL = ReCountGlobalPos(gl, loc, Vector2f(-size.x, -size.y));
        cellka glTR = ReCountGlobalPos(gl, loc, Vector2f(+size.x, -size.y));
        cellka glBL = ReCountGlobalPos(gl, loc, Vector2f(-size.x, +size.y));
        cellka glBR = ReCountGlobalPos(gl, loc, Vector2f(+size.x, +size.y));
        Vector2f locTL = ReCountLocalPos(loc, Vector2f(-size.x, -size.y));
        Vector2f locTR = ReCountLocalPos(loc, Vector2f(+size.x, -size.y));
        Vector2f locBL = ReCountLocalPos(loc, Vector2f(-size.x, +size.y));
        Vector2f locBR = ReCountLocalPos(loc, Vector2f(+size.x, +size.y));
        if (locBL.y == 99) {
            int a =0 ;
        }
        bool CollisionTL_T = mapa[glTL.i - 1][glTL.j].getFillColor() == Color(255, 255, 255) && (locTL.y+speed.y) < 1; 
        bool CollisionTL_L = mapa[glTL.i][glTL.j - 1].getFillColor() == Color(255, 255, 255) && (locTL.x+speed.x) < 1;

        bool CollisionTR_T = mapa[glTR.i - 1][glTR.j].getFillColor() == Color(255, 255, 255) && (locTR.y+speed.y) < 1;
        bool CollisionTR_R = mapa[glTR.i][glTR.j + 1].getFillColor() == Color(255, 255, 255) && (Pr::sz-locTR.x-speed.x) < 1;

        bool CollisionBL_B = mapa[glBL.i + 1][glBL.j].getFillColor() == Color(255, 255, 255) && (Pr::sz-locBL.y-speed.y) < 1;
        bool CollisionBL_L = mapa[glBL.i][glBL.j - 1].getFillColor() == Color(255, 255, 255) && (locBL.x+speed.x) < 1;

        bool CollisionBR_B = mapa[glBR.i + 1][glBR.j].getFillColor() == Color(255, 255, 255) && (Pr::sz-locBR.y-speed.y) < 1;
        bool CollisionBR_R = mapa[glBR.i][glBR.j + 1].getFillColor() == Color(255, 255, 255) && (Pr::sz-locBR.x) < 1;

        bool bottomCollision = CollisionBL_B || CollisionBR_B;
        bool topCollision = CollisionTL_T || CollisionTR_T;
        bool leftCollision = CollisionTL_L || CollisionBL_L;
        bool rightCollision = CollisionTR_R || CollisionBR_R;
        if (bottomCollision) {
            isGround = true;
        }
        else isGround = false;

        if (rightCollision && speed.x > 0) { speed.x = 0; }
        if (leftCollision && speed.x < 0) { speed.x = 0; }
        if (topCollision && speed.y < 0) { speed.y = 0; }
        if (isGround && speed.y > 0) { speed.y = 0; };

        /*if (rightWall && (Pr::sz - (localpos.x + speed.x)) < size.x && speed.x>0) { speed.x = (Pr::sz - localpos.x) - size.x; }
        if (leftWall && (localpos.x+speed.x) < size.x && speed.x<0) { speed.x = -localpos.x+size.x; }
        if (topWall && (localpos.y+speed.y) < size.y && speed.y<0) { speed.y = -localpos.y+size.y; }
        if (isGround && speed.y > 0) { speed.y = (Pr::sz-localpos.y)-size.y; };*/
        cout << locBL.y <<" "<<locBR.y<< endl;
    }
    Vector2f ReCountLocalPos(Vector2f localpos, Vector2f speed) {
        int sz = Pr::sz;
        float signx = 0, signy = 0;
        if (speed.x != 0)  signx = (speed.x / abs(speed.x));  if (speed.y != 0) signy = (speed.y / abs(speed.y));
        localpos.x += speed.x + signx * (sz * floor((speed.x) / sz));  localpos.x = localpos.x - sz * floor(localpos.x / sz);
        localpos.y += speed.y + signy * (sz * floor((speed.y) / sz));  localpos.y = localpos.y - sz * floor(localpos.y / sz);
        return localpos;
    }
    cellka ReCountGlobalPos(cellka globalposmapa, Vector2f localpos, Vector2f speed) {
        int sz = Pr::sz;
        if (speed.x > 0) {
            globalposmapa.j += ((int)(speed.x + localpos.x) / sz);
        }
        else { globalposmapa.j += ((int)(speed.x + -(sz - localpos.x)) / sz); }
        if (speed.y > 0) { globalposmapa.i += ((int)(speed.y + localpos.y) / sz); }
        else { globalposmapa.i += ((int)(speed.y + -(sz - localpos.y)) / sz); }
        return globalposmapa;
    }
    void UpdateHero() {

        
        if (!isGround) {
            speed.y += Physics::gravity;
            if (speed.x != 0) {
                if (speed.x > 0) 
                    speed.x -= Physics::airFriction; 
                
                else if (speed.x < 0) 
                    speed.x += Physics::airFriction;
            }
        }
        else {
            if (speed.x != 0) {
                if (speed.x > 0) 
                    speed.x -= Physics::groundFriction;
                else if (speed.x < 0) 
                    speed.x += Physics::groundFriction;

                if (abs(speed.x) < Physics::groundFriction) speed.x = 0;
            }
        }
        Collision();
        int sz = Pr::sz;

        /*if (speed.x>0) {
            globalposmapa.j += floor((speed.x + localpos.x) / sz); }
        else { globalposmapa.j += floor((speed.x + -(sz-localpos.x)) / sz); }
        if (speed.y > 0) { globalposmapa.i += floor((speed.y + localpos.y) / sz); }
        else { globalposmapa.i += floor((speed.y + -(sz - localpos.y)) / sz); }*/
        /*float signx = 0, signy = 0;
        if (speed.x != 0)  signx = (speed.x / abs(speed.x));  if(speed.y!=0) signy = (speed.y / abs(speed.y));
        localpos.x += speed.x + signx*(sz * floor((speed.x) / sz));  localpos.x = localpos.x - sz*floor(localpos.x/sz);
        localpos.y += speed.y + signy*(sz * floor((speed.y) / sz));  localpos.y = localpos.y - sz*floor(localpos.y/sz);*/
        globalposmapa = ReCountGlobalPos(globalposmapa, localpos, speed);
        localpos = ReCountLocalPos(localpos, speed);
        
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
    void Draw() { 
        if (window) {
            window->draw(shape);
        }
    }
    ~Hero() {

    }
};

int main()
{
    shared_ptr<RenderWindow> window_ptr = make_shared<RenderWindow>(VideoMode(Pr::windowSizex, Pr::windowSizey), L"Платформер", Style::Default);
    
    window_ptr->setVerticalSyncEnabled(true);
    srand((unsigned int)time(0));
    RectangleShape contour = InitialRectangleShape(Vector2f(Pr::windowSizex-2*Pr::sz, Pr::windowSizey-2*Pr::sz),Color(130,255,255,0),Vector2f(Pr::windowSizex/2,Pr::windowSizey/2),Pr::sz,Color(50,220,50));
    RectangleShape fon = InitialRectangleShape(Vector2f(Pr::windowSizex, Pr::windowSizey), Color(130, 255, 255), Vector2f(Pr::windowSizex / 2, Pr::windowSizey / 2));
    Hero hero(window_ptr);



    
    Font fontDays2, fontImpact2;
    if (fontDays2.loadFromFile("days2.ttf")) cout << "YEES fontDays2\n";
    if (fontImpact2.loadFromFile("impact2.ttf")) cout << "YEES fontImpact2\n";
    Texture texture1;
    //if (texture1.loadFromFile("texture1.jpeg",IntRect(10,10,128,128))) cout << "YEEES texture \n";
    if (texture1.loadFromFile("texture5.jpeg")) cout << "YEEES texture \n";
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
    //main capusta
    Clock clock;
    float time = (float)clock.getElapsedTime().asSeconds();

    int frame = 0;
    while (window_ptr->isOpen())
    {
        frame %= 100000;
        frame++;
        time = clock.getElapsedTime().asSeconds();
        Event event;
        while (window_ptr->pollEvent(event))
        {
            switch (event.type) {
            case Event::Closed:
                window_ptr->close();
                break;
            case Event::MouseButtonReleased:
                if (event.mouseButton.button == Mouse::Left) {
                    
                }
                break;
            }

        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
             //if(hero.isGround_()) 
             hero.AddSpeedx(-Physics::Speedx);
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            //if(hero.isGround_()) 
            hero.AddSpeedx(Physics::Speedx);
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            hero.AddSpeedy(2);
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (hero.isGround_())
            hero.AddSpeedy(-Physics::jumpSpeed);
        }
        hero.UpdateHero();
        UpdateMapa(hero.getGlobalPosMapa(), hero.getLocalPos());
        window_ptr->clear();
        window_ptr->draw(fon);
        DrawMapa(window_ptr,hero.getGlobalPosMapa());
        hero.Draw();
        window_ptr->draw(contour);
        window_ptr->display();
    }
    return 0;
}