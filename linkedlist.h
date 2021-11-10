#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <iostream>

// Node class containing data for first and last name and mnumber
class Node {
public:
	 std::string first_name, last_name, mnumber;
	 Node* next;
};

// LinkedList class with different 
class LinkedList {
private:
    Node *head;
    int num_nodes;
public:
    LinkedList() 
    {
        head = nullptr;
        tail = nullptr;
    }

    void createNode(std::string first_name, std::string last_name, std::string mnumber);
    void display();    

    // Sort by first name
    void bubbleSortByFirstName(bool sort_ascending);

    // Returns reference to head pointer (pointer to pointer)
    Node** const ReturnRefHead() {return &(this->head);}
    
    // Sort by last name
    void MergeSortByLastName(Node** head, bool sort_ascending);
    Node* Merge(Node* first,Node* second, bool sort_ascending);
    
    // Sort by Mnumber
    void InsertionSortByMNumber(bool sort_ascending);
};
#endif