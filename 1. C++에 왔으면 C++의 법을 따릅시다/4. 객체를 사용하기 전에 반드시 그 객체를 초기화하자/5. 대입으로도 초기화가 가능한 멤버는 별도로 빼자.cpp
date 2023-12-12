#include <iostream>

using namespace std;

/*
 * 대입으로도 초기화가 가능한 멤버는 별도로 빼자
 */

class PhoneNumber {  };
class DB   { public: static int GetData()    { return 5; } };
class File { public: static double GetData() { return 10.0; } };

class ABEntry
{
    int& refInt;
    const int cInt;

    PhoneNumber thePhone;

    int numTimesConsulted;
    int someData;
    double someData2;

    /*
     * 기본 타입의 객체들은 초기화나 대입이나 비용에 차이가 없기 때문에
     * private 초기화 함수로 빼내는 게 좋다.
     * 
     * 또, 멤버의 진짜 초깃값을 DB나 파일에서 읽어와야 하는 경우에도 유용하다.
     */
    void initPrimitve(int timesConsulted, int data = DB::GetData(), double data2 = File::GetData())
    {
        numTimesConsulted = 0;
        someData = data;
        someData2 = data2;
    }

public:
    /*
     * 보통 생성자는 인자에 따라 여러 개가 존재하기 때문에
     * 멤버 이니셜라이저를 주렁주렁 달게 되면 보기가 안 좋다.
     */
    ABEntry(int& ref, const int c)
    : refInt(ref), cInt(c), thePhone(), numTimesConsulted(0), someData(5), someData2(10.0) { }

    ABEntry(int& ref, const int c, const PhoneNumber phone)
    : refInt(ref), cInt(c), thePhone(phone), numTimesConsulted(0), someData(5), someData2(10.0) { }

    // 멤버 이니셜라이저에는 필수적인 것과 객체 타입만 적고
    // 기본 타입과 별도 초기화가 필요한 멤버들은 따로 뺐다.
    ABEntry(int& ref, const int c, const PhoneNumber phone, int timesConsulted)
    : refInt(ref), cInt(c), thePhone(phone)
    {
        initPrimitve(timesConsulted);
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
