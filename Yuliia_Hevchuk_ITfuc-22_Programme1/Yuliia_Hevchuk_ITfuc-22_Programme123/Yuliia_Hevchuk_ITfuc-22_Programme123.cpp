#include <iostream>
using namespace std;

struct node {
    int data;
    struct node* link;
    node(int value) : data(value), link(nullptr) {}
};

class Task {
public:
    node* head;
    Task() : head(nullptr) {}

    void insert(int value) {
        node* newnode = new node(value);
        if (!head) {
            head = newnode;
        }
        else {
            node* current = head;
            while (current->link) {
                current = current->link;
            }
            current->link = newnode;
        }
    }
    void removeElementsLessThanN(int n) {
        // Handle empty list
        if (!head) {
            return;
        }
        // Handle the case where the head node needs to be removed
        while (head && head->data < n) {
            node* temp = head;
            head = head->link;
            delete temp;
        }
        node* current = head;

        // Traverse the list and remove nodes that are less than n
        while (current && current->link) {
            while (current->link && current->link->data < n) {
                node* temp = current->link;
                current->link = current->link->link;
                delete temp;
            }

            current = current->link;
        }

        return;
    }
    // Function to print the linked list
    void printList() {
        node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->link;
        }
        cout << endl;
    }

    // Function to delete the linked list to free memory
    void deleteList() {
        while (head) {
            node* temp = head;
            head = head->link;
            delete temp;
        }
    }
    // Function to insert x after all negative elements
    void insertAfterNegatives(int x) {
        node* current = head;

        while (current!=nullptr) {
            if (current->data < 0 && current->data >= -10 && current->data <= 30) {
                node* newnode = new node(x);
                newnode->link = current->link;
                current->link = newnode;
                current = newnode->link;
            }
            else {
                current = current->link;
            }
        }
    }
    // Function to replace elements greater than b with b
    void replaceGreaterThanB(int b) {
        node* current = head;

        while (current) {
            if (current->data > b) {
                current->data = b;
            }

            current = current->link;
        }
    }
};

int main()
{
    Task mainList;
    for (int i = -10; i <= 30; ++i)
        mainList.insert(i);
    int choice, n, x, b, N;
    bool done = false;

    while (!done) {
        cout << "____________________________________________" << endl;
        cout << "Menu:" << endl;
        cout << "1. Display List" << endl;
        cout << "2. Remove from the singly-linked list all elements that are less than entered number n" << endl;
        cout << "3. Insert the number x after all negative elements in the singly-linked list." << endl;
        cout << "4. Enter an integer number N. Enter N integers numbers a1, a2, ... aN into a singly-linked list and the number b.In the sequence a1, a2, ... aN replace all members greater than b by b.Output the resulting sequence." << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "____________________________________________" << endl;

        switch (choice) {
        case 1: {
            // Display List   
            cout << "Current List: ";
            mainList.printList();
            break;
        }

        case 2: {
            // Remove all elements that are less then n
            cout << "Enter the number n " << endl;
            cin >> n;
            mainList.removeElementsLessThanN(n);
            cout << "New list :";
            mainList.printList();
            break;
        }

        case 3: {
            //Insert the number x after all negative elements
            cout << "Enter the number x " << endl;
            cin >> x;
            mainList.insertAfterNegatives(x);
            cout << "New list :";
            mainList.printList();
            break;
        }

        case 4: {
            //Replace all members by b
            cout << "Enter an integer numbers N " << endl;
            cin >> N;
            mainList.deleteList();

            for (int i = 0; i < N; ++i) {
                int value;
                cout << "Enter element " << i + 1 << ": ";
                cin >> value;

                mainList.insert(value);
            }
            int b;
            cout << "Enter the number b: ";
            cin >> b;

            cout << "Original List: ";
            mainList.printList();

            // Task: Replace elements greater than b with b
            mainList.replaceGreaterThanB(b);
            std::cout << "List after replacing elements greater than " << b << " with " << b << ": ";
            mainList.printList();
            break;
        }

        case 5: {
            // Quit
            done = true;
            break;
        }
              break;
        default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

        }
    }
    mainList.deleteList();


    return 0;

}
