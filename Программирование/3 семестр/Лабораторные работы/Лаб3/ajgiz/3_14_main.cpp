#include <iostream>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

struct Station {
    int trainNumber;
    char destination[100];
    char days[100];
    char arrivalTime[10];
    char stopTime[10];
};

Station* stationData = nullptr;
int dataCount = 0;

void printMenu() {
    cout << "\n";
    cout << "|1| - Ввод с клавиатуры\n";
    cout << "|2| - Загрузка из файла\n";
    cout << "|3| - Сортировка\n";
    cout << "|4| - Поиск\n";
    cout << "|5| - Изменение\n";
    cout << "|6| - Удаление\n";
    cout << "|7| - Вывод таблицы\n";
    cout << "|8| - Сохранить в файл\n";
    cout << "|9| - Выход\n";
    cout << "Выберите действие: ";
}

void printTable(Station* dataArray, int arraySize) {
    cout << "\n+---------+--------------------------+-----------------+------------+------------+\n";
    cout << "| № поезда| Пункт назначения        | Дни следования  | Прибытие   | Стоянка    |\n";
    cout << "+---------+--------------------------+-----------------+------------+------------+\n";

    for (int i = 0; i < arraySize; i++) {
        cout << "| " << dataArray[i].trainNumber << "\t | "
             << dataArray[i].destination << "\t\t | "
             << dataArray[i].days << "\t | "
             << dataArray[i].arrivalTime << "\t | "
             << dataArray[i].stopTime << "\t |" << endl;
    }
    cout << "+---------+--------------------------+-----------------+------------+------------+\n";
    cout << "Всего: " << arraySize << endl;
}

void inputFromKeyboard(Station* &dataArray, int &arraySize) {
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }

    cout << "Количество записей: ";
    cin >> arraySize;
    cin.ignore();

    dataArray = new Station[arraySize];

    for (int i = 0; i < arraySize; i++) {
        cout << "\nЗапись " << i + 1 << ":" << endl;

        cout << "Номер поезда: ";
        cin >> dataArray[i].trainNumber;
        cin.ignore();

        cout << "Пункт назначения: ";
        cin.getline(dataArray[i].destination, 100);

        cout << "Дни следования: ";
        cin.getline(dataArray[i].days, 100);

        cout << "Время прибытия (ЧЧ:ММ): ";
        cin.getline(dataArray[i].arrivalTime, 10);

        cout << "Время стоянки (ЧЧ:ММ): ";
        cin.getline(dataArray[i].stopTime, 10);
    }
    cout << "Данные сохранены!" << endl;
}

void loadFromFile(Station* &dataArray, int &arraySize) {
    if (dataArray != nullptr) {
        delete[] dataArray;
        dataArray = nullptr;
    }

    ifstream inputFile("station_data.txt");
    if (!inputFile) {
        cout << "Файл station_data.txt не найден!" << endl;
        _getch(); // Явное использование возвращаемого значения
        return;
    }

    arraySize = 0;
    string tempLine;
    while (getline(inputFile, tempLine)) {
        arraySize++;
    }

    inputFile.clear();
    inputFile.seekg(0);

    dataArray = new Station[arraySize];

    for (int i = 0; i < arraySize; i++) {
        inputFile >> dataArray[i].trainNumber;
        inputFile >> dataArray[i].destination;
        inputFile >> dataArray[i].days;
        inputFile >> dataArray[i].arrivalTime;
        inputFile >> dataArray[i].stopTime;
    }

    inputFile.close();
    cout << "Загружено " << arraySize << " записей из файла!" << endl;
}

void saveToFile(Station* dataArray, int arraySize) {
    if (arraySize == 0) {
        cout << "Нет данных для сохранения!" << endl;
        _getch();
        return;
    }

    ofstream outputFile("station_data.txt");
    for (int i = 0; i < arraySize; i++) {
        outputFile << dataArray[i].trainNumber << " "
             << dataArray[i].destination << " "
             << dataArray[i].days << " "
             << dataArray[i].arrivalTime << " "
             << dataArray[i].stopTime << endl;
    }
    outputFile.close();
    cout << "Данные сохранены в файл!" << endl;
}

void sortByNumber(Station* dataArray, int arraySize) {
    if (arraySize == 0) {
        cout << "Нет данных для сортировки!" << endl;
        return;
    }

    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = i + 1; j < arraySize; j++) {
            if (dataArray[j].trainNumber < dataArray[i].trainNumber) {
                swap(dataArray[i], dataArray[j]);
            }
        }
    }
    cout << "Сортировка завершена!" << endl;
}

void searchItem(Station* dataArray, int arraySize) {
    if (arraySize == 0) {
        cout << "Нет данных для поиска!" << endl;
        _getch();
        return;
    }

    int searchField;
    char searchValue[100];

    cout << "Поиск по: 1-номер 2-назначение 3-дни 4-прибытие 5-стоянка: ";
    cin >> searchField;
    cin.ignore();

    cout << "Значение для поиска: ";
    cin.getline(searchValue, 100);

    bool isFound = false;
    for (int i = 0; i < arraySize; i++) {
        bool isMatch = false;
        switch (searchField) {
            case 1:
                isMatch = (dataArray[i].trainNumber == atoi(searchValue));
                break;
            case 2:
                isMatch = (strcmp(dataArray[i].destination, searchValue) == 0);
                break;
            case 3:
                isMatch = (strcmp(dataArray[i].days, searchValue) == 0);
                break;
            case 4:
                isMatch = (strcmp(dataArray[i].arrivalTime, searchValue) == 0);
                break;
            case 5:
                isMatch = (strcmp(dataArray[i].stopTime, searchValue) == 0);
                break;
            default:
                cout << "Неверный выбор поля!" << endl;
                return;
        }

        if (isMatch) {
            cout << "Найден: №" << dataArray[i].trainNumber << " "
                 << dataArray[i].destination << " " << dataArray[i].days << " "
                 << dataArray[i].arrivalTime << " " << dataArray[i].stopTime << endl;
            isFound = true;
        }
    }

    if (!isFound) {
        cout << "Запись не найдена!" << endl;
    }
    _getch();
}

void changeItem(Station* dataArray, int arraySize) {
    if (arraySize == 0) {
        cout << "Нет данных для изменения!" << endl;
        _getch();
        return;
    }

    printTable(dataArray, arraySize);

    int recordId;
    cout << "Номер записи для изменения (1-" << arraySize << "): ";
    cin >> recordId;
    cin.ignore();

    if (recordId < 1 || recordId > arraySize) {
        cout << "Неверный номер!" << endl;
        _getch();
        return;
    }

    int fieldToChange;
    char newFieldValue[100];

    cout << "Поле (1-номер 2-назначение 3-дни 4-прибытие 5-стоянка): ";
    cin >> fieldToChange;
    cin.ignore();

    cout << "Новое значение: ";
    cin.getline(newFieldValue, 100);

    int recordIndex = recordId - 1;
    switch (fieldToChange) {
        case 1:
            dataArray[recordIndex].trainNumber = atoi(newFieldValue);
            break;
        case 2:
            strcpy(dataArray[recordIndex].destination, newFieldValue);
            break;
        case 3:
            strcpy(dataArray[recordIndex].days, newFieldValue);
            break;
        case 4:
            strcpy(dataArray[recordIndex].arrivalTime, newFieldValue);
            break;
        case 5:
            strcpy(dataArray[recordIndex].stopTime, newFieldValue);
            break;
        default:
            cout << "Неверный выбор поля!" << endl;
            return;
    }

    cout << "Данные записи изменены!" << endl;
    _getch();
}

void deleteItem(Station* &dataArray, int &arraySize) {
    if (arraySize == 0) {
        cout << "Нет данных для удаления!" << endl;
        _getch();
        return;
    }

    printTable(dataArray, arraySize);

    int recordId;
    cout << "Номер записи для удаления (1-" << arraySize << "): ";
    cin >> recordId;
    cin.ignore();

    if (recordId < 1 || recordId > arraySize) {
        cout << "Неверный номер!" << endl;
        _getch();
        return;
    }

    int recordIndex = recordId - 1;
    for (int i = recordIndex; i < arraySize - 1; i++) {
        dataArray[i] = dataArray[i + 1];
    }
    arraySize--;

    cout << "Запись удалена!" << endl;
    _getch();
}

int main() {
    int userChoice;

    setlocale(LC_ALL, "Russian");

    cout << "=== СИСТЕМА УПРАВЛЕНИЯ ДАННЫМИ ВОКЗАЛА ===" << endl;

    while (true) {
        printMenu();
        cin >> userChoice;
        cin.ignore();

        switch (userChoice) {
            case 1:
                inputFromKeyboard(stationData, dataCount);
                break;
            case 2:
                loadFromFile(stationData, dataCount);
                break;
            case 3:
                sortByNumber(stationData, dataCount);
                break;
            case 4:
                searchItem(stationData, dataCount);
                break;
            case 5:
                changeItem(stationData, dataCount);
                break;
            case 6:
                deleteItem(stationData, dataCount);
                break;
            case 7:
                printTable(stationData, dataCount);
                break;
            case 8:
                saveToFile(stationData, dataCount);
                break;
            case 9:
                if (stationData != nullptr) {
                    delete[] stationData;
                }
                cout << "Выход из программы..." << endl;
                return 0;
            default:
                cout << "Неверный выбор! Попробуйте снова." << endl;
                break;
        }

        cout << "Нажмите любую клавишу для продолжения...";
        _getch(); // Явное использование возвращаемого значения
    }
}









