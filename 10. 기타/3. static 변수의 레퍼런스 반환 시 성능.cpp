#include <iostream>

using namespace std;

/*
 * static 변수의 레퍼런스 반환 시 성능
 */

class Class { public: int num = 10; };

/*
 * 레퍼런스가 값 타입보다 항상
 * 반환 비용이 적은 것은 아니다.
 * 
 * 현재 Class 객체의 크기는 4바이트지만,
 * 
 * x64 시스템에서는
 * 레퍼런스는 오히려 8바이트가 된다.
 */
Class& getClass()
{
    /*
     * 함수 내의 static 변수는
     * 처음 이 문장에 도달했을 때만
     * 초기화된다.
     * 
     * 그래서, 첫 실행인지 확인하는
     * 보이지 않는 로직이 들어가기 때문에
     * 
     * 비용이 발생한다.
     */
    static Class c;

    /*
     * 또한, static 변수가 존재하는 함수에
     * inline 최적화를 적용하지 않는 컴파일러도 있다.
     */

    return c;
}

int main(int argc, char* argv[])
{
    Class& c = getClass();

    /*
     * 레퍼런스는 실제로는 컴파일러에 의해
     * 포인터로 번역된다.
     * 
     * 따라서, 역참조 비용이 따른다.
     */
    cout << c.num << endl;

    return 0;
}
