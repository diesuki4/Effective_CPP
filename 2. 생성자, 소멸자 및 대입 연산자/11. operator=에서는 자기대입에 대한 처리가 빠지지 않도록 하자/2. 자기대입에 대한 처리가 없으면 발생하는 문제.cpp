#include <iostream>

using namespace std;

/*
 * 자기대입에 대한 처리가 없으면 발생하는 문제
 */

class Widget
{
    int* pData;

public:
    Widget(int data = 0) : pData(new int(data)) { }

    /*
     * 자기대입에 대한 처리가 없어
     * 안전하지 않은 구현
     */
    Widget& operator= (const Widget& rhs)
    {
        // 자신 멤버의 메모리를 해제한다.
        delete pData;

        /*
         * 알고보니 상대방이 나 자신이어서
         * 해제된 내 멤버의 메모리를 참조하게 됐다.
         */
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

    // 오류 발생
    (x = x).Show();
    
    return 0;
}
