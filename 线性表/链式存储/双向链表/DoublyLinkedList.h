#ifndef DOUBLELINKLIST_H
#define DOUBLELINKLIST_H

#include <iostream>
#include <optional>

template<typename T>
class DoublyLinkedList;

template<typename T>
class Node
{
    friend class DoublyLinkedList<T>; // 声明DoublyLinkedList为友元类
public:
    T data;
    Node* prev; // 指向前一个节点的指针
    Node* next; // 指向后一个节点的指针
    // 构造函数
    Node(const T& newData, Node* prevNode = nullptr, Node* nextNode = nullptr)
        : data(newData), prev(prevNode), next(nextNode) {}
};

template<typename T>
class DoublyLinkedList
{
private:
    Node<T> *head; // 指向链表头部的指针
    Node<T> *tail; // 指向链表尾部的指针
    size_t m_count{};

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr)
    {}
    ~DoublyLinkedList();

    void append(const T& newData);
    void prepend(const T& newData);
    void printForward() const;
    void printBackward() const;
    void deleteNode(std::optional<size_t> index=std::nullopt);
    void insertNode(size_t index,const T& newData);
    void locateNode(size_t index);
    void modifyNode(size_t index,const T& newData);

};

//////////////////////////////////////////////////////

template<typename T>
void DoublyLinkedList<T>::append(const T& newData)
{
    if (head== nullptr)
    {
        head = new Node<T>(newData);
        tail = head;
        m_count++;
    } else
    {
        Node<T>* newNode = new Node<T>(newData,tail, nullptr);
        tail->next = newNode;
        tail = newNode;
        m_count++;
    }
}

template<typename T>
void DoublyLinkedList<T>::prepend(const T &newData)
{
    if (head== nullptr)
    {
        head = new Node<T>(newData);
        tail = head;
        m_count++;
    } else
    {
        Node<T>* newNode = new Node<T>(newData, nullptr,head);
        head->prev = newNode;
        head = newNode;
        m_count++;
    }
}

template<typename T>
void DoublyLinkedList<T>::printForward() const
{
    Node<T>* current = head;
    while (current != nullptr)
    {
        std::cout<<current->data<<" "<<std::endl;
        current=current->next;
    }
}

template<typename T>
void DoublyLinkedList<T>::printBackward() const
{
    Node<T>* current = tail;
    while (current != nullptr)
    {
        std::cout<<current->data<<" "<<std::endl;
        current=current->prev;
    }
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    m_count=0;
    while (head != nullptr)
    {
        Node<T>* temp=head;
        head=head->next;
        delete temp;
    }
}

template<typename T>
void DoublyLinkedList<T>::deleteNode(std::optional<size_t> index)
{
    //如果index为空
    if (!index.has_value())
    {
        if (head != nullptr)
        {
            Node<T>* current = tail;
            tail=tail->prev;
            tail->next= nullptr;
            current->prev= nullptr;
            delete current;
            current = nullptr;
            m_count--;
        } else
        {
            std::cout<<"The linked list is empty and elements cannot be deleted!"<<std::endl;
        }
    }else if (index.value() < m_count && index.value() >= 0)
    {
        if (index.value()==0)
        {
            Node<T>* current = head;
            head=head->next;
            head->prev= nullptr;
            current->next= nullptr;
            delete current;
            current = nullptr;
            m_count--;
            return;
        }
        Node<T>* current = head->next;
        for (int i = 1; i < m_count; ++i) {
            if (i == index.value())
            {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                current->prev = nullptr;
                current->next = nullptr;
                delete current;
                current = nullptr;
                m_count--;
                return;
            }
            current = current->next;
        }
    } else
    {
        std::cout<<"Delete failed! Index out of range."<<std::endl;
        return;
    }
}

template<typename T>
void DoublyLinkedList<T>::insertNode(size_t index,const T& newData)
{
    if (index == 0)
    {
        prepend(newData);
        return;
    } else if (index > 0 && index < m_count)
    {
        Node<T>* current=head->next;
        for (int i = 1; i < m_count; ++i)
        {
            if (i == index && index != m_count-1)
            {
                Node<T>* newNode = new Node<T>(newData,current,current->next);
                current->next = newNode;
                newNode->next->prev = newNode;
                current = nullptr;
                m_count++;
                return;
            } else
            {
                Node<T>* newNode = new Node<T>(newData,tail, nullptr);
                tail->next = newNode;
                tail = newNode;
                m_count++;
                return;
            }
            current = current->next;
        }

    } else
    {
        std::cout<<"Insert failed! Index out of range."<<std::endl;
        return;
    }
}

template<typename T>
void DoublyLinkedList<T>::locateNode(size_t index)
{
    if (index >= m_count)
    {
        std::cout<<"Locate failed! Index out of range."<<std::endl;
        return;
    }
    Node<T>* current = head;
    for (int i = 0; i < m_count; ++i)
    {
        if (i == index)
        {
            std::cout<<"Value of element of index["
                <<index<<"] is : "<<current->data<<std::endl;
            current = nullptr;
            return;
        }
        current = current->next;
    }

}

template<typename T>
void DoublyLinkedList<T>::modifyNode(size_t index,const T& newData)
{
    if (index >= m_count)
    {
        std::cout<<"Modify failed! Index out of range."<<std::endl;
        return;
    }

    Node<T>* current = head;
    for (int i = 0; i < m_count; ++i)
    {
        if (i == index)
        {
            current->data = newData;
            std::cout<<"Modify successes."<<std::endl;
            current= nullptr;
            return;
        }
        current = current->next;
    }
}

#endif