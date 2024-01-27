/*
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Fast_Pimpl
 * https://www.cleeus.de/w/blog/2017/03/10/static_pimpl_idiom.html
 * https://www.reddit.com/r/cpp/comments/cs49u/pimpl_idiom_without_dynamic_memory_allocation/
 * 
 * https://en.cppreference.com/w/cpp/types/aligned_storage
 * https://stackoverflow.com/questions/71828288/why-is-stdaligned-storage-to-be-deprecated-in-c23-and-what-to-use-instead#answer-71828512
 * https://minusi.tistory.com/entry/메모리-얼라인먼트Memory-Alignment
 * https://univ-developer.tistory.com/entry/c6
 * https://www.gamedeveloper.com/programming/data-alignment-part-2-objects-on-the-heap-and-the-stack
 *
 * https://en.wikipedia.org/wiki/Opaque_pointer */
#pragma once

#include <string>
#include <memory>

using namespace std;

class PersonImpl;
class Date;
class Address;

class Person
{
    /* 구현 세부의 크기
     * 미리 직접 계산해 적고, 생성자에서 static_assert() 를 통해 한번 더 확인한다.
     *
     * sizeof(PersonImpl) 을 쓸 수 없는 이유는 아직 크기를 모르기 때문. */
    static constexpr size_t SIZE = 32;
    // 메모리 접근 속도, 캐싱 효율성 등을 위해 정렬된 메모리를 할당 받는다.
    static constexpr size_t ALIGN = alignof(max_align_t);
    /* 스택 버퍼
     * (buffer 주소 % ALIGN) == 0 을 항상 만족하는 위치에 할당된다.
     *
     * 이렇게 어떤 데이터가 담길지 모르는 객체를 Opaque object 라고 한다. */
    alignas(ALIGN) char buffer[SIZE];

    /* 어떤 데이터가 담기는지 모르는 포인터를 Opaque pointer 라고 한다. */
    shared_ptr<PersonImpl> pImpl;

public:
    Person(const string& name, const Date& birthDay, const Address& addr);

    string name()     const;
    Date birthDate()  const;
    Address address() const;
};
