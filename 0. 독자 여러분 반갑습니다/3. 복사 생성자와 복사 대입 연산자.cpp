#include <iostream>

using namespace std;

/*
 * 복사 생성자와 복사 대입 연산자
 */

class Widget
{
    int *pData;

public:
    // 생성자
    Widget(int data) : pData(new int(data)) { cout << data << " 생성자" << endl; }

    // 복사 생성자
    // rhs로 새로운 객체를 생성할 때
    Widget(const Widget& rhs)
    {
        cout << "복사 생성자 " << *rhs.pData << endl;

        pData = new int(*rhs.pData);
    }

    // 복사 대입 연산자
    // <이미 생성된 객체>에 값을 복사할 때
    Widget& operator= (const Widget& rhs)
    {
        cout << *pData << " 복사 대입 연산자 " << *rhs.pData << endl;

        delete pData;

        pData = new int(*rhs.pData);

        return *this;
    }

    virtual ~Widget() { cout << *pData << " 소멸자" << endl;  delete pData; }
};

// 전달된 객체 passed 로 새로운 객체 w 를 만들기 위해
// W w(passed) 복사 생성자가 호출된다.
//
// 이미 할당된 객체에 대입하는 것이 아니기 때문에
// 복사 대입 연산자 X
void FuncWidget(Widget w) { return; }

int main(int argc, char* argv[])
{
    Widget w1(1);

    // 복사 생성자
    // Widget w2(w1);
    Widget w2 = w1;

    Widget w3(3);
    // 복사 대입 연산자
    w3 = w2;

    Widget w4(4);
    FuncWidget(w4);

    return 0;
}
