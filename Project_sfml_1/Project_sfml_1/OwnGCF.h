#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// И это тоже комментарий для гита Бла

RenderWindow window(VideoMode(1000, 600), L"газ2Д", Style::Default);

struct cellka { //cell-ячейка, клетка, а cellka чисто я придумал - клеточка, ячейка.
    int i = 0, j = 0;
    cellka() {}
    cellka(int i, int j) {
        this->i = i;
        this->j = j;
    };
};
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position);
Text InitialText(Text text, Vector2f position, Color TextColor, float OutlineThikness, Color OutlineColor);
bool isPressButtonRec(cellka press, RectangleShape button);


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
    RecButton(Vector2f size, Vector2f position, Color color);
    RecButton(Vector2f size, Vector2f position, Color color, string str, Font font);
    void setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness);
    void setDetect(Color colorDetect);
    void turnOnDetection();
    void turnOffDetection();
    bool isIndicate();
    void setColorPress(Color colorPress);
    void Press();
    void isPress();
    bool getPress();
    void Draw();
};


template<typename dig>
concept isdig = requires(dig d) {
    d + d;
    d* d;
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
    double getValue();
    HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, double width, Vector2f posdiaposon, Color coldiaposon, Vector2f sizeslider, Color colslider, Font font);
    HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, Vector2f posdiaposon);
    void setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness);
    RectangleShape getButtonDiaposon();
    RectangleShape getButtonSlider();
    Text getText();
    void setXSlider(dig Xslider);
    void setValue(dig мvalue);
    void isPress();
    void Draw();
};


