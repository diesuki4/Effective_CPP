#include <iostream>

using namespace std;

/*
 * 자원 관리 클래스에서 관리되는 자원은 외부에서 접근할 수 있도록 하자
 */

/*
 * 아래처럼 C API 에서 사용해야 하는 등
 * 실제 자원에 접근해야 하는 경우도 다반사다.
 */
struct FontHandle { };
FontHandle getFont() { return FontHandle(); }
void releaseFont(FontHandle fh) { }
void changeFont(FontHandle fh, float newFontSize) { }

// 폰트 자원 관리 클래스
class Font
{
    FontHandle f;

public:
    explicit Font(FontHandle fh) : f(fh) { }

    /*
     * 따라서, 자원 관리 객체는
     * 실제 자원에 접근하는 방법을 제공해야 한다.
     * 
     * 접근 방법은
     * 옳게 쓰기는 쉽게, 틀리게 쓰기는 어렵게
     * 제공해야 한다.
     * 
     * RAII 클래스는 애초에
     * 데이터 은닉이 목적이 아니기에
     * 캡슐화에 위배되어도 문제가 없다.
     * 
     * 좋은 캡슐화는
     * 사용자가 볼 필요가 없는 정보는 가리지만,
     * 꼭 접근해야 하는 데이터는 열어주는 것이다.
     * 
     * shared_ptr 도 참조 카운팅 메커니즘은 가리지만,
     * Raw 포인터에 대한 접근은 열어두고 있다.
     */

    /*
     * 이것은 명시적 변환이다.
     * 대부분의 경우에서는 이 방법이 나을 때가 많다.
     */
    FontHandle get() const      { return f; }
    /*
     * 이것은 암시적 변환이다.
     * 편의성을 제공하기 위해 사용된다.
     */
    operator FontHandle() const { return f; }

    ~Font() { releaseFont(f); }
};

int main(int argc, char* argv[])
{
    Font font(getFont());

    // 명시적 변환
    changeFont(font.get(), 12.F);
    // 암시적 변환
    changeFont(font, 12.F);

    /*
     * 그렇다고 암시적 변환이 마냥 좋은 것만은 아니다.
     * 
     * Font font2 = font; 를 쓰려다 헷갈려서
     * 아래처럼 작성해도 허용되기 때문이다.
     * 
     * font 가 소멸할 때 FontHandle 이 해제되면,
     * font2 는 해제된 폰트를 참조하게 된다.
     */
    FontHandle font2 = font;

    return 0;
}
