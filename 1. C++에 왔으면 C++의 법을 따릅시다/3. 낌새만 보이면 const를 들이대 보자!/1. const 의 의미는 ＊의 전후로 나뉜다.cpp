#include <iostream>

using namespace std;

/*
 * const 의 의미는 *의 전후로 나뉜다
 */

int main(int argc, char* argv[])
{
    char greeting[] = "Hello";

    // 비상수 포인터
    // 비상수 데이터
    char* p1 = greeting;

    // 비상수 포인터
    // 상수 데이터
    const char* p2 = greeting;
    // * 기준으로는 왼쪽이기 때문에
    // 위와 동일하다.
    char const* p3 = greeting;

    // 상수 포인터
    // 비상수 데이터
    char* const p4 = greeting;

    // 상수 포인터
    // 상수 데이터
    const char* const p5 = greeting;

    int num1 = 10;
    int num2 = 20;

    // 레퍼런스 (상수 레퍼런스)
    // 비상수 데이터
    // 
    // 레퍼런스는 원래, 초기화만 가능하고, 대입은 불가능하다.
    int& r1 = num1;
    int& const r2 = num1;

    // 이것들은 값 복사이지, num2 를 참조하도록 대입한 것이 아니다.
    r1 = num2;
    r2 = num2;

    // 레퍼런스 (상수 레퍼런스)
    // 상수 데이터
    const int& r3 = num1;
    const int& const r4 = num1;
    // r3 = num2;
    // r4 = num2;

    return 0;
}
