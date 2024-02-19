#include <iostream>
#include <list>

using namespace std;

/*
 * C++ 표준 라이브러리에서 코드 비대화를 줄인 사례
 * 
 * vector, deque, list 등이 이렇게 구현되어 있다.
 */

template <typename T, size_t N>
class Widget {};

int main(int argc, char* argv[])
{
    /* 아래 템플릿 클래스들은 바이너리 수준에서는 어떤 차이도 없다.
     * T* 로 동작하는 함수의 내부에서는 void* 로 동작하는 함수를 호출하도록 하면
     *
     * 같은 void* 버전을 호출하게 되어 코드 비대화를 줄일 수 있다. */
    list<int*> li;
    list<const double*> ld;
    list<Widget<int, 3>*> lw;

    return 0;
}
