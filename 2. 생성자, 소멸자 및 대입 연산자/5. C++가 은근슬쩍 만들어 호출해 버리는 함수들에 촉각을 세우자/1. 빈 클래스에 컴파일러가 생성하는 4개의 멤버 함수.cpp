#include <iostream>

using namespace std;

/*
 * 빈 클래스에 컴파일러가 생성하는 4개의 멤버 함수
 */

class Empty
{
    int* pData;

public:
    /*
     * 각각은 컴파일러가 필요하다고 판단할 때만 만들고,
     * 별도로 정의되어 있으면 추가하지 않는다.
     *
     * 클래스 내부에 정의된 함수는 기본적으로 inline 처리된다.
     */

    // Empty e; 같이 기본 생성자가 필요할 때
    inline Empty()
    {
        /*
         * Empty(int* pData) 같이 생성자가 1개라도 정의되어 있으면,
         * 추가하지 않는다.
         */
    }

    // Empty e1(e2); 같이 복사 생성자가 필요할 때
    inline Empty(const Empty& rhs) : pData(rhs.pData) { }

    // e1 = e2; 같이 복사 대입 연산자가 필요할 때
    inline Empty& operator= (const Empty& rhs)
    {
        /*
         * 상수 객체를 위한 const 오버로드 함수는 만들지 않는다.
         * 
         * 얕은 복사임에 유의한다.
         */
        pData = rhs.pData;
        return *this;
    }

    // 어디서든 객체 생성이 있을 때
    inline virtual ~Empty()
    {
        /*
         * 가상 함수와 마찬가지로,
         * 부모가 가상 소멸자이면 자식도 가상 소멸자가 된다.
         *
         * 부모 소멸자를 virtual 로 선언하지 않으면,
         * 업 캐스팅(부모 포인터 -> 자식 객체) 된 객체의
         * 자식 소멸자가 호출되지 않는다.
         */
    }
};

int main(int argc, char* argv[])
{

    return 0;
}
