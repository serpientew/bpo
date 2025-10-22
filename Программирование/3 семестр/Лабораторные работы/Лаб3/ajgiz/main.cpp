#include <iostream>
//
// Created by admin on 14.10.2025.
//
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

struct Train {
    int number;
    char destination[100];
    char days[100];
    char timeArrival[10];
    char timeParking[10];
};

Train* train = nullptr;
int trainCount = 0;

void printMenu() {
    printf("\n");
    printf("|1| - Ввод с клавиатуры\n");
    printf("|2| - Загрузка из файла\n");
    printf("|3| - Сортировка\n");
    printf("|4| - Поиск\n");
    printf("|5| - Изменение\n");
    printf("|6| - Удаление\n");
    printf("|7| - Вывод таблицы\n");
    printf("|8| - Сохранить в файл\n");
    printf("|9| - Выход\n");
    printf("Выберите действие: ");
}

void printTrainsTable() {
    printf("\n+---------+--------------------------+-----------------+------------+------------+\n");
    printf("| № поезда| Пункт назначения        | Дни следования  | Прибытие   | Стоянка    |\n");
    printf("+---------+--------------------------+-----------------+------------+------------+\n");

    for (int i = 0; i < trainCount; i++) {
        printf("| %-7d | %-24s | %-15s | %-10s | %-10s |\n",
               train[i].number, train[i].destination, train[i].days,
               train[i].timeArrival, train[i].timeParking);
    }
    printf("+---------+--------------------------+-----------------+------------+------------+\n");
    printf("Всего: %d\n", trainCount);
}

void inputFromKeyboard() {
    if (train != nullptr) delete[] train;

    printf("Количество поездов: ");
    scanf("%d", &trainCount);
    train = new Train[trainCount];

    for (int i = 0; i < trainCount; i++) {
        printf("Поезд %d: ", i + 1);
        scanf("%d %99s %99s %9s %9s",
              &train[i].number,
              train[i].destination,
              train[i].days,
              train[i].timeArrival,
              train[i].timeParking);
    }
    printf("Данные сохранены!\n");
}

void loadFromFile() {
    if (train != nullptr) delete[] train;

    ifstream file("trains.txt");
    if (!file) {
        printf("Файл trains.txt не найден!\n");
        getch();
        return;
    }

    // Считаем количество строк
    trainCount = 0;
    string line;
    while (getline(file, line)) trainCount++;

    file.clear();
    file.seekg(0);

    train = new Train[trainCount];

    for (int i = 0; i < trainCount; i++) {
        file >> train[i].number >> train[i].destination
             >> train[i].days >> train[i].timeArrival >> train[i].timeParking;
    }

    file.close();
    printf("Загружено %d поездов из файла!\n", trainCount);
}

void saveToFile() {
    if (trainCount == 0) {
        printf("Нет данных для сохранения!\n");
        getch();
        return;
    }

    ofstream file("trains.txt");
    for (int i = 0; i < trainCount; i++) {
        file << train[i].number << " " << train[i].destination << " "
             << train[i].days << " " << train[i].timeArrival << " " << train[i].timeParking << endl;
    }
    file.close();
    printf("Данные сохранены в файл!\n");
}

void sortByNumber() {
    for (int i = 0; i < trainCount - 1; i++) {
        for (int j = i + 1; j < trainCount; j++) {
            if (train[j].number < train[i].number) {
                swap(train[i], train[j]);
            }
        }
    }
    printf("Сортировка завершена!\n");
}

void searchTrain() {
    int field;
    char what[100];

    printf("Поиск по: 1-номер 2-назначение 3-дни 4-прибытие 5-стоянка: ");
    scanf("%d", &field);
    printf("Значение: ");
    scanf("%99s", what);

    for (int i = 0; i < trainCount; i++) {
        bool match = false;
        switch (field) {
            case 1: match = (train[i].number == atoi(what)); break;
            case 2: match = (strcmp(train[i].destination, what) == 0); break;
            case 3: match = (strcmp(train[i].days, what) == 0); break;
            case 4: match = (strcmp(train[i].timeArrival, what) == 0); break;
            case 5: match = (strcmp(train[i].timeParking, what) == 0); break;
        }

        if (match) {
            printf("Найден: №%d %s %s %s %s\n",
                   train[i].number, train[i].destination, train[i].days,
                   train[i].timeArrival, train[i].timeParking);
            getch();
            return;
        }
    }
    printf("Не найден!\n");
    getch();
}

void changeTrain() {
    printTrainsTable();

    int id;
    printf("Номер поезда для изменения: ");
    scanf("%d", &id);

    if (id < 1 || id > trainCount) {
        printf("Неверный номер!\n");
        getch();
        return;
    }

    int field;
    char newValue[100];

    printf("Поле (1-номер 2-назначение 3-дни 4-прибытие 5-стоянка): ");
    scanf("%d", &field);
    printf("Новое значение: ");
    scanf("%99s", newValue);

    int index = id - 1;
    switch (field) {
        case 1: train[index].number = atoi(newValue); break;
        case 2: strcpy(train[index].destination, newValue); break;
        case 3: strcpy(train[index].days, newValue); break;
        case 4: strcpy(train[index].timeArrival, newValue); break;
        case 5: strcpy(train[index].timeParking, newValue); break;
    }

    printf("Изменено!\n");
    getch();
}

void deleteTrain() {
    printTrainsTable();

    int id;
    printf("Номер поезда для удаления: ");
    scanf("%d", &id);

    if (id < 1 || id > trainCount) {
        printf("Неверный номер!\n");
        getch();
        return;
    }

    int index = id - 1;
    for (int i = index; i < trainCount - 1; i++) {
        train[i] = train[i + 1];
    }
    trainCount--;

    printf("Удалено!\n");
    getch();
}

int main() {
    int choice;
bool flag = true;
    printf("=== СИСТЕМА УПРАВЛЕНИЯ ПОЕЗДАМИ ===\n");

    while (true) {
        printMenu();
        cin>>choice;

        switch (choice) {
            case 1: inputFromKeyboard(); break;
            case 2: loadFromFile(); break;
            case 3: sortByNumber(); break;
            case 4: searchTrain(); break;
            case 5: changeTrain(); break;
            case 6: deleteTrain(); break;
            case 7: printTrainsTable(); break;
            case 8: saveToFile(); break;
            case 9:
                if (train != nullptr) delete[] train;
                return 0;
        }

        printf("Нажмите любую клавишу...");
        getch();
    }
}
