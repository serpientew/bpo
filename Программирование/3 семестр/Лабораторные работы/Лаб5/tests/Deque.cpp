//
// Created by admin on 27.10.2025.
//
#include <iostream>
using namespace std;

// ДЕК на двусвязном списке
struct Node {
    int data;
    Node* next = nullptr;
    Node* prev = nullptr;
};

struct Deque {
    Node* Head = nullptr;  // указатель на начало дека
    Node* Tail = nullptr;  // указатель на конец дека
    int size = 0;          // текущий размер дека

    // ДОБАВИТЬ в КОНЕЦ дека
    void addToBack(int x) {
        if (size >= 1000) return;    // проверка переполнения

        Node* NewNode = new Node;    // создаем новый узел
        NewNode->data = x;           // сохраняем данные

        if (Tail) {                  // если хвост существует
            Tail->next = NewNode;    // старый хвост указывает на новый
            NewNode->prev = Tail;    // новый указывает на старый хвост
        } else {                     // если дек пустой
            Head = NewNode;          // голова = новый узел
        }

        Tail = NewNode;              // обновляем хвост
        size++;                      // увеличиваем счетчик
    }

    // УДАЛИТЬ с НАЧАЛА дека
    int removeFromFront() {
        if (size == 0) return 0;     // проверка пустоты

        Node* temp = Head;           // сохраняем указатель на голову
        int x = temp->data;          // сохраняем данные

        Head = Head->next;           // перемещаем голову вперед
        if (Head) {                  // если дек не пустой
            Head->prev = nullptr;    // убираем ссылку на старую голову
        } else {                     // если дек стал пустым
            Tail = nullptr;          // обнуляем хвост
        }

        delete temp;                 // освобождаем память
        size--;                      // уменьшаем счетчик
        return x;                    // возвращаем значение
    }

    // ДОБАВИТЬ в НАЧАЛО дека
    void addToFront(int x) {
        if (size >= 1000) return;    // проверка переполнения

        Node* NewNode = new Node;    // создаем новый узел
        NewNode->data = x;           // сохраняем данные

        if (Head) {                  // если голова существует
            NewNode->next = Head;    // новый указывает на старую голову
            Head->prev = NewNode;    // старая голова указывает на новый
        } else {                     // если дек пустой
            Tail = NewNode;          // хвост = новый узел
        }

        Head = NewNode;              // обновляем голову
        size++;                      // увеличиваем счетчик
    }

    // УДАЛИТЬ с КОНЦА дека
    int removeFromBack() {
        if (size == 0) return 0;     // проверка пустоты

        Node* temp = Tail;           // сохраняем указатель на хвост
        int x = temp->data;          // сохраняем данные

        Tail = Tail->prev;           // перемещаем хвост назад
        if (Tail) {                  // если дек не пустой
            Tail->next = nullptr;    // убираем ссылку на старый хвост
        } else {                     // если дек стал пустым
            Head = nullptr;          // обнуляем голову
        }

        delete temp;                 // освобождаем память
        size--;                      // уменьшаем счетчик
        return x;                    // возвращаем значение
    }
};
