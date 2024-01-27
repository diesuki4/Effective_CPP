#include <iostream>

using namespace std;

/*
 * 템플릿 메소드 패턴 (NVI 관용구)
 */

// 당연한 설계
class GameCharacter
{
public:
    // 가상 인터페이스
    virtual int healthValue() const { return 100; }
};

/* 템플릿 메소드 패턴 (Template Method Pattern)
 *
 * 이름과 달리, C++ 템플릿과는 하등 관련이 없다.
 *
 * 비가상 인터페이스를 통해 가상 함수를 간접적으로 호출하므로
 * <비가상 함수 인터페이스(NVI, Non-Virtual Interface) 관용구> 라고도 한다.
 * 
 * 가상 함수는 반드시 private 으로 둬야 한다는
 * Herb Sutter 의 가상 함수 은폐론과 관련이 있다. */
class GameCharacterTMP
{
public:
    /* 비가상 인터페이스 (뼈대, 레퍼)
     *
     * 로직은 부모 클래스가 정의하지만 */
    int healthValue() const
    {
        int retVal = doHealthValue();

        cout << "[체력 로그 출력] " << retVal << endl;

        return retVal;
    }

private:
    /* 숨겨진 가상 함수 (실제 구현)
     *
     * 실제 동작은 자식이 재정의할 수 있다. */
    virtual int doHealthValue() const { return 100; }
};

int main(int argc, char* argv[])
{
    GameCharacter gc;
    int health = gc.healthValue();

    GameCharacterTMP gctmp;
    health = gctmp.healthValue();

    return 0;
}
