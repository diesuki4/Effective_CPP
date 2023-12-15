#include <iostream>

using namespace std;

/*
 * 예외에 안전하지 않은 복사 대입 연산자 구현
 */

class SomeClass
{
public:
    SomeClass() { }

    // 복사 생성 도중 예외가 발생한 상황 가정
    SomeClass(const SomeClass& rhs) throw(string)
    {
        throw "복사 생성자 실패";
    }

    void Show() { cout << "SomeClass" << endl; }
};

class Widget
{
    SomeClass* pData;

public:
    Widget() : pData(new SomeClass) { }

    Widget& operator= (const Widget& rhs)
    {
        // 자기 대입은 방지할 수 있다.
        if (this == &rhs) return *this;

        delete pData;

        /*
         * 하지만, 동적 할당이 실패하거나
         * 복사 생성 도중 예외가 발생했다면
         * 
         * 이 객체의 pData 는
         * 해제된 메모리를 가리키고 있게 된다.
         */
        pData = new SomeClass(*rhs.pData);

        return *this;
    }

    void Show() { pData->Show(); }

    ~Widget() { delete pData; }
};

int main(int argc, char* argv[])
{
    Widget x, y;

    try
    {
        // 복사 생성 도중 예외 발생
        x = y;
    }
    catch (const char* expt)
    {
        cout << expt << endl;
    }

    /*
     * 해제된 채 남겨진
     * pData 에 접근하므로 오류 발생
     */
    x.Show();
    
    return 0;
}
