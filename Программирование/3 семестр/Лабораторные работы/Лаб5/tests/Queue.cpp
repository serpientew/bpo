//Очередь FIFO

// ОЧЕРЕДЬ на массиве
struct Queue {
    int data[1000];      // массив для хранения элементов
    int size = 0;        // текущий размер очереди
    int head = 0;        // указатель на начало очереди
    int tail = 0;        // указатель на конец очереди

    // ДОБАВИТЬ в очередь
    void enqueue(int x) {
        if (size >= 1000) return;    // проверка переполнения
        data[tail] = x;              // добавляем элемент в конец
        tail = (tail + 1) % 1000;    // циклически двигаем хвост
        size++;                      // увеличиваем счетчик
    }

    // УДАЛИТЬ из очереди
    int dequeue() {
        if (size == 0) return 0;     // проверка пустоты
        int x = data[head];          // сохраняем данные из начала
        head = (head + 1) % 1000;    // циклически двигаем голову
        size--;                      // уменьшаем счетчик
        return x;                    // возвращаем значение
    }

    // ПОЛУЧИТЬ первый элемент
    int front() {
        if (size == 0) return 0;     // проверка пустоты
        return data[head];           // возвращаем первый элемент
    }

    // ПОЛУЧИТЬ последний элемент
    int back() {
        if (size == 0) return 0;     // проверка пустоты
        return data[(tail - 1 + 1000) % 1000]; // возвращаем последний элемент
    }
};

// ОЧЕРЕДЬ на связном списке
struct QueueNode {
    int data;
    QueueNode* next = nullptr;
};

struct LinkedQueue {
    QueueNode* Head = nullptr;  // указатель на начало очереди
    QueueNode* Tail = nullptr;  // указатель на конец очереди
    int size = 0;               // текущий размер очереди

    // ДОБАВИТЬ в очередь
    void enqueue(int x) {
        QueueNode* NewNode = new QueueNode;  // создаем новый узел
        NewNode->data = x;                   // сохраняем данные

        if (Tail) {                          // если очередь не пустая
            Tail->next = NewNode;            // старый хвост указывает на новый
        } else {                             // если очередь пустая
            Head = NewNode;                  // голова = новый узел
        }

        Tail = NewNode;                      // обновляем хвост
        size++;                              // увеличиваем счетчик
    }

    // УДАЛИТЬ из очереди
    int dequeue() {
        if (size == 0) return 0;             // проверка пустоты

        QueueNode* temp = Head;              // сохраняем указатель на голову
        int x = temp->data;                  // сохраняем данные

        Head = Head->next;                   // перемещаем голову вперед
        if (!Head) {                         // если очередь стала пустой
            Tail = nullptr;                  // обнуляем хвост
        }

        delete temp;                         // освобождаем память
        size--;                              // уменьшаем счетчик
        return x;                            // возвращаем значение
    }
};