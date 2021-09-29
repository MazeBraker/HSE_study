//Heap-sort пирамидальная сортировка на C++
#include <iostream>

// Procedure for converting to a binary heap a subtree with root node i, which is
// index in arr []. n - heap size
void binary_heap_construct(int *arr, int n, int i) {
    int maxx = i;
// Инициализируем наибольший элемент как корень
    int left = 2 * i + 1; // левый child
    int right = 2 * i + 2; // правый child

    // Если правый child больше, чем самый большой элемент на данный момент
    if (right < n && arr[right] > arr[maxx])
        maxx = right;

    // Если левый child больше корня
    if (left < n && arr[left] > arr[maxx])
        maxx = left;
    
    // Если самый большой элемент не корень
    if (maxx != i) {
        std::swap(arr[i], arr[maxx]);

// Дальше работаем с меньшим затронутым поддеревом
        binary_heap_construct(arr, n, maxx);
    }
}

// Cортировку по дереву
void heapSort(int arr[], int n) {
    // Построение кучи
    for (int i = n / 2 - 1; i >= 0; i--)
        binary_heap_construct(arr, n, i);

    // One by one we extract elements from a heap
    for (int i = n - 1; i >= 0; i--) {
        // Move the current root to the end
        std::swap(arr[0], arr[i]);

        // Сall the heapify procedure on the reduced heap
        binary_heap_construct(arr, i, 0);
    }
}

int main() {
    int arr[100001];
    int n, i = 0;
    std::cin >> n;
    int size = n;
    while (std::cin >> n) {
        arr[i++] = n;
        if (i == size) {
            break;
        }
    }

    heapSort(arr, size);

    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    return 0;
}