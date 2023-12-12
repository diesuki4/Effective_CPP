#include <iostream>

#define STRING "AAAAA"

using namespace std;

/*
 * #define 을 const 상수로 교체할 때 주의할 점
 */

/*
 * const 상수는 보통 헤더에 정의한다.
 *
 * #define 을 const 상수로 교체하려는 경우,
 * 상수 포인터면 주의해야 한다.
 *
 * 다음과 같이 선언하면 문자열의 내용이 바뀔 수 있다.
 */
const char* CString = "AAAAA";

/*
 * 따라서, const 를 2번 정의해 포인터와 내용 모두 바뀌지 않도록 해야 한다.
 */
const char* const ConstCString = "AAAAA";

/*
 * C++ 에서는 string 을 사용하는 것이 더 좋다.
 */
const string StringString = "AAAAA";

int main(int argc, char* argv[])
{


    return 0;
}
