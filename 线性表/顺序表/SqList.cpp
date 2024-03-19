#include "SqList.h"
#include <iostream>

Elem::Elem()
{
    m_number=objCount++;
    std::cout<<"constructor";
}

void Elem::modify(const std::string& name,unsigned int price)
{
    m_bookName=name;
    m_price=price;
}

unsigned int Elem::getNumber()
{
    return m_number;
}

std::string Elem::getName()
{
    return m_bookName;
}

unsigned int Elem::getPrice()
{
    return m_price;
}

void Elem::adjNumber(int factor)
{
    m_number=factor;
}

SqList::SqList(unsigned int length)
    :m_length{length},m_ptrElem(std::make_unique<Elem[]>(length))
{}

bool SqList::isEmpty() const
{
    if (m_currentLen!=0)
    {
        return false;
    }
    return true;
}

void SqList::clearList()
{
    m_currentLen=0;
}

std::optional<unsigned int> SqList::locateElem(unsigned int number) const
{
    for (size_t i = 0; i < m_currentLen; i++)
    {
        if (m_ptrElem[i].getNumber()==number)
        {
            std::cout<<"find element of number: "<<number<<std::endl;
            return i;
        }
    }

    std::cout<<"element of number: "<<number<<" not find"<<std::endl;
    return std::nullopt;
}

std::optional<unsigned int> SqList::locateElem(const std::string& bookName) const
{
    for (size_t i = 0; i < m_currentLen; i++)
    {
        if (m_ptrElem[i].getName()==bookName)
        {
            std::cout<<"find element of bookName: "<<bookName<<std::endl;
            return i;
        }
    }

    std::cout<<"element of bookName: "<<bookName<<" not find"<<std::endl;
    return std::nullopt;
}

std::optional<Elem> SqList::getElem(int number) const
{
    auto index = locateElem(number);
    if (index.has_value())
    {
        return m_ptrElem[index.value()];
    }
    return std::nullopt;
}

std::optional<Elem> SqList::getElem(const std::string& bookName) const
{
    auto index = locateElem(bookName);
    if (index.has_value())
    {
        return m_ptrElem[index.value()];
    }
    return std::nullopt;    
}

bool SqList::borderCheck(unsigned int index) const
{
    if (index >= m_currentLen)
    {
        return false;
    }
    return true;
}

bool SqList::modify(unsigned int index,const std::string& changedName,unsigned int changedPrice)
{
    if( borderCheck(index) )
    {
        m_ptrElem[index].modify(changedName,changedPrice);
        std::cout<<"modified successfully."<<std::endl;
        return true;
    }
    std::cout<<"out of current length"<<std::endl;
    return false;  
}

bool SqList::insertElem(std::string bookName,unsigned int price,unsigned int index)
{
    if( borderCheck(index) )
    {
        if (m_length-m_currentLen>=1)
        {
            for (size_t i = m_currentLen+1; i > index ; i--)
            {
                m_ptrElem[i]=m_ptrElem[i-1];
                m_ptrElem[i].adjNumber(m_ptrElem[i-1].getNumber()+1); //插入元素，number编号往后+1
            }

            modify(index,bookName,price);
            std::cout<<"inserted successfully."<<std::endl;
            m_currentLen++;  
            return true;
        }
    }else if (index < m_length)
    {

        m_ptrElem[m_currentLen].modify(bookName,price); //大于
        m_currentLen++; 
        std::cout<<"inserted successfully."<<std::endl;
        return true;
    }
    std::cout<<"out of max length"<<std::endl;
    return false;
}

bool SqList::delect(unsigned int index)
{
    if( borderCheck(index) )
    {
        for (size_t i = index; i < m_currentLen-1; i++)
        {
            m_ptrElem[i]=m_ptrElem[i+1];
            m_ptrElem[i].adjNumber(m_ptrElem[i].getNumber()-1); //删除元素，number编号-1
        }
        m_currentLen--;
        return true;
    }
    std::cout<<"out of current length"<<std::endl;
    return false;
}

void SqList::delectList()
{   
    m_currentLen=0;
    m_length=0;
    m_ptrElem.reset();
    std::cout<<"delect all elements."<<std::endl;
}

void SqList::display() const
{
    for (size_t i = 0; i < m_currentLen; i++)
    {
        std::cout<<m_ptrElem[i].getNumber()<<" "
            <<m_ptrElem[i].getName()<<" "
            <<m_ptrElem[i].getPrice()
            <<std::endl;
    }
    std::cout<<"display all."<<std::endl;
}
