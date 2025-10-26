#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
const int MAXSIZE = 100000;

struct Queue {
    char data[MAXSIZE];
    int size, head, tail;
    Queue() : size(0), head(0), tail(-1) {
    }
};

void AddToQueue(Queue &Q, char x) {
    if (Q.size == MAXSIZE) {
        printf("Массив переполнен!\n");
        return;
    }
    Q.tail++;
    if (Q.tail >= MAXSIZE) Q.tail = 0;
    Q.data[Q.tail] = x;
    Q.size++;
}
char RemoveFromQueue(Queue& Q) {
    if (Q.size==0) {
        return char(32767);
    }
    char x = Q.data[Q.head];
    Q.head++;
    if (Q.head >= MAXSIZE) Q.head = 0;
    Q.size--;
    return x;
}
int main() {
    setlocale(LC_ALL, "Russian");
    Queue Letters = Queue();
    Queue Numbers = Queue();
    Queue Others = Queue();
    const string numbers = "0123456789";
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    ifstream inputFile("Dulles' Plan.txt");
    ofstream outputFile("outputFile.txt");
    string line;
    while (getline(inputFile, line)) {
        for (int i = 0; i < line.length(); i++) {
        if (numbers.find(line[i]) != string::npos) {
            AddToQueue(Numbers,line[i]);
        }
        else {
            if (alphabet.find(line[i]) != string::npos) {
                AddToQueue(Letters,line[i]);
            }
            else {
                AddToQueue(Others,line[i]);
            }
        }
        }
        while (Letters.size > 0) {
            outputFile<<RemoveFromQueue(Letters);
        }
        while (Numbers.size > 0) {
            outputFile<<RemoveFromQueue(Numbers);
        }
        while (Others.size > 0) {
            outputFile<<RemoveFromQueue(Others);
        }
        outputFile<<endl;
    }

    return 1;
}