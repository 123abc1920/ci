#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node *next;

    Node(const T &value)
    {
        data = value;
        next = nullptr;
    }
};

template <typename T>
class Iterator
{
private:
    Node<T> *current;

public:
    Iterator(T *content, int count)
    {
        Node<T> *head = new Node<T>(content[0]);

        Node<T> *node = head;
        for (int i = 1; i < count; i++)
        {
            node->next = new Node<T>(content[i]);
            node = node->next;
        }

        current = head;
    }

    ~Iterator()
    {
    }

    bool hasNext()
    {
        return current != nullptr;
    }

    T next()
    {
        T value = current->data;
        current = current->next;
        return value;
    }
};

#endif