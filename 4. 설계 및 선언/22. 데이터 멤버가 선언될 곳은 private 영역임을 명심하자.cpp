#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*
 * 데이터 멤버가 선언될 곳은 private 영역임을 명심하자
 * 
 * 접근 수준은
 * private(캡슐화 제공) 과 private이 아닌(캡슐화 없음)
 * 둘 뿐이다.
 */

/*
 * 멤버의 접근성에 대해 훨씬 정교한 제어가 가능하다.
 */
class AccessLevels
{
    int noAccess;
    int readOnly;
    int readWrite;
    int writeOnly;

public:
    int getReadOnly() const      { return readOnly; }
    int getReadWrite() const     { return readWrite; }
    void setReadWrite(int value) { readWrite = value; }
    void setWriteOnly(int value) { writeOnly = value; }
};

/*
 * 캡슐화가 가능하다.
 * 
 * 함수를 통해 데이터 멤버에 접근하도록 하면
 * 
 * 1. 내부 구현을 바꿔도 사용자 측에서는 신경쓰지 않아도 된다.
 * 2. 데이터 멤버를 계산식으로 대체할 수도 있게 된다.
 * 3. 읽기/쓰기 시에 별도 작업이 가능하다.
 * 4. 불변속성, 유효성 검증이 가능하다.
 * 5. 멀티스레드 환경에서 동기화를 걸 수 있다.
 */
class SpeedDataCollection
{
    // float average;
    vector<int> speeds;

public:
    void addValue(int speed)
    {
        speeds.emplace_back(speed);
    }

    float averageSoFar() const
    {
        /*
         * 평균값 데이터 멤버가
         * 계산식으로 대체되었다.
         *
         * return average;
         */
        return accumulate(speeds.begin(), speeds.end(), 0) / static_cast<float>(speeds.size());
    }
};

class SomeDamnClass
{
    /* 
     * public 으로 선언한다는 것은 사용자가 쓰고 있다는 걸 가정하기 때문에
     * 코드를 깨트리지 않기 위해서는 바꾸기가 쉽지 않다.
     *
     * 따라서, 캡슐화되지 않았다 = 바꿀 수 없다의 의미를 담고 있다.
     */
public:
    /*
     * 캡슐화되지 않은 변수의 이름이 바뀌었다고 가정
     * 
     * int nonCapsulizedVariable;
     */
    int NameChangedVariable;

    /*
     * protected 는 외부에 노출되지 않으니 괜찮을까?
     * 
     * 사실 public 과 별반 차이가 없다.
     */
protected:
    /*
     * 캡슐화되지 않은 변수의 이름이 바뀌었다고 가정
     *
     * int nonCapsulizedBaseVariable;
     */
    int NameChangedBaseVariable;
};

class DerivedClass : public SomeDamnClass
{
public:
    void Show()
    {
        /*
         * 내 클래스를 상속받은 누군가의 클래스에서
         * public 과 마찬가지로 코드가 깨진다.
         *
         * cout << onCapsulizedBaseVariable << endl;
         */
        cout << NameChangedBaseVariable << endl;
    }
};

int main(int argc, char* argv[])
{
    SpeedDataCollection sdc;

    sdc.addValue(1);
    sdc.addValue(2);
    sdc.addValue(3);
    sdc.addValue(11);

    /*
     * 사용자 측에서는 내부 구현을 몰라도 되고
     * 계산식을 통해 평균값이라는 멤버에 바로 접근할 수 있다.
     * 
     * C# 에서는 프로퍼티(Property) 라는 이름으로 이렇게 사용한다.
     */
    cout << sdc.averageSoFar() << endl;

    SomeDamnClass damnClass;

    /*
     * 캡슐화되지 않은 데이터 멤버는
     * 이름이 바뀌면 사용자 측의 코드가 깨진다.
     * 
     * cout << damnClass.nonCapsulizedVariable << endl;
     */
    cout << damnClass.NameChangedVariable << endl;

    return 0;
}
