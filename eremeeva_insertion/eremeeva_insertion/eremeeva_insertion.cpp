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

Node* insertionSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* sorted = nullptr;
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        if (sorted == nullptr || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        }
        else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    return sorted;
}

Node* loadDataFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: File '" << filename << "' not found!" << endl;
        return nullptr;
    }

    Node* head = nullptr;
    Node* tail = nullptr;
    int value;

    while (file >> value) {
        Node* newNode = new Node(value);
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

void displayList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

void freeMemory(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void runInsertionSortModule() {
    cout << " INSERTION SORT MODULE " << endl;

    Node* list = loadDataFromFile("numbers.txt");
    if (list == nullptr) return;

    cout << "Input data: ";
    displayList(list);

    auto start = high_resolution_clock::now();
    Node* sorted = insertionSort(list);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Output data: ";
    displayList(sorted);
    cout << "Insertion Sort time: " << duration.count() << " microseconds" << endl << endl;

    freeMemory(sorted);
}

int main() {
    cout << " INSERTION SORT ALGORITHM " << endl;
    cout << "File: numbers.txt" << endl;

    runInsertionSortModule();

    cout << "Program completed. Press any key to exit..." << endl;
    system("pause");
    return 0;
}