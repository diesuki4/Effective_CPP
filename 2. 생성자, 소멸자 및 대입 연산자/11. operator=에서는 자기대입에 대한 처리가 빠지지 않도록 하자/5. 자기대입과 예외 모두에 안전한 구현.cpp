#include <iostream>

using namespace std;

/*
 * 자기대입과 예외 모두에 안전한 구현
 */

class SomeClass
{
public:
    SomeClass() { }

    SomeClass(const SomeClass& rhs) throw(string)
    {
        throw "복사 생성자 실패";
    }

    void Show() { cout << "SomeClass" << endl; }
};

class Widget
{
    SomeClass* pData;

public:
    Widget() : pData(new SomeClass) { }

    Widget& operator= (const Widget& rhs)
    {
        /*
         * 복사 대입 연산자는 예외에 안전하게 구현하면
         * 자기대입에도 안전하게 된다.
         * 
         * 아래처럼 삭제와 대입의 순서를 바꿔,
         * 대입이 성공한 경우에만 삭제하도록 구현하면
         * 해제된 메모리를 가리키지 않도록 할 수 있다.
         * 
         * 실제로 많은 경우에, 문장 순서를 바꾸는 것만으로도
         * 예외에 안전한 코드가 된다.
         * 
         * 또, 아래 구현은 자기대입에서도 잘 동작한다.
         */

        /*
         * if (this == &rhs) return *this;
         * 
         * 일치성 검사도 같이 넣으면 불필요한
         * 할당과 삭제도 막을 수 있지 않나? 할 수 있다.
         *
         * 하지만, 일치성 검사도 결국 Branch 를 만들기 때문에
         * Branch Prediction, 캐시 등에서 손해를 볼 수 있고
         * 코드 크기를 증가시킨다.
         *  
         * 자기대입은 흔하게 일어나지 않기 때문에
         * 일치성 검사를 생략하는 것이 더 좋은 선택일 수도 있다.
         */

        SomeClass* pOrig = pData;

        pData = new SomeClass(*rhs.pData);

        delete pOrig;

        return *this;
    }

    void Show() { pData->Show(); }

    ~Widget() { delete pData; }
};

int main(int argc, char* argv[])
{
    Widget x, y;

    try
    {
        /*
         * 대입 연산자에서 복사 생성 실패로
         * 예외 발생
         */
        x = y;
    }
    catch (const char* expt)
    {
        cout << expt << endl;
    }

    /*
     * 복사 생성이 실패했지만
     * 메모리는 해제되지 않았다.
     */
    x.Show();
    
    return 0;
}
