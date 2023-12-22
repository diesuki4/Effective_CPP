#include <iostream>
#include <vector>

using namespace std;

/*
 * 폭포식 dynamic_cast 설계는 절대 금지
 */

class Window
{
public:
    virtual ~Window() { }
};

class SpecialWindow1 : public Window
{
public:
    void blink1()
    {
        cout << "SpecialWindow1::blink1()" << endl;
    }
};

class SpecialWindow2 : public Window
{
public:
    void blink2()
    {
        cout << "SpecialWindow2::blink2()" << endl;
    }
};

class SpecialWindow3 : public Window
{
public:
    void blink3()
    {
        cout << "SpecialWindow3::blink3()" << endl;
    }
};

int main(int argc, char* argv[])
{
    using VPW = vector<shared_ptr<Window>>;
    VPW winPtrs;

    winPtrs.emplace_back(new Window);
    winPtrs.emplace_back(new SpecialWindow1);
    winPtrs.emplace_back(new SpecialWindow2);
    winPtrs.emplace_back(new SpecialWindow3);

    for (VPW::iterator it = winPtrs.begin(); it != winPtrs.end(); ++it)
    {
        /*
         * 아래처럼 실제 객체에 해당하는 포인터를 찾기 위해
         * dynamic_cast 를 줄줄이 호출하는 것을
         * 
         * 폭포식(Cascading) 설계라고 한다.
         * 
         * Window 의 상속 계통이 바뀌면,
         * 아래 코드에도 변경이 발생한다.
         */
        if (SpecialWindow1* psw = dynamic_cast<SpecialWindow1*>(it->get()))
            psw->blink1();
        else if (SpecialWindow2* psw = dynamic_cast<SpecialWindow2*>(it->get()))
            psw->blink2();
        else if (SpecialWindow3* psw = dynamic_cast<SpecialWindow3*>(it->get()))
            /*
             * 여기까지 오면 벌써
             * dynamic_cast 가 3번이나 호출되었다.
             */
            psw->blink3();
    }

    return 0;
}
