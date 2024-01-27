#include <iostream>
#include "Date.h"
#include "Address.h"
#include "Person.h"

using namespace std;

/*
 * Pimpl 관용구
 *
 * 인터페이스와 구현 세부 분리를 통해 컴파일 의존성을 줄여,
 *
 * 하나의 수정으로 연쇄적으로 컴파일이 일어나지 않도록
 * 컴파일 방화벽을 달성하는 기법
 */

int main(int argc, char* argv[])
{
    string s;
    Date d;
    Address a;

    // 이제 전방 선언을 통해 포인터를 사용하지 않아도 된다.
    Person p(s, d, a);

    return 0;
}
