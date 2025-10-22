#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <windows.h>

using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* next;
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

Node* bubbleSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
    return head;
}

Node* createListFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Cannot open file '" << filename << "'" << endl;
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    int number;

    while (file >> number) {
        Node* newNode = new Node(number);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    file.close();
    return head;
}

void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void runBubbleSortModule() {
    cout << "=== BUBBLE SORT MODULE ===" << endl;

    Node* list = createListFromFile("numbers.txt");
    if (list == nullptr) return;

    cout << "Original list: ";
    printList(list);

    auto start = high_resolution_clock::now();
    Node* sorted = bubbleSort(list);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Sorted list: ";
    printList(sorted);
    cout << "Bubble Sort time: " << duration.count() << " microseconds" << endl << endl;

    deleteList(sorted);
}

// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ
int main() {
    cout << "=== BUBBLE SORT ALGORITHM ===" << endl;
    cout << "File: numbers.txt" << endl;
    cout << "=============================" << endl << endl;

    runBubbleSortModule();

    cout << "Program completed. Press any key to exit..." << endl;
    system("pause");
    return 0;
}