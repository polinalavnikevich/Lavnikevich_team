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

Node* selectionSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* current = head;
    while (current != nullptr) {
        Node* minNode = current;
        Node* temp = current->next;
        while (temp != nullptr) {
            if (temp->data < minNode->data) {
                minNode = temp;
            }
            temp = temp->next;
        }
        swap(current->data, minNode->data);
        current = current->next;
    }
    return head;
}

Node* readNumbersFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Could not open " << filename << endl;
        return nullptr;
    }

    Node* first = nullptr;
    Node* last = nullptr;
    int num;

    while (file >> num) {
        Node* newNode = new Node(num);
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        }
        else {
            last->next = newNode;
            last = newNode;
        }
    }
    file.close();
    return first;
}

void showList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "END" << endl;
}

void cleanupList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void runSelectionSortModule() {
    cout << " SELECTION SORT MODULE " << endl;

    Node* list = readNumbersFromFile("numbers.txt");
    if (list == nullptr) return;

    cout << "Before sorting: ";
    showList(list);

    auto start = high_resolution_clock::now();
    Node* sorted = selectionSort(list);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "After sorting: ";
    showList(sorted);
    cout << "Selection Sort time: " << duration.count() << " microseconds" << endl << endl;

    cleanupList(sorted);
}

int main() {
    cout << " SELECTION SORT ALGORITHM " << endl;
    cout << "File: numbers.txt" << endl;

    runSelectionSortModule();

    cout << "Program completed. Press any key to exit..." << endl;
    system("pause");
    return 0;
}