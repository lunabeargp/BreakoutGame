//
// Created by georg on 12/8/2021.
//


#include "graphics.h"
#include "Brick.h"
#include <iostream>
using namespace std;

/********************* Dimensions Struct ********************/

dimensions1::dimensions1() : width(0), height(0) {}

dimensions1::dimensions1(double w, double h) : width(w), height(h) {}

ostream& operator << (ostream& outs, const dimensions1 &d) {
    outs << "[" << d.width << ", " << d.height << "]";
    return outs;
}

Brick::Brick(): Rect(), size({0, 0}) {
}

Brick::Brick(dimensions1 size) : Rect() {
    setSize(size);
}

Brick::Brick(color fill) : Rect(fill), size({0, 0}) {
}

Brick::Brick(point2D center) : Rect(center), size({0, 0}) {
}

Brick::Brick(color fill, point2D center) : Rect(fill, center), size({0, 0}) {
}

Brick::Brick(double red, double green, double blue, double alpha) : Rect(red, green, blue, alpha), size({0, 0}) {
}

Brick::Brick(double x, double y) : Rect(x, y), size({0, 0}) {
}

Brick::Brick(double red, double green, double blue, double alpha, double x, double y) : Rect(red, green, blue, alpha, x, y), size({0, 0}) {
}

Brick::Brick(color fill, double x, double y) : Rect(fill, x, y), size({0, 0}) {
}

Brick::Brick(double red, double green, double blue, double alpha, point2D center) : Rect(red, green, blue, alpha, center), size({0, 0}) {
}

Brick::Brick(color fill, dimensions1 size) : Rect(fill) {
    setSize(size);
}

Brick::Brick(point2D center, dimensions1 size) : Rect(center) {
    setSize(size);
}

Brick::Brick(color fill, point2D center, dimensions1 size) : Rect(fill, center) {
    setSize(size);
}

Brick::Brick(double red, double green, double blue, double alpha, dimensions1 size) : Rect(red, green, blue, alpha) {
    setSize(size);
}

Brick::Brick(double x, double y, dimensions1 size) : Rect(x, y) {
    setSize(size);
}

Brick::Brick(double red, double green, double blue, double alpha, double x, double y, dimensions1 size) : Rect(red, green, blue, alpha, x, y) {
    setSize(size);
}

Brick::Brick(color fill, double x, double y, dimensions1 size, int brickHealth, bool brickInPlay) : Rect(fill, x, y) {
    setSize(size);
    setBrickHealth(brickHealth);
    brickInPlay=true;
}

Brick::Brick(double red, double green, double blue, double alpha, point2D center, dimensions1 size) : Rect(red, green, blue, alpha, center) {
    setSize(size);
}

dimensions1 Brick::getSize() const {
    return size;
}

double Brick::getWidth() const {
    return size.width;
}

double Brick::getHeight() const {
    return size.height;
}

double Brick::getLeftX() const {
    return center.x - (size.width / 2.0);
}

double Brick::getRightX() const {
    return center.x + (size.width / 2.0);
}

double Brick::getTopY() const {
    return center.y - (size.height / 2.0);
}

double Brick::getBottomY() const {
    return center.y + (size.height / 2.0);
}

void Brick::setSize(dimensions1 size) {
    if (size.width >= 0 && size.height >= 0) {
        this->size = size;
    }
}

void Brick::setSize(double width, double height) {
    setSize({width, height});
}

void Brick::setWidth(double width) {
    setSize({width, size.height});
}

void Brick::setHeight(double height) {
    setSize({size.width, height});
}

void Brick::changeSize(double deltaWidth, double deltaHeight) {
    setSize({size.width + deltaWidth, size.height + deltaHeight});
}

void Brick::changeWidth(double delta) {
    setSize({size.width + delta, size.height});
}

void Brick::changeHeight(double delta) {
    setSize({size.width, size.height + delta});
}
void Brick::setBrickHealth(int num){
    brickHealth=num;
}
int Brick::getBrickHealth(){
    return brickHealth;
}
void Brick::setBrickInPlay(bool play) {
    brickInPlay=play;
}
bool Brick::getBrickInPlay(){
    return brickInPlay;
}
