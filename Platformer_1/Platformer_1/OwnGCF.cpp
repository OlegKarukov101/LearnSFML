#pragma once
#include "OwnGCF.h"
//RenderWindow window(VideoMode(1600, 900), L"Платформер", Style::Default);



RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position) {
    RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);
    return shape;
}
RectangleShape InitialRectangleShape(Vector2f size, Color color, Vector2f position, float OutlineThikness, Color ColorOutlineThikness) {
    RectangleShape shape(size);
    shape.setFillColor(color);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);
    shape.setOutlineThickness(OutlineThikness);
    shape.setOutlineColor(ColorOutlineThikness);
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

RecButton::RecButton(shared_ptr<RenderWindow> window, Vector2f size, Vector2f position, Color color) {
    this->window = window;
    shape = InitialRectangleShape(size, color, position);
    this->color = color;
}
RecButton::RecButton(shared_ptr<RenderWindow> window, Vector2f size, Vector2f position, Color color, string str, Font font) {
    this->window = window;
    this->font = font;
    shape = InitialRectangleShape(size, color, position);
    this->color = color;
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
void RecButton::setTextPress(string str, double CharacterSize, Color textcolor, double WidthThikness, Color colorThikness) {
    detecttext = true;
    textpress.setString(str);
    textpress.setFont(this->font);
    textpress.setCharacterSize(CharacterSize);
    textpress.setStyle(Text::Bold);
    textpress = InitialText(textpress, Vector2f(300, 300), textcolor, WidthThikness, colorThikness);
    textpress.setPosition(shape.getPosition().x - shape.getSize().x / 2 + (shape.getSize().x - textpress.getLocalBounds().width) / 2, shape.getPosition().y - shape.getSize().y / 2 + (shape.getSize().y - textpress.getLocalBounds().height) / 2 - shape.getSize().y * 0.1);
}
void RecButton::setDetect(Color colorDetect) {
    this->colorDetect = colorDetect;
    detection = true;
}
void RecButton::setDetect() {
    detection = true;
}
void RecButton::turnOnDetection() { detection = true; }
void RecButton::turnOffDetection() { detection = false; }
bool RecButton::isIndicate() {
    cellka press = cellka(Mouse::getPosition(*window).y, Mouse::getPosition(*window).x);
    if (abs(press.i - shape.getPosition().y) < shape.getSize().y / 2 && abs(press.j - shape.getPosition().x) < shape.getSize().x / 2) {
        return true;
    }
    return false;
}
void RecButton::setColorPress(Color colorPress) {
    this->colorPress = colorPress;
    detectpress = true;
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
        if (detectpress && press) shape.setFillColor(colorPress);
        else shape.setFillColor(color);
    (*window).draw(shape);
    if (press && detecttext) {
        (*window).draw(textpress);
    }
    else if (s != "") {
        (*window).draw(text);
    }
}






