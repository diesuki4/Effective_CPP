#include <iostream>
#include <vector>

using namespace std;

/*
 * 캐스팅이 꼭 필요하다면 함수를 통해 인터페이스로 제공하라
 * 
 * 꼭 필요하다면이다.
 * 
 * dynamic_cast 를 쓰기 전에 최대한
 * 가상 함수를 활용하던지, 별도 컨테이너를 활용하던지 해서
 * 
 * 안 쓰는 방향으로 설계해야 한다.
 */

class Window
{
public:
    virtual void onResize() { cout << "Window::onResize()" << endl; }

    /*
     * 부모에 blink() 의 가상 함수가 없고
     * 자식 포인터만을 저장하는 별도 컨테이너도 사용할 수 없어
     * 
     * 어쩔 수 없이 dynamic_cast 를
     * 써야만 하는 상황을 가정한다.
     */

    virtual ~Window() { }
};

using VPW = vector<shared_ptr<Window>>;

class SpecialWindow : public Window
{
public:
    virtual void onResize() override { cout << "SpecialWindow::onResize()" << endl; }

    void blink()
    {
        cout << "SpecialWindow::blink()" << endl;
    }
};

/*
 * 이렇게 함수로 제공하면
 * 사용자 측에서는 캐스팅을 고려하지 않아도 된다.
 */
void BlinkAll(VPW& winPtrs)
{
    for (VPW::iterator it = winPtrs.begin(); it != winPtrs.end(); ++it)
        if (SpecialWindow* psw = dynamic_cast<SpecialWindow*>(it->get()))
            psw->blink();
}

int main(int argc, char* argv[])
{
    VPW winPtrs;

    winPtrs.emplace_back(new SpecialWindow);
    winPtrs.emplace_back(new SpecialWindow);
    winPtrs.emplace_back(new Window);

    // 사용자 측에서는 편하게 사용할 수 있다.
    BlinkAll(winPtrs);

    return 0;
}
