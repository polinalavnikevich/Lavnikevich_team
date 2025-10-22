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

Node* merge(Node* left, Node* right) {
    Node* dummy = new Node(0);
    Node* current = dummy;
    while (left != nullptr && right != nullptr) {
        if (left->data <= right->data) {
            current->next = left;
            left = left->next;
        }
        else {
            current->next = right;
            right = right->next;
        }
        current = current->next;
    }
    if (left != nullptr) current->next = left;
    else current->next = right;
    Node* result = dummy->next;
    delete dummy;
    return result;
}

Node* findMiddle(Node* head) {
    if (head == nullptr) return head;
    Node* slow = head;
    Node* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* mergeSort(Node* head) {
    if (head == nullptr || head->next == nullptr) return head;
    Node* middle = findMiddle(head);
    Node* nextToMiddle = middle->next;
    middle->next = nullptr;
    Node* left = mergeSort(head);
    Node* right = mergeSort(nextToMiddle);
    return merge(left, right);
}

Node* importData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "ERROR: Unable to access " << filename << endl;
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

void printLinkedList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

void releaseMemory(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void runMergeSortModule() {
    cout << " MERGE SORT MODULE " << endl;

    Node* list = importData("numbers.txt");
    if (list == nullptr) return;

    cout << "Initial list: ";
    printLinkedList(list);

    auto start = high_resolution_clock::now();
    Node* sorted = mergeSort(list);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    cout << "Sorted list: ";
    printLinkedList(sorted);
    cout << "Merge Sort time: " << duration.count() << " microseconds" << endl << endl;

    releaseMemory(sorted);
}

int main() {
    cout << "MERGE SORT ALGORITHM" << endl;
    cout << "File: numbers.txt" << endl;

    runMergeSortModule();

    cout << "Program completed. Press any key to exit..." << endl;
    system("pause");
    return 0;
}