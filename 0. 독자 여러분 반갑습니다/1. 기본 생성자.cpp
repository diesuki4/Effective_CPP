#include <iostream>

using namespace std;

/*
 * 기본 생성자
 */

class AAA
{
    int x;
    int y;

public:
    // O
    // 어떤 인자도 받지 않는다.
    AAA() { }
};

class BBB
{
    int x;
    int y;

public:
    // O
    // 모든 인자가 기본 값을 갖고 있다.
    BBB(int x = 0, int y = 0) : x(x), y(y) { }
};

class CCC
{
    int x;
    int y;

public:
    // X
    // 인자를 받지만, 일부만 기본 값을 갖고 있다.
    CCC(int x, int y = 0) : x(x), y(y) { }
};

int main(int argc, char* argv[])
{
    // 기본 생성자가 있으면
    // 인자 없이 객체를 생성할 수 있다.
    AAA aaa;

    BBB bbb;
    
    // 기본 생성자가 없으므로
    // 생성 X
    // CCC ccc;
    
    return 0;
}
