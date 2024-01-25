#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

/*
 * std::function을 이용한 전략 패턴 개선
 */

class GameCharacterSP;

/* 함수 포인터
 * 
 * 반환 타입이 int 와 호환되는 short */
short calcHealth(const GameCharacterSP& gc) { return 100; }

/* 펑터 */
struct HealthCalculator
{
    // 반환 타입이 int 와 호환되는 float
    float operator() (const GameCharacterSP&) const { return 200.F; }
};

class GameLevel
{
public:
    /* 멤버 함수 포인터
     *
     * 반환 타입이 int 와 호환되는 double */
    double health(const GameCharacterSP&) const { return 300.0; }
};

class GameCharacterSP
{
public:
    /* 함수 포인터에서 function 으로 변경
    using HealthCalcFunc = int(*)(const GameCharacterSP&);*/
    using HealthCalcFunc = function<int(const GameCharacterSP&)>;

private:
    HealthCalcFunc healthFunc;

public:
    explicit GameCharacterSP(HealthCalcFunc hcf = calcHealth) : healthFunc(hcf) {}

    int healthValue() const
    {
        int retVal = healthFunc(*this);

        cout << "[체력 로그 출력] " << retVal << endl;

        return retVal;
    }

    void setHealthFunc(HealthCalcFunc hcf)
    {
        healthFunc = hcf;
    }
};

class EvilBadGuy : public GameCharacterSP
{
public:
    explicit EvilBadGuy(HealthCalcFunc hcf = calcHealth) : GameCharacterSP(hcf) {}
};

class EyeCandyCharacter : public GameCharacterSP
{
public:
    explicit EyeCandyCharacter(HealthCalcFunc hcf = calcHealth) : GameCharacterSP(hcf) {}
};

int main(int argc, char* argv[])
{
    // 체력 계산을 위해 함수 포인터도 사용 가능
    EvilBadGuy ebg1(calcHealth);

    cout << ebg1.healthValue() << endl;

    // 체력 계산을 위해 펑터도 사용 가능
    EyeCandyCharacter ecc1{HealthCalculator()};

    cout << ecc1.healthValue() << endl;


    /* 체력 계산을 위해 멤버 함수 포인터도 사용 가능
     *
     * GameLevel::health() 함수는 암시적으로 첫 번째 인자로 this 포인터를 받는다.
     *
     * bind 를 통해 (GameLevel*, const GameCharacterSP&) 를
     * 하나의 인자를 받는 (const GameCharacterSP&) 함수로 바꿔준 것.
     * 
     * _1 위치에 const GameCharacterSP& 가 위치하게 된다.
     *
     * 결과적으로 ebg2 의 체력 계산은
     * currentLevel.health(const GameCharacterSP&) 로 계산되는 것이다. */
    GameLevel currentLevel;
    EvilBadGuy ebg2(bind(&GameLevel::health, &currentLevel, _1));

    /* 이때는 currentLevel 의 복사본이 바인딩된다.
    EvilBadGuy ebg2(bind(&GameLevel::health, currentLevel, _1)); */

    cout << ebg2.healthValue() << endl;

    return 0;
}
