#include <iostream>
#include <mutex>

using namespace std;

/*
 * Copy & Swap을 통한 강한 보장
 * 
 * All or Nothing
 * 
 * 객체의 사본을 만들고, 사본을 수정한 후 성공하면
 * 원본 객체와 맞바꾼다.
 * 
 * 여기서 Swap 부분은 Non-throwing Swap 으로 수행되어야 한다.
 */

class Image
{
    char bytes[1024][1024];

public:
    Image(istream& imgSrc) {}
    Image(const char* imgPath) {}
};

// Copy & Swap 은 자주 Pimpl 관용구와 함께 쓰이곤 한다.
struct PrettyMenuImpl
{
    shared_ptr<Image> bgImage;
    int imageChanges;
};

class PrettyMenu
{
    mutex mtx;
    /* 여기서 private 으로 캡슐화가 되기 때문에
     * rettyMenuImpl 은 public 인 구조체로 만들어도 괜찮다. */
    shared_ptr<PrettyMenuImpl> pImpl;

public:
    // Copy & Swap 을 통한 강한 보장의 함수
    void changeBackground_CopyNSwap(const char* imgPath)
    {
        lock_guard<mutex> lg(mtx);

        // 사본을 만든다.
        shared_ptr<PrettyMenuImpl> pTemp(new PrettyMenuImpl(*pImpl));

        // 사본에 변경 사항을 적용한다.
        pTemp->bgImage.reset(new Image(imgPath));
        ++pTemp->imageChanges;

        // 원본과 사본을 바꾼다.
        swap(pImpl, pTemp);
    }

    /* 강한 예외 안전성을 보장하는 함수들로만 이뤄졌다고 해서
     * 그 함수까지 강한 보장이 되는 것은 아니다. */
    void someFunc_not_strong(int a, int b)
    {
        // f1 호출이 성공적으로 끝나 일부 자료가 변경됐다.
        f1_strong(a);

        /* f2 호출에서 예외가 발생해 나머지는 변경되지 않고 남으면
         * f1 이 변경된 것에 대해서는 되돌릴 추가적인 처리가 필요하다. */
        f2_strong(b);
    }

    void f1_strong(int) {}
    void f2_strong(int) {}

    // 내부에서 예외 안전성을 제공하지 않는 함수를 하나라도 호출하면
    void someFunc_no_guarantee(int a, int b)
    {
        f1_strong(a);

        /* 그 함수도 예외에 안전하지 않은 함수가 될 수 밖에 없다.
         *
         * 따라서, 예외 안전성은 꼭 문서화해 인수인계자가 알 수 있도록 해야 한다. */
        f2_no_guarantee(b);
    }

    void f2_no_guarantee(int) {}
};

int main(int argc, char* argv[])
{
    

    return 0;
}
