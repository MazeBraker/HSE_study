/* 
 * *Двоичную кучу удобно хранить в виде одномерного массива, причем левый потомок вершины 
 * с индексом i имеет индекс 2*i+1, а правый 2*i+2. Корень дерева – элемент с индексом 0. 
 * Высота двоичной кучи равна высоте дерева, то есть log2 N, 
 * где N – количество элементов массива.
*/
#include <iostream>

class Heap {
    int size = 1;
    int arr[100001];
public:
    Heap() {
        size = 0;
    }

    void Insert(int val);

    int Extract();
};

void Heap::Insert(int val) {
    // увеличили размер для new val
    size++;
    arr[size - 1] = val;
    for (int i = size - 1; i > 0;) {
        // левый родитель, если больше выталкиваем наверх,то есть меняем значения
        if (arr[i] > arr[(i - 1) / 2]) {
            std::swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        } else {
            break;
        }
    }
}

int Heap::Extract() {
    int root = arr[0];
    // largestChild = i;
    int i = 0;
    int leftChild = 2 * i + 1;
    int rightChild;
    while (leftChild < size) {
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        if (leftChild == size - 1) {
            arr[i] = arr[leftChild];
            break;
        } else if (arr[leftChild] > arr[rightChild]) {
            arr[i] = arr[leftChild];
            i = 2 * i + 1;
        } else {
            arr[i] = arr[rightChild];
            i = 2 * i + 2;
        }
    }
    // в бин куче максимум в корне
    return root;
}

int main() {
    Heap heap;
    int N, val, flag;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
        std::cin >> flag;
        if (flag == 1)
            std::cout << heap.Extract() << '\n';
        else {
            std::cin >> val;
            heap.Insert(val);
        }
    }
    return 0;
}