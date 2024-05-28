#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<>
void swapValues<const char*>(const char*& a, const char*& b) {
    const char* temp = a;
    a = b;
    b = temp;
}

template <typename T>
int binarySearch(const std::vector<T>& arr, const T& key) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] < key) {
            left = mid + 1;
        }
        else if (key < arr[mid]) {
            right = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& newData) : data(newData), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insertRecursive(Node*& node, const T& data) {
        if (node == nullptr) {
            node = new Node(data);
        }
        else if (data < node->data) {
            insertRecursive(node->left, data);
        }
        else {
            insertRecursive(node->right, data);
        }
    }

    void traverseInOrder(Node* node) const {
        if (node == nullptr)
            return;
        traverseInOrder(node->left);
        std::cout << node->data << " ";
        traverseInOrder(node->right);
    }

    void traversePostOrder(Node* node) const {
        if (node == nullptr)
            return;
        traversePostOrder(node->left);
        traversePostOrder(node->right);
        std::cout << node->data << " ";
    }

    void traversePreOrder(Node* node) const {
        if (node == nullptr)
            return;
        std::cout << node->data << " ";
        traversePreOrder(node->left);
        traversePreOrder(node->right);
    }

    bool searchRecursive(Node* node, const T& key) const {
        if (node == nullptr)
            return false;
        if (node->data == key)
            return true;
        if (key < node->data)
            return searchRecursive(node->left, key);
        return searchRecursive(node->right, key);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const T& data) {
        insertRecursive(root, data);
    }

    void traverseInOrder() const {
        traverseInOrder(root);
    }

    void traversePostOrder() const {
        traversePostOrder(root);
    }

    void traversePreOrder() const {
        traversePreOrder(root);
    }

    bool search(const T& key) const {
        return searchRecursive(root, key);
    }
};

class Array {
private:
    int* data;
    int size;

public:
    Array(int arr[], int n) {
        size = n;
        data = new int[size];
        for (int i = 0; i < size; ++i) {
            data[i] = arr[i];
        }
    }

    ~Array() {
        delete[] data;
    }

    class Iterator {
    private:
        int* ptr;
    public:
        Iterator(int* p) : ptr(p) {}

        int operator*() {
            return *ptr;
        }

        void operator++() {
            ++ptr;
        }

        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }
    };

    Iterator begin() {
        return Iterator(data);
    }

    Iterator end() {
        return Iterator(data + size);
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    int choice;
    std::cout << "Введіть номер коду, який ви хочете виконати (1, 2, 3, або 4): ";
    std::cin >> choice;

    switch (choice) {
    case 1: {
        int x = 5, y = 10;
        std::cout << "Перед обміном: x = " << x << ", y = " << y << std::endl;
        swapValues(x, y);
        std::cout << "Після обміну: x = " << x << ", y = " << y << std::endl;

        const char* str1 = "Привіт";
        const char* str2 = "Світ";
        std::cout << "Перед обміном: str1 = " << str1 << ", str2 = " << str2 << std::endl;
        swapValues(str1, str2);
        std::cout << "Після обміну: str1 = " << str1 << ", str2 = " << str2 << std::endl;
        break;
    }
    case 2: {
        std::vector<std::string> arr = { "яблуко", "банан", "вишня", "апельсин", "ананас" };
        std::sort(arr.begin(), arr.end());
        std::string key = "апельсин";
        int index = binarySearch(arr, key);
        if (index != -1) {
            std::cout << "Елемент знайдено на позиції " << index << std::endl;
        }
        else {
            std::cout << "Елемент не знайдено" << std::endl;
        }
        break;
    }
    case 3: {
        BinarySearchTree<int> bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        std::cout << "Впорядкований прохід: ";
        bst.traverseInOrder();
        std::cout << std::endl;

        std::cout << "Обхід у зворотному порядку: ";
        bst.traversePostOrder();
        std::cout << std::endl;

        std::cout << "Прямий обхід: ";
        bst.traversePreOrder();
        std::cout << std::endl;

        int key = 30;
        if (bst.search(key))
            std::cout << key << " знайдено у дереві." << std::endl;
        else
            std::cout << key << " не знайдено у дереві." << std::endl;
        break;
    }
    case 4: {
        int arr[] = { 1, 2, 3, 4, 5 };
        Array array(arr, 5);

        std::cout << "Елементи масиву: ";
        for (Array::Iterator it = array.begin(); it != array.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        break;
    }
    default:
        std::cout << "Невірний вибір коду." << std::endl;
    }

    return 0;
}
