#include <iostream>

using namespace std;

/*
 * Copy & Swap
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

    // Copy & Swap 이므로 swap() 함수를 선언했다.
    void swap(Widget& rhs)
    {
        // 내부 멤버들을 교환한다.
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
     * 복사 대입 연산자 작성에 자주 쓰이는 기법이다.
     * 
     * 생성과 삭제 순서 조정 등을 고려하지 않아도 된다.
     */
    Widget& operator= (const Widget& rhs)
    {
        // rhs 의 값 타입 사본을 만든다.
        Widget temp(rhs);

        // 내부 멤버들을 swap 한다.
        swap(temp);

        return *this;
        
        /*
         * 함수가 종료되면 지역 변수 temp 에
         * 옮겨진 기존 데이터들은 자동으로 소멸한다.
         */
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
