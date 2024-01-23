#include <iostream>

using namespace std;

/*
 * 고전적인 전략 패턴
 */

class GameCharacterSP;

/* 체력 계산 함수를 나타내는 클래스 계통을 아예 따로 만들었다. */
class HealthCalcFunc
{
public:
    virtual int calc(const GameCharacterSP& gc) const { return 100; }
};

HealthCalcFunc defaultHealthCalc;

class WarriorHealthCalcFunc : public HealthCalcFunc
{
public:
    /* 실제 체력 계산은 오버라이드로 구현한다. */
    int calc(const GameCharacterSP& gc) const override { return 500; }
};

WarriorHealthCalcFunc warriorHealthCalcFunc;

class GameCharacterSP
{
    HealthCalcFunc *pHealthCalc;

public:
    explicit GameCharacterSP(HealthCalcFunc *phcf = &defaultHealthCalc) : pHealthCalc(phcf) {}

    int healthValue() const
    {
        int retVal = pHealthCalc->calc(*this);

        cout << "[체력 로그 출력] " << retVal << endl;

        return retVal;
    }

    void setHealthFunc(HealthCalcFunc* phcf)
    {
        pHealthCalc = phcf;
    }
};

int main(int argc, char* argv[])
{
    GameCharacterSP gc;

    cout << gc.healthValue() << endl;

    cout << "전사로 캐릭터 변경" << endl;
    gc.setHealthFunc(&warriorHealthCalcFunc);

    cout << gc.healthValue() << endl;

    return 0;
}
