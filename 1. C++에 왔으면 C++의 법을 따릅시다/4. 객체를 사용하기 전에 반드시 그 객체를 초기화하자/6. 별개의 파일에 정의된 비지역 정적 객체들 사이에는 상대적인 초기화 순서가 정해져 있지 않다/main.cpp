#include <iostream>

using namespace std;

/*
 * 별개의 파일에 정의된 비지역 정적 객체들 사이에는
 * 상대적인 초기화 순서가 정해져 있지 않다
 */

/*
 * 번역 단위 (Translation unit)
 *
 * 컴파일을 통해 하나의 오브젝트 파일을 만들기 위한 소스 코드
 * 
 * #include 를 포함한 하나의 소스 파일이 하나의 번역 단위가 된다.
 */

/*
 * 정적 객체의 종류
 *
 * 1. 전역 객체
 * 2. 파일 유효 범위에서 static 으로 선언된 객체
 * 3. 네임스페이스 유효 범위에서 정의된 객체
 * 4. 클래스에서 static 으로 선언된 객체
 * 5. 함수에서 static 으로 선언된 객체
 * 
 * 모두 main() 함수의 실행이 끝날 때 소멸한다.
 * 5번을 제외하고는 모두 비지역 정적 객체라고 한다.
 * 
 */

// 1. 전역 객체
int g_num = 1;

// 2. 파일 유효 범위에서 static 으로 선언된 객체
static int fs_num = 2;

namespace AAA
{
    // 3. 네임스페이스 유효 범위에서 정의된 객체
    int namespace_num = 3;
};

class Class
{
public:
    // 4. 클래스에서 static 으로 선언된 객체
    static int class_num;
};
int Class::class_num = 4;

int Func()
{
    // 5. 함수에서 static 으로 선언된 객체
    static int func_num = 5;

    return func_num;
}

int main(int argc, char* argv[])
{
    cout << g_num << endl;
    cout << fs_num << endl;
    cout << AAA::namespace_num << endl;
    cout << Class::class_num << endl;
    cout << Func() << endl;

    return 0;
}
