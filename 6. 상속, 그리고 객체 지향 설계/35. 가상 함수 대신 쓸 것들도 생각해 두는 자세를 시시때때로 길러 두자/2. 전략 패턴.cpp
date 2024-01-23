#include <iostream>

using namespace std;

/*
 * 전략 패턴
 * 
 * <장점>
 * 객체별로 전략을 지정할 수 있고, 런타임에도 교체가 가능하다.
 * 
 * <단점>
 * 캡슐화를 약화시킨다.
 */

class GameCharacterSP;

/* 체력 계산이라는 작업을 캐릭터에서 분리했다.
 *
 * 하지만, GameCharacter 의 내부 멤버를 이용해 체력을 계산해야 할 때는
 * 이렇게 쓸 수 없다.
 *
 * 굳이 쓰자면 friend 로 선언하거나, public 멤버 함수를 또 만들 수 있지만
 * 캡슐화는 약화되게 된다. */
int defaultHealthCalc(const GameCharacterSP& gc) { return 100; }
int warriorHealthCalc(const GameCharacterSP& gc) { return 300; }

/* 전략 패턴 (Strategy Pattern) */
class GameCharacterSP
{
public:
    using HealthCalcFunc = int(*)(const GameCharacterSP&);

private:
    // 체력 계산 전략
    HealthCalcFunc healthFunc;

public:
    // 전략 지정
    explicit GameCharacterSP(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}

    /* 비가상 인터페이스(뼈대, 레퍼)
     *
     * 이 부분은 템플릿 메소드 패턴과 같다. */
    int healthValue() const
    {
        /* 실제 구현이 가상 함수 오버라이드가 아닌
         * 함수 포인터, 펑터 등을 통해
         *
         * 런타임에도 교체될 수 있다는 점이 다르다. */
        int retVal = healthFunc(*this);

        cout << "[체력 로그 출력] " << retVal << endl;

        return retVal;
    }

    void setHealthFunc(HealthCalcFunc hcf)
    {
        healthFunc = hcf;
    }
};

int main(int argc, char* argv[])
{
    // 함수 포인터를 이용해 다른 전략을 끼워넣을 수 있다.
    GameCharacterSP defaultChar;
    GameCharacterSP warriorChar(warriorHealthCalc);

    cout << defaultChar.healthValue() << endl;
    cout << warriorChar.healthValue() << endl;

    // 런타임에 동적으로 전략을 교체할 수도 있다.
    warriorChar.setHealthFunc(defaultHealthCalc);

    cout << warriorChar.healthValue() << endl;

    return 0;
}
