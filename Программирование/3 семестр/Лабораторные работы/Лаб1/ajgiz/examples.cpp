//
// Created by admin on 24.09.2025.
//

int integral(int n) {
    if (n <= 0) return 1;
    else return n * integral(n - 1);
}



void mason(int a[], int from, int to) {
    int i, j, temp, x;
    i = from;
    j = to;
    x = a[(i + j) / 2];
    while (i <= j) {
        while (a[i] < x) i++;
        while (a[j] > x) j--;
        if (i<=j) {
            temp = a[i];
            a[i]=a[j];
            a[j]=temp;
            i++;
            j--;

        }
    }
    mason(a,from,j);
    mason(a,i,to);
}




struct Node {
    chat word[40];
    int count;
    Node *next;
};
typedef struct Node *PNode;
Pnode Head = NULL;


int main() {
}
