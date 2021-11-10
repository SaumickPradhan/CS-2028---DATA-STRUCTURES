#include "linkedlist.h"
#include <string>
using namespace std;

void LinkedList::createNode(std::string first_name, std::string last_name, std::string mnumber)
{
    Node *temp = new Node;
    temp->first_name = first_name;
    temp->last_name = last_name;
    temp->mnumber = mnumber;
    temp->next = nullptr;

    // Make this head if head does not exist
    if (head==nullptr)
    {
        head = temp;
        tail = temp;
        temp = nullptr;
        num_nodes = 1;
    }
    else
    {
        tail->next = temp;
        tail = temp;
        num_nodes++;
    }
}

// Displays all nodes
void LinkedList::display()
{
    Node *temp = new Node;
    temp = head;
    while(temp != nullptr)
    {
        std::cout << temp->first_name << "\t" << temp->last_name << "\t" << temp->mnumber << std::endl;
        temp = temp->next;
    }
}

// Use bubblesort to sort by first name
void LinkedList::bubbleSortByFirstName(bool sort_ascending){
    Node *p = head;
    head = nullptr;

    while (p)
    {
        Node **first = &p;
        Node **second = &p->next;
        bool swapped = false;

        // keep going until qq holds the address of a null pointer
        while (*second)
        {
            // if the first name is alphabetically more than the second name
            if (sort_ascending && (*first)->first_name.compare((*second)->first_name) > 0)
            {
                // swap pointers (not data)
                std::swap(*first, *second);
                std::swap((*first)->next, (*second)->next);
                first = &(*first)->next;
                swapped = true;
            }
            else if (!sort_ascending && (*first)->first_name.compare((*second)->first_name) < 0)
            {
                // swap
                std::swap(*first, *second);
                std::swap((*first)->next, (*second)->next);
                first = &(*first)->next;
                swapped = true;
            }
            else
            {   // no swap, still advance both pointers
                first = second;
                second = &(*second)->next;
            }
        }

        // link last node to the sorted segment
        *second = head;

        // if we swapped, detach the final node, terminate the list, and continue.
        if (swapped)
        {
            // take the last node off the list and push it into the result.
            head = *first;
            *first = nullptr;
        }

        // otherwise we're done. since no swaps happened the list is sorted.
        // set the output parameter and terminate the loop.
        else
        { 
            head = p;
            break;
        }
    }
}

// Merge sort helper function
Node* LinkedList::Merge(Node* first,Node* second, bool sort_ascending)
{
  Node* answer=nullptr;
  if(!first)
  {
    return second;
  }
  else if (!second)
  {
    return first;
  }

  if (sort_ascending){
  if (first-> last_name <=second->last_name)
  {
    answer=first;
    answer->next=Merge(first->next, second,sort_ascending);
  }
  else
  {
    answer=second;
    answer->next=Merge(first, second->next,sort_ascending);
  }
  }
  else{
    if (first-> last_name >=second->last_name)
  {
    answer=first;
    answer->next=Merge(first->next, second,sort_ascending);
  }
  else
  {
    answer=second;
    answer->next=Merge(first, second->next,sort_ascending);
  }

  }
  return answer;
}

// Merge sort helper function
void MiddleNode(Node* curr,Node** first,Node** second)
{
  Node* twice;
  Node* single;
  single=curr;
  twice=curr->next;
  while(twice!=nullptr)
  {
    twice=twice->next;
    if(twice!=nullptr)
    {
      single=single->next;
      twice=twice->next;
    }
  }
  
  *first=curr;
  *second=single->next;
  single->next=nullptr; 

}

// Use merge sort to sort by last name
void LinkedList::MergeSortByLastName(Node** head, bool sort_ascending)
{
  Node* curr= *head;
  Node *first;
  Node *second;

  if (!curr or !curr->next) 
  {
    return;
  }

  MiddleNode(curr, &first, &second);

  MergeSortByLastName(&first,sort_ascending);
  MergeSortByLastName(&second,sort_ascending);
  *head = Merge(first, second,sort_ascending);

}

//ALEX - INSERTION SORT BY NUMBER
void LinkedList::InsertionSortByMNumber(bool sort_ascending){
  Node* curr = head;
  Node* sortedList = NULL;
  if(sort_ascending == true){ //Case for ascending
    while(curr != NULL){
        Node* next = curr->next;

        if(sortedList == NULL || sortedList->mnumber.compare(curr->mnumber) > 0){ //case for the head
        curr->next = sortedList;
        sortedList = curr; // new head
        }
        else{
        Node* temp = sortedList;
        while(temp->next != NULL && temp->next->mnumber.compare(curr->mnumber) < 0){ //comparing using .compare
            temp = temp->next;
        }
        curr->next = temp->next;
        temp->next = curr;
        }
        curr = next;
    }
    head = sortedList; //assigning head to be the new list
  }
  else{ //Case for descending
    while(curr != NULL){
    Node* next = curr->next;

    if(sortedList == NULL || sortedList->mnumber.compare(curr->mnumber) < 0){ //case for the head
    curr->next = sortedList;
    sortedList = curr;
    }
    else{
    Node* temp = sortedList;
    while(temp->next != NULL && temp->next->mnumber.compare(curr->mnumber) > 0){
        temp = temp->next;
    }
    curr->next = temp->next;
    temp->next = curr;
    }
    curr = next;
    }
    head = sortedList;
  }
}