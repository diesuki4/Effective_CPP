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
    char *p = greeting;

    // 비상수 포인터
    // 상수 데이터
    const char* p = greeting;
    // * 기준으로는 왼쪽이기 때문에
    // 위와 동일하다.
    char const* p = greeting;

    // 상수 포인터
    // 비상수 데이터
    char* const p = greeting;

    // 상수 포인터
    // 상수 데이터
    const char* const p = greeting;

    return 0;
}
