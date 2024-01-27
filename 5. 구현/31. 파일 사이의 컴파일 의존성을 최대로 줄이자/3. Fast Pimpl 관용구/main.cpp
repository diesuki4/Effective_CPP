#include <iostream>
#include "Date.h"
#include "Address.h"
#include "Person.h"

using namespace std;

/*
 * Fast Pimpl 관용구
 *
 * 인터페이스 클래스 내에 Stack 버퍼를 만들고 그곳에 구현 세부를 할당해
 * Heap Allocation, Deallocation 오버헤드를 줄인 개선 버전
 * 
 * 정렬된 메모리를 할당 받는 점도 다르다.
 * 단, 정렬된 위치에만 메모리가 할당되므로 빈 홀들로 인해 단편화가 발생할 수 있다.
 */

int main(int argc, char* argv[])
{
    string s;
    Date d;
    Address a;

    Person p(s, d, a);

    return 0;
}
