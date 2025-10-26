#include <iostream>
#include <string>
#include <cmath>
using namespace std;

struct Node {
    string name;
    int score;
    Node* next;
};

void addNode(Node** head, string name, int score) {
    Node* newNode = new Node{name, score, *head};
    *head = newNode;
}

int getMax(Node* head) {
    int mx = 0;
    while (head) {
        if (head->score > mx) mx = head->score;
        head = head->next;
    }
    return mx;
}

int getLength(Node* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

void radixSort(Node** head) {
    int maxScore = getMax(*head);
    for (int exp = 1; maxScore / exp > 0; exp *= 10) {
        Node* buckets[10] = {nullptr};
        Node* tails[10] = {nullptr};
        Node* curr = *head;
        while (curr) {
            int digit = (curr->score / exp) % 10;
            Node* next = curr->next;
            curr->next = nullptr;
            if (!buckets[digit]) buckets[digit] = tails[digit] = curr;
            else { tails[digit]->next = curr; tails[digit] = curr; }
            curr = next;
        }
        Node* newHead = nullptr;
        Node* newTail = nullptr;
        for (int i = 0; i < 10; i++) {
            if (buckets[i]) {
                if (!newHead) newHead = buckets[i];
                else newTail->next = buckets[i];
                newTail = tails[i];
            }
        }
        *head = newHead;
    }
}

Node* getNodeAt(Node* head, int index) {
    int i = 0;
    while (head && i < index) {
        head = head->next;
        i++;
    }
    return head;
}

Node* binarySearch(Node* head, int n, string name, int score) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        Node* midNode = getNodeAt(head, mid);
        if (midNode->score == score && midNode->name == name) return midNode;
        if (midNode->score < score) low = mid + 1;
        else high = mid - 1;
    }
    return nullptr;
}

void deleteNode(Node** head, string name, int score) {
    Node* temp = *head;
    Node* prev = nullptr;
    while (temp) {
        if (temp->name == name && temp->score == score) {
            if (prev) prev->next = temp->next;
            else *head = temp->next;
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void display(Node* head) {
    while (head) {
        cout << head->name << " " << head->score << endl;
        head = head->next;
    }
}

int main() {
    Node* head = nullptr;
    addNode(&head, "Ayan", 90);
    addNode(&head, "Zameer", 60);
    addNode(&head, "Sara", 70);
    addNode(&head, "Sohail", 30);
    addNode(&head, "Ahmed", 20);
    radixSort(&head);
    display(head);
    string name;
    int score;
    cout << "Enter name and score to delete: ";
    cin >> name >> score;
    int len = getLength(head);
    Node* found = binarySearch(head, len, name, score);
    if (found) {
        deleteNode(&head, name, score);
        cout << "Updated list:\n";
        display(head);
    }
   
}
