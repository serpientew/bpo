#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// Ввод с возвратом головы
Node* inputSinglyLinkedList() {
    Node* head = nullptr;
    Node* tail = nullptr;
    int value;

    cout << "Введите числа для списка (-1 для окончания ввода):" << endl;

    while (cin >> value && value != -1) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Функция для вывода списка
void printList(Node* head) {
    Node* current = head;
    cout << "Список: ";
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << " -> nullptr" << endl;
}


bool hasDuplicates(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return false; // Пустой список или один элемент - дубликатов нет
    }

    Node* current = head;

    // Для каждого элемента проверяем все последующие
    while (current != nullptr) {
        Node* runner = current->next; // Указатель для проверки последующих элементов

        while (runner != nullptr) {
            if (current->data == runner->data) {
                cout<<"Дубликат найден!";
                return true;

            }
            runner = runner->next;
        }

        current = current->next;
    }
    cout<<" Дубликатов не найдено";
    return false;

}
int main() {
    Node* head = inputSinglyLinkedList();
    printList(head);

    bool has = hasDuplicates(head);

    return 0;
}