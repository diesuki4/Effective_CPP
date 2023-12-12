#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 물리적 상수성과 논리적 상수성
 */

class CTextBlock
{
    char* pText;

public:
    CTextBlock(const char* pText)
    {
        size_t len = string(pText).length() + 1;

        this->pText = new char[len];

        copy(pText, pText + len, this->pText);
    }

    /*
     * 물리적 상수성 (비트수준 상수성)
     *
     * 어떤 멤버 함수가 객체의 1비트도 변경하지 않아야
     * const 로 인정하는 개념
     *
     * C++에서 정의하고 있는 상수성이다.
     *
     * 컴파일러는 멤버 변수에 대한
     * 대입 연산이 있는지를 통해 확인이 가능하다.
     *
     */
    char& operator[] (size_t position) const
    {
        return pText[position];
    }

    void Show() const { cout << pText << endl; }

    /*
     * 논리적 상수성
     *
     * 물리적 상수성을 보완하는 대체 개념으로 나오게 됐다.
     *
     * 물리적 상수성으로도 멤버의 변경을 완벽하게 막을 수는 없으니,
     * 일부 몇 비트 정도는 바꿀 수 있되 (mutable), 사용자 측에서 알아채지만 못 하면
     * 상수 멤버의 자격이 있다는 개념
     *
     */

private:
    mutable size_t textLength;
    mutable bool lengthIsValid;

public:
    size_t length() const
    {
        if (!lengthIsValid)
        {
            /*
             * mutable 로 선언됐으므로
             * 상수 멤버 함수에서도
             * 일부 비트는 바뀔 수 있다.
             */
            textLength = string(pText).length();
            lengthIsValid = true;
        }

        // 컴파일러와 사용자 모두 만족할 수 있는 방법
        return textLength;
    }

    virtual ~CTextBlock() { delete[] pText; }
};

int main(int argc, char* argv[])
{
    const CTextBlock cctb("Hello");

    // 물리적 상수성은 완벽하게 지켜질 수 없다.
    char* pc = &cctb[0];
    *pc = 'J';

    cctb.Show();

    /*
     * 따라서, 유연한 논리적 상수성이 등장했다.
     *
     * 사용자 측에서는 상수 함수를 호출하므로
     * 내부 몇 비트가 변경될 수 있다는 걸
     * 
     * 알아채지 못 한다.
     * 
     */
    cout << cctb.length() << endl;

    return 0;
}
