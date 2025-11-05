//
// Created by admin on 04.11.2025.
//

#include <iostream>
using namespace std;

// Структура узла бинарного дерева
struct Node {
    int data;         // Данные узла
    Node *left = nullptr;  // Указатель на левое поддерево
    Node *right = nullptr; // Указатель на правое поддерево
};

typedef Node *PNode; // Псевдоним для указателя на Node

// Функция удаления дерева (освобождение памяти)
void DeleteTree(PNode root) {
    if (root == nullptr) return;        // Базовый случай: пустое дерево
    DeleteTree(root->left);             // Рекурсивно удаляем левое поддерево
    DeleteTree(root->right);            // Рекурсивно удаляем правое поддерево
    delete root;                        // Удаляем текущий узел
}

// Функция построения сбалансированного дерева из массива (pre-order с балансировкой)
PNode MakeTree(int arrayOfData[], int from, int sizeOfDataArray) {
    int n1, n2;
    if (sizeOfDataArray == 0) return nullptr;  // Базовый случай: пустой массив

    PNode Tree = new Node;              // Создаем новый узел
    n1 = sizeOfDataArray / 2;           // Размер левого поддерева: ⌊n/2⌋
    n2 = sizeOfDataArray - n1 - 1;      // Размер правого поддерева: n - ⌊n/2⌋ - 1

    Tree->data = arrayOfData[from];     // Pre-order: первый элемент -> корень

    // Рекурсивно строим левое поддерево из следующих n1 элементов
    Tree->left = MakeTree(arrayOfData, from + 1, n1);

    // Рекурсивно строим правое поддерево из оставшихся n2 элементов
    Tree->right = MakeTree(arrayOfData, from + 1 + n1, n2);

    return Tree;
}

// Функция красивого вывода дерева в консоль
void PrintTree(PNode root, string prefix = "", bool isLeft = true) {
    if (root == nullptr) return;  // Базовый случай: пустое дерево

    // Сначала выводим правое поддерево (оно будет сверху)
    PrintTree(root->right, prefix + (isLeft ? "│   " : "    "), false);

    // Выводим текущий узел с отступом и соединительными линиями
    cout << prefix;
    cout << (isLeft ? "└── " : "┌── ");  // Выбираем символ соединения
    cout << root->data << endl;

    // Затем выводим левое поддерево (оно будет снизу)
    PrintTree(root->left, prefix + (isLeft ? "    " : "│   "), true);
}

// Функция проверки, являются ли два дерева зеркальными
bool areMirror(PNode a, PNode b) {
    // 1. Оба nullptr - дошли до листьев одновременно
    if (a == nullptr && b == nullptr) return true;

    // 2. Только один nullptr - структуры разные
    if (a == nullptr || b == nullptr) return false;

    // 3. Проверяем условия зеркальности:
    return a->data == b->data &&                    // Данные в корнях равны
           areMirror(a->left, b->right) &&          // ЛЕВОЕ(a) зеркально ПРАВОМУ(b)
           areMirror(a->right, b->left);            // ПРАВОЕ(a) зеркально ЛЕВОМУ(b)
}

int main() {
    int size1, size2, temp;

    // Ввод первого дерева
    cout << "Введите размер первого дерева: ";
    cin >> size1;
    int *data1 = new int [size1];  // Динамический массив для данных первого дерева
    cout << "Введите значения для первого дерева>>"<<endl;
    for (int i = 0; i < size1; i++) {
        cout << i + 1 << " значение: ";
        cin >> temp;
        data1[i] = temp;  // Заполняем массив данными
    }

    // Построение и вывод первого дерева
    PNode root1 = MakeTree(data1, 0, size1);
    PrintTree(root1);

    // Ввод второго дерева
    cout << "Введите размер второго дерева: ";
    cin >> size2;
    int *data2 = new int [size2];  // Динамический массив для данных второго дерева
    cout << "Введите значения для второго дерева>>"<<endl;
    for (int i = 0; i < size2; i++) {
        cout << i + 1 << "значение: ";
        cin >> temp;
        data2[i] = temp;  // Заполняем массив данными
    }

    // Построение и вывод второго дерева
    PNode root2 = MakeTree(data2, 0, size2);
    PrintTree(root2);

    // Проверка на зеркальность и вывод результата
    bool are = (areMirror(root1, root2));
    cout << "Деревья зеркальны? (0/1): " << are;

    // Освобождение памяти
    DeleteTree(root1);    // Удаляем первое дерево
    DeleteTree(root2);    // Удаляем второе дерево
    delete[] data1;       // Освобождаем массив данных первого дерева
    delete[] data2;       // Освобождаем массив данных второго дерева

    return 1;
}