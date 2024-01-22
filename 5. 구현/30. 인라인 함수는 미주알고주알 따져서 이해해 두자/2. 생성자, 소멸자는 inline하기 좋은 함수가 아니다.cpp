#include <iostream>
#include <vector>

using namespace std;

/*
 * 생성자, 소멸자는 inline하기 좋은 함수가 아니다
 */

class Base
{
    string bm1, bm2;

public:
    Base() {}
};

class Derived : public Base
{
    string dm1, dm2, dm3;

public:
    // 빈 생성자라서 inline하기 좋을 것 같지만, 실제로는 그렇지 않다.
    Derived() {}
};

class DerivedReal : public Base
{
    string dm1, dm2, dm3;

    // 빈 것처럼 보여도 실제로는 다음과 비슷한 과정의 코드가 추가된다.
    DerivedReal()
    {
        // Base 의 string 멤버 2개
        Base::Base();

        try
        {
            /* Derived 의 string 멤버 3개까지 inline화 될 것을 생각하면,
             * 똑같은 string 생성자, 소멸자가 5개나 끼워 넣어지게 된다.
             *
             * 생성자, 소멸자에 왜 inline이 좋지 않은지 알 수 있다. */
            dm1.string::basic_string();
        }
        catch (...)
        {
            Base::~Base();
            throw;
        }

        try
        {
            dm2.string::basic_string();
        }
        catch (...)
        {
            dm1.string::~basic_string();
            Base::~Base();
            throw;
        }

        try
        {
            dm3.string::basic_string();
        }
        catch (...)
        {
            dm2.string::~basic_string();
            dm1.string::~basic_string();
            Base::~Base();
            throw;
        }
    }
};

int main(int argc, char* argv[])
{
    /* 배열에서는 객체를 생성하고 소멸시킬 때
     * 생성자, 소멸자의 함수 포인터를 얻어낼 수 있어야 한다.
     *
     * inline화 되지 않는다는 뜻. */
    vector<Derived> v;

    return 0;
}
