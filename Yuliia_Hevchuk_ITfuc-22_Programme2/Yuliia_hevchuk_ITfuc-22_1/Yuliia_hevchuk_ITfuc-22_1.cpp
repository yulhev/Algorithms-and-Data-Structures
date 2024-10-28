#include <iostream>
#include <string>

using namespace std;

// Doubly-Linked List Node
struct DListNode {
    string surname;
    DListNode* prev, * next;
    DListNode(string s) : surname(s), prev(nullptr), next(nullptr) {}
};

// Queue implemented using a Doubly-Linked List
class Queue {
public:
    DListNode* front, * back;

    Queue() : front(nullptr), back(nullptr) {}

    void enqueue(string surname) {
        DListNode* newNode = new DListNode(surname);
        if (back == nullptr) {
            front = back = newNode;
        }
        else {
            back->next = newNode;
            newNode->prev = back;
            back = newNode;
        }
    }

    void display() {
        DListNode* current = front;
        while (current != nullptr) {
            cout << current->surname << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~Queue() {
        while (front) {
            DListNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// Stack implemented using a Singly-Linked List
class SListNode {
public:
    string surname;
    SListNode* next;
    SListNode(string s) : surname(s), next(nullptr) {}
};

class Stack {
public:
    SListNode* top;

    Stack() : top(nullptr) {}

    void push(string surname) {
        SListNode* newNode = new SListNode(surname);
        newNode->next = top;
        top = newNode;
    }

    string pop() {
        if (isEmpty()) {
            return "";
        }
        SListNode* temp = top;
        string popped = temp->surname;
        top = top->next;
        delete temp;
        return popped;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        SListNode* current = top;
        while (current != nullptr) {
            cout << current->surname << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~Stack() {
        while (top) {
            SListNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

// TreeNode structure for the binary tree
struct TreeNode {
    string surname;
    TreeNode* left, * right;
    TreeNode(string s) : surname(s), left(nullptr), right(nullptr) {}
};

// Queue for surnames ending with "is"
class AtQueue {
public:
    DListNode* front, * back;

    AtQueue() : front(nullptr), back(nullptr) {}

    void enqueue(string surname) {
        DListNode* newNode = new DListNode(surname);
        if (back == nullptr) {
            front = back = newNode;
        }
        else {
            back->next = newNode;
            newNode->prev = back;
            back = newNode;
        }
    }

    void display() {
        DListNode* current = front;
        while (current != nullptr) {
            cout << current->surname << " ";
            current = current->next;
        }
        cout << endl;
    }

    ~AtQueue() {
        while (front) {
            DListNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

// Binary Tree class
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {}

    void insert(string surname) {
        root = insertRec(root, surname);
    }

    TreeNode* search(string surname) {
        return searchRec(root, surname);
    }

    void inOrderPrint() {
        inOrderRec(root);
        cout << endl;
    }

    void deleteSurname(string surname) {
        root = deleteRec(root, surname);
    }

    void enqueueSurnamesEndingWithIs(Queue& queue) {
        enqueueEndingIsRec(root, queue);
    }

    void enqueueSurnamesStartingWithAt(AtQueue& atQueue) {
        enqueueStartingAtRec(root, atQueue);
    }

    void removeFromTreeAndPushToStack(Stack& stack) {
        removeFromTreeAndPushRec(root, stack);
    }

private:
    TreeNode* insertRec(TreeNode* node, string surname) {
        if (node == nullptr) {
            return new TreeNode(surname);
        }
        if (surname < node->surname) {
            node->left = insertRec(node->left, surname);
        }
        else if (surname > node->surname) {
            node->right = insertRec(node->right, surname);
        }
        return node;
    }

    TreeNode* searchRec(TreeNode* node, string surname) {
        if (node == nullptr || node->surname == surname) {
            return node;
        }
        if (surname < node->surname) {
            return searchRec(node->left, surname);
        }
        return searchRec(node->right, surname);
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteRec(TreeNode* node, string surname) {
        if (node == nullptr) return node;

        if (surname < node->surname) {
            node->left = deleteRec(node->left, surname);
        }
        else if (surname > node->surname) {
            node->right = deleteRec(node->right, surname);
        }
        else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->surname = temp->surname;
            node->right = deleteRec(node->right, temp->surname);
        }
        return node;
    }

    void inOrderRec(TreeNode* node) {
        if (node != nullptr) {
            inOrderRec(node->left);
            cout << node->surname << " ";
            inOrderRec(node->right);
        }
    }

    void enqueueEndingIsRec(TreeNode* node, Queue& queue) {
        if (node) {
            enqueueEndingIsRec(node->left, queue);
            if (!node->surname.empty() && node->surname.size() >= 2 &&
                node->surname.substr(node->surname.size() - 2) == "is") {
                queue.enqueue(node->surname);
            }
            enqueueEndingIsRec(node->right, queue);
        }
    }

    void enqueueStartingAtRec(TreeNode* node, AtQueue& atQueue) {
        if (node) {
            enqueueStartingAtRec(node->left, atQueue);
            if (!node->surname.empty() && node->surname.substr(0, 2) == "At") {
                atQueue.enqueue(node->surname);
            }
            enqueueStartingAtRec(node->right, atQueue);
        }
    }

    void removeFromTreeAndPushRec(TreeNode*& node, Stack& stack) {
        if (node) {
            removeFromTreeAndPushRec(node->left, stack);
            if (!node->surname.empty() && node->surname.substr(0, 2) == "Is") {
                stack.push(node->surname);
                deleteSurname(node->surname); // Assuming a function for deleting a specific surname
            }
            removeFromTreeAndPushRec(node->right, stack);
        }
    }

   
};

void showMenu() {
    cout << "------------------------------";
    cout << "\nMenu:\n";
    cout << "1. Insert Surname\n";
    cout << "2. Search Surname\n";
    cout << "3. Delete Surname\n";
    cout << "4. Print Tree\n";
    cout << "5. Enqueue Surnames Ending with 'Is'\n";
    cout << "6. Enqueue Surnames Starting with 'At'\n";
    cout << "7. Remove 'Is' Surnames from Tree and Push to Stack\n";
    cout << "8. Remove Items from Queue and Stack\n";
    cout << "9. Exit\n";
    cout << "\nEnter your choice: ";
}

int main() {
    BinaryTree tree;
    Queue endingIsQueue; // Queue for surnames ending with "is"
    AtQueue startingAtQueue; // Queue for surnames starting with "At"
    Stack removalStack; // Stack for surnames starting with "is"

    int choice;
    string surname;

    while (true) {
        showMenu();
        cin >> choice;
        cout << "------------------------------\n";
        switch (choice) {
        case 1: // Insert Surname
            while (true) {
                cout << "Enter surname ('menu' to exit): ";
                cin >> surname;
                if (surname == "menu") {
                    break;
                }
                tree.insert(surname);
                cout << "Surname '" << surname << "' inserted.\n";
            }
            break;
        case 2: // Search Surname
            cout << "Enter surname to search: ";
            cin >> surname;
            if (tree.search(surname)) {
                cout << "Surname found: " << surname << "\n";
            }
            else {
                cout << "Surname not found.\n";
            }
            break;
        case 3: // Delete Surname
            cout << "Enter surname to delete: ";
            cin >> surname;
            if (tree.search(surname)) {
                tree.deleteSurname(surname);
                cout << "Surname deleted: " << surname << "\n";
            }
            else {
                cout << "Surname not found.\n";
            }
            break;
        case 4: // Print Tree
            cout << "Binary Tree In-Order: ";
            tree.inOrderPrint();
            break;
        case 5: // Enqueue Surnames Ending with 'is'
            tree.enqueueSurnamesEndingWithIs(endingIsQueue);
            cout << "Surnames ending with 'is' have been enqueued.\n";
            cout << "Queue (ending with 'is'): ";
            endingIsQueue.display();
            break;
        case 6: // Enqueue Surnames Starting with 'At'
            tree.enqueueSurnamesStartingWithAt(startingAtQueue);
            cout << "Surnames starting with 'At' have been enqueued.\n";
            cout << "Queue (starting with 'At'): ";
            startingAtQueue.display();
            break;
        case 7: // Remove surnames starting with 'is' from tree and push to stack
            tree.removeFromTreeAndPushToStack(removalStack);
            cout << "Surnames starting with 'Is' removed from tree and pushed to stack.\n";
            break;
        case 8: // Remove all items from queue and stack by printing them
            cout << "Items in Queue (ending with 'is'): ";
            endingIsQueue.display();
            cout << "Items in Queue (starting with 'At'): ";
            startingAtQueue.display();
            cout << "Items in Stack: ";
            removalStack.display();
            break;
        case 9: // Exit
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
