#include <iostream>
#include "Person.h"

using namespace std;

/*
 * 컴파일 의존성
 */

int main(int argc, char* argv[])
{
    /* 포인터는 전방 선언만으로도, 크기를 알 수 있다.
     *
     * Java, C# 등의 언어에서는 구조체 타입은 값으로,
     * 클래스 타입은 동적 할당 객체로 무조건 처리된다. */
    shared_ptr<Person> shp;

    return 0;
}
