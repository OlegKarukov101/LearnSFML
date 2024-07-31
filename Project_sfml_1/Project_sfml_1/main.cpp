/*#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>*/
#include "OwnGCF.h"

//Просто комментарий для гита Жопа коня

using namespace std;
using namespace sf;

//RenderWindow window(VideoMode(1000, 600), L"газ2Д", Style::Default);
RectangleShape area(Vector2f(700, 400));
int N;
int V;
int T;
float p;

const double PI = 3.141592653589793;
/*struct cellka { //cell-ячейка, клетка, а cellka чисто я придумал - клеточка, ячейка.
    int i = 0, j = 0;
    cellka() {}
    cellka(int i, int j) {
        this->i = i;
        this->j = j;
    };
};
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position) {
    RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);
    return shape;
}
Text InitialText(Text text, Vector2f position, Color TextColor, float OutlineThikness, Color OutlineColor) {
    Text text_(text);
    text_.setPosition(position);
    text_.setFillColor(TextColor);
    text_.setOutlineThickness(OutlineThikness);
    text_.setOutlineColor(OutlineColor);
    return text_;
}
bool isPressButtonRec(cellka press, RectangleShape button) {
    if (abs(press.i - button.getPosition().y) < button.getSize().y / 2 && abs(press.j - button.getPosition().x) < button.getSize().x / 2) {
        return true;
    }
    //cout << abs(press.i - button.getPosition().y) << "  " << abs(press.j - button.getPosition().x) << "\n";
    return false;
}
class RecButton {
private:
    RectangleShape shape;
    Color color;
    bool detection;
    Color colorDetect;
    bool press;
    Color colorPress;
    Text text;
    string s;
    Font font;
public:
    RecButton(Vector2f size, Vector2f position, Color color) {
        shape = InitialRectangleShape(size, color, position);
        this->color = color;
        press = false;
        colorDetect = Color(100, 100, 255);
        detection = false;
        s = "";
    }
    RecButton(Vector2f size, Vector2f position, Color color, string str, Font font) {
        this->font = font;
        shape = InitialRectangleShape(size, color, position);
        this->color = color;
        press = false;
        colorDetect = Color(100, 100, 255);
        detection = false;
        s = str;
        text.setString(s);
        text.setFont(this->font);
        text.setCharacterSize(45);
        text.setStyle(Text::Bold);
        text = InitialText(text, Vector2f(300, 300), Color(255, 255, 255), 4, Color(0, 0, 0));
        text.setPosition(shape.getPosition().x - shape.getSize().x / 2 + (shape.getSize().x - text.getLocalBounds().width) / 2, shape.getPosition().y - shape.getSize().y / 2 + (shape.getSize().y - text.getLocalBounds().height) / 2 - shape.getSize().y * 0.1);
    }
    void setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness) {
        this->font = font;
        s = str;
        text.setString(s);
        text.setFont(this->font);
        text.setCharacterSize(CharacterSize);
        text.setStyle(Text::Bold);
        text = InitialText(text, Vector2f(300, 300), textcolor, WidthThikness, colorThikness);
        text.setPosition(shape.getPosition().x - shape.getSize().x / 2 + (shape.getSize().x - text.getLocalBounds().width) / 2, shape.getPosition().y - shape.getSize().y / 2 + (shape.getSize().y - text.getLocalBounds().height) / 2 - shape.getSize().y * 0.1);
    }
    void setDetect(Color colorDetect) {
        this->colorDetect = colorDetect;
        detection = true;
    }
    void turnOnDetection() { detection = true; }
    void turnOffDetection() { detection = false; }
    bool isIndicate() {
        cellka press = cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x);
        if (abs(press.i - shape.getPosition().y) < shape.getSize().y / 2 && abs(press.j - shape.getPosition().x) < shape.getSize().x / 2) {
            return true;
        }
        return false;
    }
    void setColorPress(Color colorPress) {
        this->colorPress = colorPress;
    }
    void Press() { press = !press; }
    void isPress() {
        if (isIndicate()) {
            Press();
        }
    }
    bool getPress() {
        return press;
    }
    void Draw() {
        if (detection && !press) {
            if (isIndicate()) {
                shape.setFillColor(colorDetect);
            }
            else shape.setFillColor(color);
        }
        else
            if (press) shape.setFillColor(colorPress);
            else shape.setFillColor(color);
        window.draw(shape);
        if (s != "") {
            window.draw(text);
        }
    }
};


template<typename dig>
concept isdig = requires(dig d) {
    d + d;
    d * d;
};
template<isdig dig>
string RoundDig(dig d, double precision);
template<isdig dig>
bool isInteger(dig d);
template<isdig dig>
class HorizontalSlider {
private:
    RectangleShape diaposon;
    RectangleShape SliderButton;
    Text textvalue;
    Font font;
    dig* quantity;
    double leftX, rightX, constYslider;
    double coefficient;
    dig diaposonvalue, minvalue, maxvalue;
    dig value;
    Text text;
    Font textfont;
    string s;
public:
    double getValue() { return value; }
    HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, double width, Vector2f posdiaposon, Color coldiaposon, Vector2f sizeslider, Color colslider, Font font) {
        this->quantity = &quantity;
        *(this->quantity) = basevalue;
        this->minvalue = minvalue;
        this->maxvalue = maxvalue;
        this->diaposonvalue = maxvalue - minvalue;
        this->coefficient = diaposonvalue / lenghtdiaposon;
        this->value = ceil(basevalue * 100) / 100;
        leftX = posdiaposon.x - lenghtdiaposon / 2;
        rightX = posdiaposon.x + lenghtdiaposon / 2;
        this->diaposonvalue = diaposonvalue;
        this->constYslider = posdiaposon.y;
        diaposon = InitialRectangleShape(Vector2f(lenghtdiaposon, width), coldiaposon, posdiaposon);
        SliderButton = InitialRectangleShape(sizeslider, colslider, Vector2f(basevalue / coefficient + leftX, posdiaposon.y));
        this->font = font;
        textvalue = Text(RoundDig(value, 0.01), this->font, 20);
        textvalue = InitialText(textvalue, Vector2f(posdiaposon.x + lenghtdiaposon / 2 + 10, constYslider - 10), Color::Green, 4, Color::Black);
        textvalue.setStyle(Text::Bold);
    }
    HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, Vector2f posdiaposon) {
        this->quantity = &quantity;
        *(this->quantity) = basevalue;
        this->minvalue = minvalue;
        this->maxvalue = maxvalue;
        this->diaposonvalue = maxvalue - minvalue;
        this->coefficient = diaposonvalue / lenghtdiaposon;
        if (basevalue < minvalue) basevalue = minvalue;
        if (basevalue > maxvalue) basevalue = maxvalue;
        this->value = ceil(basevalue * 100) / 100;
        leftX = posdiaposon.x - lenghtdiaposon / 2;
        rightX = posdiaposon.x + lenghtdiaposon / 2;
        this->diaposonvalue = diaposonvalue;
        this->constYslider = posdiaposon.y;
        diaposon = InitialRectangleShape(Vector2f(lenghtdiaposon, 10), Color::Black, posdiaposon);
        SliderButton = InitialRectangleShape(Vector2f(20, 40), Color::Blue, Vector2f((basevalue - minvalue) / coefficient + leftX, posdiaposon.y));
        if (font.loadFromFile("days2.ttf"));//cout << "YEES fontDays2\n";
        textvalue = Text(RoundDig(value, 0.01), font, 20);
        textvalue = InitialText(textvalue, Vector2f(posdiaposon.x + lenghtdiaposon / 2 + 10, constYslider - 10), Color::Green, 4, Color::Black);
        textvalue.setStyle(Text::Bold);
    }
    void setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness) {
        textfont = font;
        s = str;
        text.setString(s);
        text.setFont(textfont);
        text.setCharacterSize(CharacterSize);
        text.setStyle(Text::Bold);
        text = InitialText(text, Vector2f(300, 300), textcolor, WidthThikness, colorThikness);
        text.setPosition(diaposon.getPosition().x - diaposon.getSize().x / 2 - text.getLocalBounds().width - 100, diaposon.getPosition().y - text.getLocalBounds().height / 2);
    }
    RectangleShape getButtonDiaposon() { return diaposon; }
    RectangleShape getButtonSlider() { return SliderButton; }
    Text getText() { return textvalue; }
    void setXSlider(dig Xslider) {
        if (Xslider <= leftX)  Xslider = leftX;
        if (Xslider >= rightX)
            Xslider = rightX;
        this->value = minvalue + ceil(((Xslider - leftX) * coefficient) * 100) / 100;
        if (value < minvalue) value = minvalue;
        if (value > maxvalue) value = maxvalue;
        *quantity = value;
        Xslider = (value - minvalue) / coefficient + leftX;
        SliderButton.setPosition(Vector2f(Xslider, constYslider));
        textvalue.setString(RoundDig(value, 0.01));
    }
    void setValue(dig мvalue) {
        value = мvalue;
        if (value < minvalue) value = minvalue;
        if (value > maxvalue) value = maxvalue;
        *quantity = value;
        double Xslider = (value - minvalue) / coefficient + leftX;
        SliderButton.setPosition(Vector2f(Xslider, constYslider));
        textvalue.setString(RoundDig(value, 0.01));
    }
    void isPress() {
        //вынести гет позишен мышки в переменную
        if ((isPressButtonRec(cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x), diaposon)) || (isPressButtonRec(cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x), SliderButton))) {
            (*this).setXSlider(Mouse::getPosition(window).x);
        }
    }
    void Draw() {
        window.draw(diaposon);
        window.draw(SliderButton);
        window.draw(textvalue);
        window.draw(text);
    }

};
template<isdig dig>
string RoundDig(dig d, double precision) {
    if (isInteger(d)) return to_string(d);
    int n = (int)(1.0 / precision);
    string s = to_string(ceil(d * n) / n);
    string ss = "";
    int index = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != '.') ss += s[i];
        else {
            ss += s[i];
            index = i;
            break;
        }
    }
    for (int i = 0; i < to_string(n).size() - 1; i++) {
        ss += s[index + i + 1];
    }
    return ss;
}
template<isdig dig>
bool isInteger(dig d) {
    string s = to_string(d);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
            return false;
        }
    }
    return true;
}*/

double Distance(Vector2f point1, Vector2f point2) {
    double x1 = point1.x; double y1 = point1.y;
    double x2 = point2.x; double y2 = point2.y;
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}
double DegreesToRadians(double degrees) {
    return degrees * (PI / 180);
}

class ball {
private:
    CircleShape shape;
    RectangleShape line;
    float weight;
    float speed;//speed 0 - 200
    float speedx,speedy;
    float strenght;
    float acceleration;
    float a, b;//ax=by;
    int sign;
public:
    ball(){}
    ball(float radius, Color col, Vector2f Position) {
        shape = CircleShape(radius);
        shape.setFillColor(col);
        shape.setOrigin(Vector2f(radius,radius));
        shape.setPosition(Position);
        weight = 1; speed = 0;
        speedx = 0; speedy = 0;
        strenght = 0;
        acceleration = 0;
        a = 1; b = 1; sign = 1;
        
    }
    CircleShape getShape() {
        return shape;
    }
    void SpeedToColor() {
        if (speed < 30) { 
            shape.setFillColor(Color(speed*1.5+10, speed*1.5+10, speed*8+15)); 
        }
        else if (speed < 50) { shape.setFillColor(Color(speed*5, speed*5, speed * 5));}
        else{ 
            shape.setFillColor(Color(speed * 1.2+15,50,50)); }
    }
    void RecountSpeedXY() {
        if (a != 0 && b != 0) {
            float k = b / a;
            speedx = sign * sqrt(speed * speed / (1 + k * k));
            speedy = k * speedx;
        }
        else if (a == 0) {
            speedy = speed;//x=0
            speedx = 0;
        }
        else if(b==0) {
            speedy = 0;   //y=0;
            speedx = speed;
        }
    }
    void move() {
        Vector2f pos = shape.getPosition();
        pair<bool,bool> check = CheckCollision();
        if (check.first)  { pos.x += speedx * 0.1; }
        if (check.second) { pos.y += speedy * 0.1; }
        shape.setPosition(pos);
    }
    void setDirection(Vector2f pointTarget) {
        float x1 = this->shape.getPosition().x;
        float y1 = this->shape.getPosition().y;
        float x2 = pointTarget.x;
        float y2 = pointTarget.y;
        a = x2 - x1;
        b = y2 - y1;
        if (x2 > x1) sign = 1; else sign = -1;
        RecountSpeedXY();
    }
    void setDirRotate(int rotate) {
        if (rotate % 90 != 0 || rotate % 180 == 0) {
            float k = tan(DegreesToRadians(rotate));
            a = 1;
            b = a * k; // tan rotate = 0 -> y=0;
        }
        else {
            a = 0;
            b = 1; //x=0;
        }
        RecountSpeedXY();
    }

    pair<bool,bool> CheckCollision() { //Collision with not pos behind the wall
        pair<bool, bool> res(1,1);
        Vector2f pos = shape.getPosition();
        Vector2f areapos = area.getPosition();
        Vector2f areaSize = area.getSize();
        float spx = speedx*0.1; float spy = speedy*0.1;
        Vector2f posnew = pos;
        if (((pos.x+spx) - areapos.x) < 1) { //left wall
            a *= -1; sign *= -1;
            speedx *= -1;
            posnew.x = areapos.x + ((pos.x + spx) - areapos.x);
            res.first = 0;
        }
        if (((areapos.x + areaSize.x) - (pos.x+spx)) < 1) { //right wall
            a *= -1; sign *= -1;
            speedx *= -1;
            posnew.x = (areapos.x + areaSize.x) - (areapos.x + areaSize.x - (pos.x + spx));
            res.first = 0;
        }  
        /*if (((pos.y + spy) - (areapos.y + areaSize.y)) < 1) { // bottom 
            a *= -1;
            speedy *= -1;
            posnew.y = (areapos.y + areaSize.y) - ((pos.y + spy) - (areapos.y + areaSize.y));
            res.second = 0;
        }
        if ((areapos.y - (pos.y+spy)) < 1) {  // top
            a *= -1;
            speedy *= -1;
            posnew.y = areapos.y + (areapos.y - (pos.y + spy));
            res.second = 0;
        }*/
        if (((areapos.y + areaSize.y)- (pos.y + spy)) < 1) { // bottom 
            a *= -1;
            speedy *= -1;
            posnew.y = (areapos.y + areaSize.y) - ((areapos.y + areaSize.y) - (pos.y + spy));
            res.second = 0;
        }
        if (((pos.y + spy) - areapos.y) < 1) {  // top
            a *= -1;
            speedy *= -1;
            posnew.y = areapos.y + ((pos.y + spy) - areapos.y);
            res.second = 0;
        }
        shape.setPosition(posnew);
        return res;
    }
    void setSpeed(int speed) { 
        this->speed = abs(speed); 
        SpeedToColor();
        RecountSpeedXY();
    }
    void setSpeedXY(int speedx, int speeedy) { 
        if (speedx < 0) sign = -1;
        this->speedx = speedx; 
        this->speedy = speedy;
        speed = sqrt(speedx*speedx+speedy*speedy);
        SpeedToColor();
    }
    void setPositionBall(Vector2f pos) {
        shape.setPosition(pos);
    }
};
HorizontalSlider<int> sliderV(V, 1000, 500, 2000, 200, Vector2f(620, 250));
int main()
{
    V = 1000;
    

    window.setVerticalSyncEnabled(true);
    srand((unsigned int)time(0));

    
    area.setFillColor(Color(20,20,20));
    area.setOutlineThickness(3);
    area.setOutlineColor(Color(255, 255, 255));
    area.setPosition(360-350,350-200);
    


    Font fontDays2, fontImpact2;
    if (fontDays2.loadFromFile("days2.ttf")) cout << "YEES fontDays2\n";
    if (fontImpact2.loadFromFile("impact2.ttf")) cout << "YEES fontImpact2\n";
    sliderV.setText("V", fontImpact2, 50, Color(255, 255, 255), 3, Color(0, 0, 0));

    Clock clock;
    double time = clock.getElapsedTime().asMilliseconds();
    
    vector<ball> vec(200, ball(3, Color(240, 240, 240), Vector2f(300,400)));
    int jht = 1;
    for (int i = 0; i < vec.size(); i++) {
        vec[i].setDirRotate(jht*rand()%90);
        vec[i].setSpeed(20+rand()%180);
        Vector2f areapos = area.getPosition();
        Vector2f areaSize = area.getSize();
        vec[i].setPositionBall(Vector2f(areapos.x + rand() % ((int)areaSize.x), areapos.y + rand() % ((int)areaSize.y)));
        jht *= -1;
    }
    int frame = 0;
    while (window.isOpen())
    {   
        frame %= 100000;
        frame++;
        time = clock.getElapsedTime().asMilliseconds();
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            sliderV.isPress();

        }
        time = clock.getElapsedTime().asMilliseconds();

        for (int i = 0; i < vec.size(); i++) {
            vec[i].move();
        }
        //cout << "frame"<<endl;
        window.clear(Color(0,0,0));
        window.draw(area);
        for (int i = 0; i < vec.size(); i++) {
            vec[i].move();
            if(frame%1==0)window.draw(vec[i].getShape());
        }
        window.display();
        clock.restart();
    }
    return 0;
}