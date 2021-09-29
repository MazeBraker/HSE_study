#include <iostream>
#include <vector>
#include<algorithm>
// куча через вектор
void binary_heap_construct(std::vector<int> &arr, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int root;
    if (l < arr.size()) {
        root = (r < arr.size() && arr[r] > arr[l]) ? r : l;
        if (arr[root] > arr[i]) {
            int buf = arr[i];
            arr[i] = arr[root];
            arr[root] = buf;
            binary_heap_construct(arr, root);
        }
    }
}

void Insert(std::vector<int> &arr, int value) {
    arr.push_back(value);
    int loc = arr.size() - 1;
    int parent = (loc - 1) / 2;

    while (loc > 0 && arr[parent] < arr[loc]) {
        int temp = arr[loc];
        arr[loc] = arr[parent];
        arr[parent] = temp;
        loc = parent;
        parent = (loc - 1) / 2;
    }
}

int main() {
    int n;
    int flag, num;
    std::vector<int> Heap;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> flag;
        if (flag == 0) {
            std::cin >> num;
            Insert(Heap, num);
        }
        if (flag != 1) continue;
        std::cout << *(begin(Heap)) << '\n';
        std::swap(Heap[Heap.size() - 1], Heap[0]);
        Heap.pop_back();
        binary_heap_construct(Heap, 0);
    }
}