#include <iostream>
#include <vector>

using namespace std;

/*
 * new 및 delete를 사용할 때는 형태를 반드시 맞추자
 */

int main(int argc, char* argv[])
{
    /*
     * new 의 동작
     * 1. operator new 연산을 통한 메모리 할당
     * 2. 생성자 호출
     * 
     * delete 의 동작
     * 1. 소멸자 호출
     * 2. operator delete 연산을 통한 메모리 해제
     */

    /*
     * 단일 객체와 객체 배열의 메모리 배치 구조는 다르다.
     * 
     * 단일 객체
     * Obj
     * 
     * 객체 배열
     * n(원소 개수) | Obj | Obj | Obj | ...
     * 
     * delete[] 시에, 앞 부분의 원소 개수 블록을 읽어
     * 배열의 크기를 알 수 있다.
     */

    /*
     * 따라서, new 와 delete 형태를 맞추지 않으면
     * Undefined behavior 가 발생할 수 있다.
     */

    string *stringArray = new string[100];
    /* 
     * 1. 첫 번째 객체만 소멸자가 호출된다.
     * 2. 그냥 원소 개수를 나타내는 블록만 해제된다.
     */
    delete stringArray;

    string* stringPtr = new string;
    /*
     * 객체가 저장된 공간을 원소 개수 블록으로 읽어서
     * 그 뒤 공간까지 소멸자를 호출하며 해제하려고 한다.
     */
    delete[] stringPtr;

    /*
     * typedef 를 쓴다면 작성자에게는
     * 어떤 delete 형태를 사용해야 하는지
     * 알릴 의무가 있다.
     */
    typedef string AddressLines[4];

    // string[4] 이므로 delete[] 를 사용하세요.
    string* pal = new AddressLines;

    delete[] pal;

    /*
     * 사실은 그냥 vector 같은
     * 좋은 동적 배열을 쓰는 게 좋다.
     */
    vector<string> v(4);

    return 0;
}
