#include <iostream>
#include <fstream>
#include <string>
#include "linkedlist.h"
#include <iomanip>

using namespace std;

void InputData(LinkedList *Student_List);
void Menu(LinkedList * students);

int main(){

    // Create and LinkedList pointer and allocate it memory
    LinkedList* Student_List = new LinkedList();

    // Read data from data.txt and call menu to decide how to sort
    InputData(Student_List);
    cout << "Unsorted:\n\n";
    Student_List->display();
    cout << endl << endl;

    Menu(Student_List);
    cout << "\nSorted\n\n";
    
    Student_List->display();
}

// initialize list with data from data.txt
void InputData(LinkedList *Student_List) {
    
    ifstream data{"./data.txt"};

    // check for errors
    if (!data) {
        cout << "data.txt could not be opened" << endl;
        return;
    }
    string fname, lname, mnum;

    // skips header
    data >> fname >> lname >> mnum;

    // write data to LinkedList
    for (int i = 0; i < 50; ++i) {
        data >> fname >> lname >> mnum;
        Student_List->createNode(fname, lname, mnum);
    }

    data.close();
}

// Uses std::iomanip to output menu and call desired sorting algorithm and direction
void Menu(LinkedList *Student_List)
{
   std::cout << std::setw(20) << std::setfill('*') << "" << std::endl;
   std::cout << std::setw(5) << std::setfill(' ') << "MENU - Sort direction" << std::endl;
   std::cout << std::setw(20) << std::setfill('*') << "" << std::endl;
   int sort_dir, sort_algo;
   do {
      std::cout << std::setfill(' ') << "   1) Sort Ascending" << std::endl;
      std::cout << "   2) Sort Descending" << std::endl;
      std::cout << "Enter choice: ";
      std::cin >> sort_dir;
   } while (!(sort_dir != 1 || sort_dir != 2));
    
   std::cout << endl;
   std::cout << std::setw(20) << std::setfill('*') << "" << std::endl;
   std::cout << std::setw(5) << std::setfill(' ') << "MENU - Sort algo" << std::endl;
   std::cout << std::setw(20) << std::setfill('*') << "" << std::endl;
   do {
      std::cout << std::setfill(' ') << "   1) Sort by First name" << std::endl;
      std::cout << "   2) Sort by Last Name" << std::endl;
      std::cout << "   3) Sort by MNumber" << std::endl;
      std::cout << "Enter choice: ";
      std::cin >> sort_algo;
   } while (!(sort_algo != 1 || sort_algo != 2 || sort_algo != 3));
     

   // call correct function
   if (sort_dir == 1) {
       if (sort_algo == 1) {
           Student_List->bubbleSortByFirstName(true);
       }
       else if (sort_algo == 2) {
           Student_List->MergeSortByLastName(Student_List->ReturnRefHead(), true);
       }
       else {
           Student_List->InsertionSortByMNumber(true);
       }
   }
   else {
       if (sort_algo == 1) {
           Student_List->bubbleSortByFirstName(false);
       }
       else if (sort_algo == 2) {
           Student_List->MergeSortByLastName(Student_List->ReturnRefHead(), false);
       }
       else {
           Student_List->InsertionSortByMNumber(false);
       }
   }
   
   return;
}