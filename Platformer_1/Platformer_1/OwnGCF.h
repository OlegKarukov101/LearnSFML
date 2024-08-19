#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// TODO:: необходимо отойти от синглтона в сторону передачи weak_ptr в конструкторы классов
/*class RenderWindowSingle
{
public:
    static RenderWindowSingle& Instance()
    {
        static RenderWindowSingle theSingleInstance;
        return theSingleInstance;
    }
    RenderWindow& Get() {
        return window;
    }
private:
    RenderWindow window = RenderWindow(VideoMode(1000, 600), L"газ2ƒ", Style::Default);
    RenderWindowSingle() {}
    RenderWindowSingle(const RenderWindowSingle& root) = delete;
    RenderWindowSingle& operator=(const RenderWindowSingle&) = delete;
};

static RenderWindow& window = RenderWindowSingle::Instance().Get();*/
//extern RenderWindow window;
struct cellka { //cell-€чейка, клетка, а cellka чисто € придумал - клеточка, €чейка.
    int i = 0, j = 0;
    cellka() {}
    cellka(int i, int j) {
        this->i = i;
        this->j = j;
    };
};
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position);
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness);
Text InitialText(Text text, Vector2f position, Color TextColor, float OutlineThikness, Color OutlineColor);
bool isPressButtonRec(cellka press, RectangleShape button);


class RecButton {
private:
    shared_ptr<RenderWindow> window;
    RectangleShape shape;
    Color color;
    bool detection = false;
    bool detectpress = false;
    bool detecttext = false;
    Color colorDetect = Color(50, 210, 40);
    bool press = false;
    Color colorPress;
    Text text;
    Text textpress;
    string s = "";
    Font font;
public:
    RecButton(shared_ptr<RenderWindow> window, Vector2f size, Vector2f position, Color color);
    RecButton(shared_ptr<RenderWindow> window, Vector2f size, Vector2f position, Color color, string str, Font font);
    void setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness);
    void setTextPress(string str, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness);
    void setDetect(Color colorDetect);
    void setDetect();
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
    shared_ptr<RenderWindow> window;
    RectangleShape diapason;
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
    dig getValue() { return value; }
    HorizontalSlider(shared_ptr<RenderWindow> window, dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, double width, Vector2f posdiaposon, Color coldiaposon, Vector2f sizeslider, Color colslider, Font font) {
        this->window = window;
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
        diapason = InitialRectangleShape(Vector2f(lenghtdiaposon, width), coldiaposon, posdiaposon);
        SliderButton = InitialRectangleShape(sizeslider, colslider, Vector2f(basevalue / coefficient + leftX, posdiaposon.y));
        this->font = font;
        textvalue = Text(RoundDig(value, 0.01), this->font, 20);
        textvalue = InitialText(textvalue, Vector2f(posdiaposon.x + lenghtdiaposon / 2 + 10, constYslider - 10), Color::Green, 4, Color::Black);
        textvalue.setStyle(Text::Bold);
    }
    HorizontalSlider(shared_ptr<RenderWindow> window, dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, Vector2f posdiaposon) {
        this->window = window;
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
        diapason = InitialRectangleShape(Vector2f(lenghtdiaposon, 10), Color::Black, posdiaposon);
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
        text.setPosition(diapason.getPosition().x - diapason.getSize().x / 2 - text.getLocalBounds().width - 20, diapason.getPosition().y - text.getLocalBounds().height / 2 - 5);
    }
    RectangleShape getButtonDiaposon() { return diapason; }
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
        if ((isPressButtonRec(cellka(Mouse::getPosition(*window).y, Mouse::getPosition(*window).x), diapason)) || (isPressButtonRec(cellka(Mouse::getPosition(*window).y, Mouse::getPosition(*window).x), SliderButton))) {
            (*this).setXSlider(Mouse::getPosition(*window).x);
        }
    }
    void Draw() {
        *window.draw(diapason);
        *window.draw(SliderButton);
        *window.draw(textvalue);
        *window.draw(text);
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
}


