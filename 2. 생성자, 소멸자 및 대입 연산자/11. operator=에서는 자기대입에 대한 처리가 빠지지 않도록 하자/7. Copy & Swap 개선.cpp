#include <iostream>

using namespace std;

/*
 * Copy & Swap 개선
 */

class SomeClass
{
    int num;

public:
    SomeClass(int num) : num(num) { cout << "SomeClass::생성자 " << num << endl; }
    SomeClass(const SomeClass& rhs) : num(rhs.num) { cout << "SomeClass::복사 생성자 " << num << endl; }

    int getNum() const { return num; }

    ~SomeClass() { cout << "SomeClass::소멸자 " << num << endl; }
};

class Widget
{
    SomeClass* pData;

    void swap(Widget& rhs)
    {
        SomeClass* pData = this->pData;

        this->pData = rhs.pData;

        rhs.pData = pData;
    }

public:
    Widget(int num) : pData(new SomeClass(num))
    {
        cout << "Widget::생성자 " << num << endl;
    }

    Widget(const Widget& rhs) : pData(new SomeClass(*rhs.pData))
    {
        cout << "Widget::복사 생성자 " << pData->getNum() << endl;
    }

    /*
     * 복사 대입 연산자는 복사 생성자처럼
     * 시그니처가 고정되어 있는 것이 아니기 때문에
     * 
     * 값 타입을 인자로 받을 수도 있다.
     */
    Widget& operator= (Widget rhs)
    {
        /*
         * 그렇다면 사본 temp 를 만들 필요 없이
         * 넘어온 인자 자체가 사본이 된다.
         * 
         * Widget temp(rhs);
         * swap(temp);
         * 
         */
        swap(rhs);

        return *this;
    }

    ~Widget()
    {
        cout << "Widget::소멸자 " << pData->getNum() << endl;
        delete pData;
    }
};

int main(int argc, char* argv[])
{
    Widget x(1), y(2);

    cout << endl << "--- operator= 시작 ---" << endl << endl;
    x = y;
    cout << endl << "--- operator= 종료 ---" << endl << endl;
}
