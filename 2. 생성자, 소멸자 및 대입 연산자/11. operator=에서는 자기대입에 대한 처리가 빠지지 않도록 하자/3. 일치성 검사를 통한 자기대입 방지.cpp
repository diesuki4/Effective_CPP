#include <iostream>

using namespace std;

/*
 * 일치성 검사를 통한 자기대입 방지
 */

class Widget
{
    int* pData;

public:
    Widget(int data = 0) : pData(new int(data)) { }

    Widget& operator= (const Widget& rhs)
    {
        /*
         * this 포인터와 전달된 레퍼런스의 주소를 비교한다.
         * 
         * 같으면, 대입 없이 바로 반환해버린다.
         */
        if (this == &rhs) return *this;

        delete pData;

        pData = new int(*rhs.pData);

        return *this;
    }

    void Show() { cout << *pData << endl; }

    ~Widget() { delete pData; }
};

int main(int argc, char* argv[])
{
    Widget x, y(3);

    // 정상 작동
    (x = y).Show();

    // 자기대입이면 바로 반환된다.
    (x = x).Show();
}
