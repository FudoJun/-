#ifndef SQLIST_H
#define SQLIST_H

#include <memory>
#include <string>
#include <string_view>
#include <optional>

class Elem
{
private:

    static inline unsigned int objCount{};
    unsigned int m_number{};
    std::string m_bookName{};
    unsigned int m_price{};

public:
    Elem();
    virtual ~Elem()=default;

    void modify(const std::string& name,unsigned int price);

    unsigned int getNumber();
    std::string getName();
    unsigned int getPrice();
    void adjNumber(int factor);

};


class SqList
{
private:

    unsigned int m_length{};
    unsigned int m_currentLen{};
    std::unique_ptr<Elem[]> m_ptrElem{};

public:

    SqList(unsigned int length);
    virtual ~SqList()=default;

    bool isEmpty() const;
    bool borderCheck(unsigned int index) const;
    void clearList();
    void display() const;

    std::optional<unsigned int> locateElem(unsigned int number) const;
    std::optional<unsigned int> locateElem(const std::string& bookName) const;
    std::optional<Elem> getElem(int number) const;
    std::optional<Elem> getElem(const std::string& bookName) const;

    bool modify(unsigned int index,const std::string& changedName,unsigned int changedPrice);
    bool insertElem(std::string bookName,unsigned int price,unsigned int index);
    bool delect(unsigned int index);
    void delectList();

};


#endif