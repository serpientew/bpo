//
// Created by admin on 27.10.2025.
//

// СТЕК НА МАССИВЕ
struct Stack {
    int a[1000];    // массив для хранения элементов
    int size = 0;   // текущий размер стека (и указатель на вершину)

    void addToStack(int x) {
        if (size >= 1000) return;  // проверка переполнения
        a[size] = x;               // добавляем элемент в конец массива
        size++;                    // увеличиваем размер/указатель
    };

    int removeFromStack() {
        if (size == 0) return 0;   // проверка пустоты
        size--;                    // уменьшаем размер/указатель
        int x = a[size];
        return x;
    };
};

// ВИЗУАЛИЗАЦИЯ СВЯЗАННОГО СТЕКА:
// Head → [10] → [20] ← Tail

// СТЕК НА СВЯЗАННОМ СПИСКЕ
struct NodeStack {
    Node* Head;  // указатель на вершину стека (последний добавленный)
    Node* Tail;  // указатель на дно стека (первый добавленный) - обычно не нужен
};

struct Node {
    int data;
    Node* next = nullptr;  // указатель на следующий узел
    Node* prev = nullptr;  // указатель на предыдущий узел
};

// Добавление в связанный стек
void addToStack(NodeStack &S, int x) {
    Node* NewNode = new Node;
    NewNode->data = x;
    NewNode->next = S.Head;    // новый узел указывает на старую вершину

    if (S.Head) {
        S.Head->prev = NewNode; // старый верх теперь указывает на новый
    }
    S.Head = NewNode;          // обновляем вершину стека

    if (!S.Tail) S.Tail = S.Head; // если стек был пуст, инициализируем хвост
}

// Удаление из связанного стека
int removeFromStack(NodeStack &S) {
    if (!S.Head) return 0;     // проверка пустоты стека

    int x = S.Head->data;      // берем данные с вершины
    S.Head = S.Head->next;     // перемещаем вершину на следующий узел

    if (S.Head) {
        S.Head->prev = nullptr; // убираем ссылку на старую вершину
    } else {
        S.Tail = nullptr;      // если стек стал пустым, обнуляем хвост
    }
    return x;
}