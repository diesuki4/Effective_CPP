#include <iostream>

using namespace std;

/*
 * 임시 객체와 상수 참조자
 */

class Widget
{
public:
    Widget(int size) { cout << "Widget::생성자" << endl; }
    ~Widget()        { cout << "Widget::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    /*
     * 임시 객체는 주소를 구할 수 없다.
     *
     * & 연산자는 l-value 에만 사용할 수 있다.
     *
     * Widget *ptr = &Widget(10);
     */

    /*
     * 임시 객체에는 레퍼런스를 사용할 수 없다.
     * 
     * C++ 는 임시 값, 임시 객체의 수정을 허용하지 않기 때문.
     *
     * Widget& ref = Widget(10);
     */

    /*
     * 하지만, 값 불변을 보장할 수 있는 상수 레퍼런스는 가능하다.
     * 
     * 이때는 상수 레퍼런스의 생명주기가 끝날 때,
     * 
     * 임시 객체도 함께 소멸한다.
     */
    const Widget& ref = Widget(10);

    cout << "임시 객체 Widget(10) 은 ref 가 해제될 때, 함께 소멸한다." << endl;

    return 0;
}
