
#ifndef LINKEDLIST_SKIPLIST_H
#define LINKEDLIST_SKIPLIST_H

#include <iostream>
#include <vector>
#include <random>
#include <optional>

template<typename K,typename V>
class SkipListNode{
public:
    K key;
    V value;
    std::vector<SkipListNode*> forward;

    SkipListNode(const K& k, const V& v, int level)
            : key(k), value(v), forward(level, nullptr) {}
};

template<typename K,typename V>
class SkipList{
private:
    int maxLevel;
    int currentLevel;
    SkipListNode<K,V>* head;

    int randomLevel();

public:
    SkipList(int maxLvl=4);
    ~SkipList();

    std::optional<V> find(const K& key);
    void insert(const K& key,const V& value);
    bool remove(const K& key);
    void printSkipList();
};

template<typename K,typename V>
SkipList<K,V>::SkipList(int maxLvl)
    : maxLevel{maxLvl},currentLevel{1}{
    head=new SkipListNode<K,V>(K(),V(),maxLvl);
}

template<typename K,typename V>
SkipList<K,V>::~SkipList(){
    while (head)
    {
        SkipListNode<K,V>* temp = head;
        head=head->forward[0];
        delete temp;
    }
}

template<typename K,typename V>
std::optional<V> SkipList<K,V>::find(const K& key){
    SkipListNode<K,V>* current=head;
    for (int i = currentLevel-1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key){
            current = current->forward[i];
        }
    }
    current=current->forward[0];
    if (current && current->key == key){
        return current->value;
    }
    return std::nullopt;
}

template<typename K,typename V>
void SkipList<K,V>::insert(const K& key,const V& value){
    SkipListNode<K,V>* update[maxLevel];
    SkipListNode<K,V>* current = head;
    for (int i = currentLevel - 1; i >= 0 ; i--) {
        while (current->forward[i] && current->forward[i]->key < key){
            current=current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current && current->key == key){
        current->value=value;
    } else {
        int newLevel = randomLevel();
        if (newLevel > currentLevel){
            for (int i = currentLevel; i < newLevel; i++) {
                update[i] = head;
            }
            currentLevel = newLevel;
        }

        SkipListNode<K,V>* newNode= new SkipListNode<K,V>(key,value,newLevel);
        for (int i = 0; i < newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

template<typename K,typename V>
bool SkipList<K,V>::remove(const K &key) {
    SkipListNode<K,V>* update[maxLevel];
    SkipListNode<K,V>* current = head;
    for (int i = currentLevel-1; i >= 0; i--) {
        while (current->forward[i] && current->forward[i]->key < key){
            current=current->forward[i];
        }
        update[i] = current;
    }
    current = current->forward[0];
    if (current && current->key == key){
        for (int i = 0; i < currentLevel; i++) {
            if (update[i]->forward[i] != current){
                break;
            }
            update[i]->forward[i]=current->forward[i];
        }
        delete current;
        while (currentLevel > 1 && head->forward[currentLevel - 1] == nullptr){
            currentLevel--;
        }
        return true;
    }
    return false;
}

template<typename K,typename V>
int SkipList<K,V>::randomLevel() {
    int level = 1;
    while ((rand() & 1) && level < maxLevel){
        level++;
    }
    return level;
}

template<typename K,typename V>
void SkipList<K,V>::printSkipList()
{
    for (int i = currentLevel-1; i >=0 ; i--) {
        SkipListNode<K,V>* current = head;

        while (current->forward[0] != nullptr)
        {
            if (current->forward.size() > i){
                std::cout<<current->forward[0]->key<<"\t";
            } else{
                std::cout<<"\t";
            }
            current = current->forward[0];
        }
        std::cout<<std::endl;
    }
}

#endif //LINKEDLIST_SKIPLIST_H
