#include <iostream>

using namespace std;

/*
 * NVI(비가상 인터페이스, Non-Virtual Interface) 관용구를 이용한 불일치 해결
 * 
 * 동적/정적 바인딩에 의한 기본 매개변수와 가상 함수의 불일치를
 * 해결하는 방법은 2가지를 생각해 볼 수 있다.
 *
 * 1. 기본 매개변수가 동적 바인딩 되도록 한다.
 * 2. 가상 함수 대신 비가상 함수로 정적 바인딩 한다.
 *
 * 아쉽게도 1번처럼 기본 매개변수가 동적 바인딩 되도록 하는 방법은 없다.
 */

/*
 * NVI 관용구(템플릿 메소드 패턴) 를 통해 정적/동적 바인딩에 의한 불일치를 해결할 뿐,
 * 부모 타입에 담길 때 자식의 기본 매개변수를 사용할 수 있는 방법은 없다.
 *
 * 따라서, 기본 매개변수를 재정의하게 되면 불일치가 발생한다.
 *
 * 멤버 함수에 기본 매개변수를 쓰고 싶을 때는 비가상 함수에 작성해야 하고,
 * 가상 함수라면 NVI 관용구를 이용해야 한다.
 */
class Shape
{
public:
    // 비가상 인터페이스는 항상 정적 바인딩 되므로, 여기에 기본 매개변수를 작성
    void draw(const char* p = "Shape") const
    {
        // 매개변수를 가상 함수에 인자로 전달한다.
        drawImpl(p);
    }

// 실제 구현부는 숨겼다.
private:
    virtual void drawImpl(const char *p) const = 0;
};

class Rectangle : public Shape
{
private:
    // 숨겨진 가상 함수 구현부에서는 기본 매개변수를 작성하지 않는다.
    void drawImpl(const char* p) const override { cout << "Rectangle(\"" << p << "\")" << endl; }
};

class Circle : public Shape
{
private:
    void drawImpl(const char* p) const override { cout << "Circle(\"" << p << "\")" << endl; }
};

int main(int argc, char* argv[])
{
    /* 이제 기본 매개변수와 호출 함수의 불일치가 해결되었다. */

    Shape* pr = new Rectangle;
    pr->draw();   // Shape::draw(const char *p = "Shape") { Rectangle::draw(p); }

    Shape* pc = new Circle;
    pc->draw();   // Shape::draw(const char *p = "Shape") { Circle::draw(p); }

    Circle* pcc = new Circle;
    pcc->draw();  // Shape::draw(const char *p = "Shape") { Circle::draw(p); }

    return 0;
}
