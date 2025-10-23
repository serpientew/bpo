#include <iostream>
using namespace std;

struct Node {
    double data;
    Node *next;
    Node *prev;
};

typedef Node *PNode;

PNode createNode(double val) {
    PNode newNode = new Node;
    newNode->data = val;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

PNode inputDoublyLinkedList() {
    PNode head = nullptr;
    PNode tail = nullptr;
    double value;

    cout << "Введите действительные числа для двусвязного списка (-1 для окончания ввода):" << endl;

    while (cin >> value && value != -1) {
        PNode newNode = createNode(value);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return head;
}

PNode addToHeadAndTail(PNode anyNode, double firstNum, double secondNum) {
    // Находим голову списка
    PNode head = anyNode;
    while (head->prev != nullptr) {
        head = head->prev;
    }

    // Находим хвост списка
    PNode tail = anyNode;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // Добавляем первое число в начало
    PNode newHead = createNode(firstNum);
    newHead->next = head;
    head->prev = newHead;

    // Добавляем второе число в конец
    PNode newTail = createNode(secondNum);
    tail->next = newTail;
    newTail->prev = tail;

    cout << "Добавлено: " << firstNum << " в начало, " << secondNum << " в конец" << endl;

    return newHead;
}

void printForward(PNode head) {
    PNode current = head;
    cout << "Список: ";
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " <-> ";
        }
        current = current->next;
    }
    cout << " -> nullptr" << endl;
}

PNode getNodeAtPosition(PNode head, int position) {
    PNode current = head;
    int count = 0;

    while (current != nullptr && count < position) {
        current = current->next;
        count++;
    }

    return current;
}

int main() {
    PNode head = inputDoublyLinkedList();
    printForward(head);

    int number;
    cout << "Введите порядковый номер узла: ";
    cin >> number;

    PNode someNode = getNodeAtPosition(head, number - 1);

    if (someNode != nullptr) {
        cout << "\nВыбран узел со значением: " << someNode->data << endl;

        double firstNum, secondNum;
        cout << "Введите первое число для добавления в начало: ";
        cin >> firstNum;
        cout << "Введите второе число для добавления в конец: ";
        cin >> secondNum;

        // Вызываем функцию и получаем новую голову
        cout << "Вызов функции:" << endl;
        head = addToHeadAndTail(someNode, firstNum, secondNum);

        // Выводим измененный список
        cout << "\nСписок после добавления:" << endl;
        printForward(head);
    } else {
        cout << "Узел с таким номером не найден!" << endl;
    }

    return 0;
}
