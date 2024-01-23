#include <iostream>

using namespace std;

/*
 * 펭귄은 날 수 있다?
 */

class Bird1
{
    // 새는 날 수 있다.
    virtual void fly() {}
};

class Penguin1 : public Bird1
{
    /* 펭귄은 날 수 있다..?
    virtual void fly(); */
};

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

void error(const char* msg) { cout << msg << endl; }

class Bird2
{
    // 새는 날 수 있다.
    virtual void fly() {}
};

class Penguin2 : public Bird2
{
    // 컴파일이 아닌, 런타임에 펭귄의 비행 불가가 확인된다.
    void fly() override { error("펭귄은 날 수 있지만, 날려고 하면 막을 것이다."); }
};

/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */

class Bird3
{
    /* 모든 종류의 새가 날 수 있는 건 아니다.
    virtual void fly(); */
};

class Eagle3 : public Bird3
{
    /* 독수리는 날 수 있다. */
    virtual void fly() {}

};

class Penguin3 : public Bird3
{
    /* 펭귄은 날 수 없다.
     * 펭귄의 비행 불가가 컴파일 타임에 확인된다.
     *
     * 유효하지 않은 코드를 컴파일 단계에서 막아주는 인터페이스가
     * 좋은 인터페이스다. */
};

int main(int argc, char* argv[])
{
    

    return 0;
}
