#include <iostream>

using namespace std;

/*
 * 가상 함수는 동적 바인딩되지만, 기본 매개변수는 정적 바인딩된다
 * 
 * 이는 런타임 비용과 구현 간편성에 무게를 둔 결정이다.
 */

class Shape
{
public:
    virtual void draw(const char *p = "Shape") const = 0;
};

class Rectangle : public Shape
{
public:
    void draw(const char* p = "Rectangle") const override { cout << "Rectangle(\"" << p << "\")" << endl; }
};

class Circle : public Shape
{
public:
    void draw(const char* p) const override { cout << "Circle(\"" << p << "\")" << endl; }
};

int main(int argc, char* argv[])
{
    // 정적 타입: Shape, 동적 타입: Rectangle
    Shape* pr = new Rectangle;
    // 기본 매개변수: Shape, 가상 함수: Rectangle
    pr->draw();   // Rectangle::draw(const char *p = "Shape")

    Shape* pc = new Circle;
    pc->draw();   // Circle::draw(const char *p = "Shape")

    Circle* pcc = new Circle;
    pcc->draw("Circle");   // Circle::draw(const char *p)

    return 0;
}
