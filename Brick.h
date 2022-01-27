//
// Created by georg on 12/8/2021.
//

#ifndef FINAL_BRICK_H
#define FINAL_BRICK_H
#include "rect.h"
struct dimensions1 {
    double width;
    double height;

    /* Constructors */
    dimensions1();
    dimensions1(double w, double h);

    /* Overloaded Operator */
    friend std::ostream& operator << (std::ostream& outs, const dimensions1 &d);
};

class Brick: public Rect {
private:
    dimensions1 size;
    int brickHealth;
    bool brickInPlay;
public:
    Brick();
    explicit Brick(dimensions1 size);
    explicit Brick(color fill);
    explicit Brick(point2D center);
    Brick(color fill, point2D center);
    Brick(double red, double green, double blue, double alpha);
    Brick(double x, double y);
    Brick(double red, double green, double blue, double alpha, double x, double y);
    Brick(color fill, double x, double y);
    Brick(double red, double green, double blue, double alpha, point2D center);
    Brick(color fill, dimensions1 size);
    Brick(point2D center, dimensions1 size);
    Brick(color fill, point2D center, dimensions1 size);
    Brick(double red, double green, double blue, double alpha, dimensions1 size);
    Brick(double x, double y, dimensions1 size);
    Brick(double red, double green, double blue, double alpha, double x, double y, dimensions1 size);
    Brick(color fill, double x, double y, dimensions1 size, int brickHealth, bool brickInPlay);
    Brick(double red, double green, double blue, double alpha, point2D center, dimensions1 size);

    /* Destructor */
    virtual ~Brick() = default;

    /* Getters */
    dimensions1 getSize() const;
    double getWidth() const;
    double getHeight() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setters */
    void setSize(dimensions1 size);
    void setSize(double width, double height);
    void setWidth(double width);
    void setHeight(double height);
    void changeSize(double deltaWidth, double deltaHeight);
    void changeWidth(double delta);
    void changeHeight(double delta);
    void setBrickHealth(int num);
    int getBrickHealth();
    void setBrickInPlay(bool play);
    bool getBrickInPlay();

};


#endif //FINAL_BRICK_H
