#pragma once
#include "OwnGCF.h"

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

    RecButton::RecButton(Vector2f size, Vector2f position, Color color) {
        shape = InitialRectangleShape(size, color, position);
        this->color = color;
        press = false;
        colorDetect = Color(100, 100, 255);
        detection = false;
        s = "";
    }
    RecButton::RecButton(Vector2f size, Vector2f position, Color color, string str, Font font) {
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
    void RecButton::setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness) {
        this->font = font;
        s = str;
        text.setString(s);
        text.setFont(this->font);
        text.setCharacterSize(CharacterSize);
        text.setStyle(Text::Bold);
        text = InitialText(text, Vector2f(300, 300), textcolor, WidthThikness, colorThikness);
        text.setPosition(shape.getPosition().x - shape.getSize().x / 2 + (shape.getSize().x - text.getLocalBounds().width) / 2, shape.getPosition().y - shape.getSize().y / 2 + (shape.getSize().y - text.getLocalBounds().height) / 2 - shape.getSize().y * 0.1);
    }
    void RecButton::setDetect(Color colorDetect) {
        this->colorDetect = colorDetect;
        detection = true;
    }
    void RecButton::turnOnDetection() { detection = true; }
    void RecButton::turnOffDetection() { detection = false; }
    bool RecButton::isIndicate() {
        cellka press = cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x);
        if (abs(press.i - shape.getPosition().y) < shape.getSize().y / 2 && abs(press.j - shape.getPosition().x) < shape.getSize().x / 2) {
            return true;
        }
        return false;
    }
    void RecButton::setColorPress(Color colorPress) {
        this->colorPress = colorPress;
    }
    void RecButton::Press() { press = !press; }
    void RecButton::isPress() {
        if (isIndicate()) {
            Press();
        }
    }
    bool RecButton::getPress() {
        return press;
    }
    void RecButton::Draw() {
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

    template<isdig dig>
    double HorizontalSlider<dig>::getValue() { return value; }
    template<isdig dig>
    HorizontalSlider<dig>::HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, double width, Vector2f posdiaposon, Color coldiaposon, Vector2f sizeslider, Color colslider, Font font) {
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
    template<isdig dig>
    HorizontalSlider<dig>::HorizontalSlider(dig& quantity, dig basevalue, dig minvalue, dig maxvalue, double lenghtdiaposon, Vector2f posdiaposon) {
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
    template<isdig dig>
    void HorizontalSlider<dig>::setText(string str, Font font, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness) {
        textfont = font;
        s = str;
        text.setString(s);
        text.setFont(textfont);
        text.setCharacterSize(CharacterSize);
        text.setStyle(Text::Bold);
        text = InitialText(text, Vector2f(300, 300), textcolor, WidthThikness, colorThikness);
        text.setPosition(diaposon.getPosition().x - diaposon.getSize().x / 2 - text.getLocalBounds().width - 100, diaposon.getPosition().y - text.getLocalBounds().height / 2);
    }
    template<isdig dig>
    RectangleShape HorizontalSlider<dig>::getButtonDiaposon() { return diaposon; }
    template<isdig dig>
    RectangleShape HorizontalSlider<dig>::getButtonSlider() { return SliderButton; }
    template<isdig dig>
    Text HorizontalSlider<dig>::getText() { return textvalue; }
    template<isdig dig>
    void HorizontalSlider<dig>::setXSlider(dig Xslider) {
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
    template<isdig dig>
    void HorizontalSlider<dig>::setValue(dig мvalue) {
        value = мvalue;
        if (value < minvalue) value = minvalue;
        if (value > maxvalue) value = maxvalue;
        *quantity = value;
        double Xslider = (value - minvalue) / coefficient + leftX;
        SliderButton.setPosition(Vector2f(Xslider, constYslider));
        textvalue.setString(RoundDig(value, 0.01));
    }
    template<isdig dig>
    void HorizontalSlider<dig>::isPress() {
        //вынести гет позишен мышки в переменную
        if ((isPressButtonRec(cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x), diaposon)) || (isPressButtonRec(cellka(Mouse::getPosition(window).y, Mouse::getPosition(window).x), SliderButton))) {
            (*this).setXSlider(Mouse::getPosition(window).x);
        }
    }
    template<isdig dig>
    void HorizontalSlider<dig>::Draw() {
        window.draw(diaposon);
        window.draw(SliderButton);
        window.draw(textvalue);
        window.draw(text);
    }



