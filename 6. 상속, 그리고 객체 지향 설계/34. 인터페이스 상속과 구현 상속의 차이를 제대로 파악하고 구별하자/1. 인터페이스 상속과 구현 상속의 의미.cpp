#include <iostream>

using namespace std;

/*
 * 인터페이스 상속과 구현 상속의 의미
 */

class Shape
{
    /* 인터페이스만 상속
     *
     * 각 도형에서 어떻게 그릴지는 모르겠지만 그리기는 지원해야 한다. 구현은 각자 알아서 정해라. */
    virtual void draw() const = 0;

    /* 인터페이스와 기본 구현의 상속
     *
     * 각 도형에서 어떻게 출력할지는 모르겠지만 출력은 지원해야 한다. 개별 구현이 필요 없다면 기본 구현을 써라. */
    virtual void error(const string& msg);

    /* 인터페이스와 필수적인 구현(Mandatory Implementation) 의 상속
     *
     * 각 도형에서는 모두 동일한 방법으로 ID를 계산할 수 있어야 하고, 개별적으로 구현하면 안 된다. */
    int objectID() const;
};

/* 사실 순수 가상 함수도 본문을 정의할 수 있다.
 * 직접 객체를 만들 수 없기 때문에
 * 
 * child->Shape::draw() 처럼 호출해야 하지만. */
void Shape::draw() const
{
    cout << "Shape::draw() const = 0" << endl;
}

class Rectangle : public Shape
{
};

class Ellipse : public Shape
{
};

int main(int argc, char* argv[])
{
    

    return 0;
}
