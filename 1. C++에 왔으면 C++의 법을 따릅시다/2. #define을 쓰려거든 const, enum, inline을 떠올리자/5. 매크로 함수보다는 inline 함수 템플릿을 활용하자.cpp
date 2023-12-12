#include <iostream>

#define CALL_WITH_MAX(a, b) Func((a) > (b) ? (a) : (b))

using namespace std;

void Func(int num) { cout << num << endl; }

/*
 * 매크로 함수보다는 inline 함수 템플릿을 활용하자
 */

/*
 * 빠른 실행 속도, 다양한 타입 수용 가능 등
 * 매크로 함수의 장점을 그대로 유지하면서
 * 
 * 괄호 치기, 변수가 여러 번 평가되는 문제 등
 * 단점도 해결할 수 있다.
 * 
 * 진짜 함수이기 때문에, 클래스 등에서
 * Scope 를 제한할 수도 있다.
 */
class AAA
{
public:
    template <typename T>
    // T 가 객체일 수도 있기 때문에, 레퍼런스를 받는다.
    inline void CallWithMax(const T& a, const T& b)
    {
        Func(a > b ? a : b);
    }
};

int main(int argc, char* argv[])
{
    int a = 3, b = 2;

    // a가 2번 증가한다.
    CALL_WITH_MAX(++a, b);

    // b가 더 크므로, a는 1번 증가한다.
    CALL_WITH_MAX(++a, b + 10);

    AAA aaa;
    a = 3, b = 2;

    aaa.CallWithMax(++a, b);

    return 0;
}
