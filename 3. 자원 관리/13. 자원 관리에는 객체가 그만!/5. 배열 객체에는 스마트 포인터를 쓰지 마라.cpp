#include <iostream>
#include <vector>

using namespace std;

/*
 * 배열 객체에는 스마트 포인터를 쓰지 마라
 */

int main(int argc, char* argv[])
{
    /*
     * C++ 의 스마트 포인터 소멸자에서는 delete[] 가 아닌
     * delete 만을 사용한다.
     * 
     * 동적 할당된 배열은 vector, string 등으로 대체 가능하기 때문이다.
     * 
     * 따라서, 배열 객체는 스마트 포인터에 담으면 안 된다.
     *
     * 배열 객체를 delete[] 가 아닌 delete 로 해제하게 되면
     * 컴파일 에러는 발생하지 않지만
     * 
     * 첫 번째 객체만 해제된다던지, 소멸자가 모두 호출되지 않는 등의
     * Undefined behavior 로 이어질 수 있다.
     */

    // 잘못된 사용
    shared_ptr<int> shptr(new int[10]);

    // 차라리
    vector<int> v(10);

    return 0;
}
