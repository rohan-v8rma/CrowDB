#include <iostream>
#include "./linked_list.h"
#include "./avl_tree.h"
// #include "crow.h"


using namespace std;
#define CAPACITY 100 // Size of the Hash Table

// A Hash table is an array of items, which themselves are a {key: value} pair.
// Hash-Item
class hashTableItem {
    
public:
    string teacherName;
    Node* teacherDB;

    // Member functions
    hashTableItem() {
      teacherName = "";
      teacherDB = NULL;
    }

    hashTableItem(string teacherName, Node* teacherDB) {
      this->teacherName = teacherName;
      this->teacherDB = teacherDB;
    }
};

// Overloaded the stream insertion operator for easily printing `hashTableItem` instance variables
ostream& operator << (ostream& out, hashTableItem* item) {
    out << "teacherName: " << item->teacherName << ", Value: " << item->teacherDB;
    return out;
}

// Hash-Table
class hashTable {
    
public:
    hashTableItem** items;
    linkedListNode<hashTableItem>** overflowLinkedLists;
    int hashLimit = CAPACITY; // Available hash values are 0 to 9. The maximum amount of maps the hash table can contain is 10 in this case, but it is possible that two teacherNames have the same hash value and hash value is unoccupied.
    int count = 0;

    // Member functions
    hashTable() {
        this->items = new hashTableItem*[hashLimit];
        // All elements of the items array, which contains pointers, are by-default NULL.
        this->overflowLinkedLists = new linkedListNode<hashTableItem>*[hashLimit];
    }

    // hashTable(int hashLimit) {
    //     this->hashLimit = hashLimit;
    //     this->items = new hashTableItem*[hashLimit];
    //     // All elements of the items array created above, which contains pointers, are by-default NULL. We need to allocate memory for each of them separately.
    //     this->overflowLinkedLists = new linkedListNode<hashTableItem>*[hashLimit];
    // }   
  
};

// Hashing function
int hashFunction(string name) {
  int hash = 0;
  for(int i = 0; i< name.length(); i++){
    hash += name[i];
  }
  return hash % CAPACITY; 
}

hashTableItem* hashSearch(hashTable* table, string teacherName) {

    // Searches the teacherName in the hashtable and returns NULL if it doesn't exist
    
    int index = hashFunction(teacherName);

    hashTableItem* currentItem = table->items[index];

    linkedListNode<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];


    // Ensure that we move to a non NULL item
    while(currentItem != NULL) {

        // return new hashTableItem;  
        // return NULL;

        //! This part is problematic
        if (currentItem->teacherName == teacherName) { // Returning the value only if it matches.
            return currentItem;
        }

        // Changing item to the items present in the overflowLinkedList of the corresponding index hash value
        if(overflowLinkedList != NULL) {
            
            currentItem = overflowLinkedList->item;
            overflowLinkedList = overflowLinkedList->next;
        }
        else {
            break; // For the condition when the item's teacherName doesn't match, as well as the overflowLinkedList is NULL, so no more elements are left to check. So, we can safely terminate the while loop.
        }

    }
    

    return NULL;
}

int doesDBExist(hashTable* table, string teacherName) {
    if(hashSearch(table, teacherName)) {
        return 1; // DB doesn't exist
    }
    else {
        return 0;
    }
}

void handleCollision(hashTable* table, unsigned long index, hashTableItem* item) { // `index` is the corresponding index position of the hash.
    linkedListNode<hashTableItem>* head = table->overflowLinkedLists[index];

    if (head == NULL) { // Since overflow hasn't occured as of yet, we need to allocate memory for the overflow linked list.
        head = new linkedListNode<hashTableItem>;
    }

    head->insert(item); // Takes care of both cases. When linked-list is empty as well as when it has some elements.

    table->overflowLinkedLists[index] = head;
    table->count++;
}

void insertDatabaseintoHashTable(hashTable* table, string teacherName, Node* teacherDB) {
    
    // Compute the index
    unsigned long index = hashFunction(teacherName);

    hashTableItem* currentItem = table->items[index];
    
    if (currentItem == NULL) { // teacherName does not exist.
        if (table->count == table->hashLimit) {
            // Hash Table Full
            cout << ("Insert Error: Hash Table is full\n") << endl;
            // Remove the create item
            return;
        }
        
        // Creating and inserting the item directly
        table->items[index] = new hashTableItem(teacherName, teacherDB); 
        table->count++;
    }
    else if(!doesDBExist(table, teacherName)) { // When DB doesn't exist, only then do we try to insert it using collision resolution.
        // Scenario 2: Collision resolution
        handleCollision(table, index, new hashTableItem(teacherName, teacherDB));
        return;
    }
    else {
        cout << "teacherName:"<< teacherName <<" already has a database in our system. Creation aborted." << endl;
    }
}

void hashTableUpdateDatabaseRecords(hashTable* table, string teacherName, Node* studentNode) {
    if(!doesDBExist) { // Database doesn't exist, so not possible to update it
        cout << "The database doesn't exist, so it is not possible to update it." << endl;
        return;
    }
    // Compute the index
    unsigned long index = hashFunction(teacherName);

    hashTableItem* item = table->items[index];
    linkedListNode<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];

    while(true) {
        if (item->teacherName == teacherName) { // Returning the value only if it matches.
            item->teacherDB = insertNode(item->teacherDB, studentNode);
            break;
        }
    
        // Changing item to the items present in the overflowLinkedList of the corresponding index hash value
        if(overflowLinkedList != NULL) {
            item = overflowLinkedList->item;
            overflowLinkedList = overflowLinkedList->next;
        }
    }
}

void hashTableDeleteFromDatabase(hashTable* table, string teacherName, string studentName) {

    if(!doesDBExist(table, teacherName)) { // Database doesn't exist, so not possible to update it
        //TODO: Change where responses come from
        // return crow::response(404, "The database doesn't exist, so it is not possible to delete records from it.\n");
        cout << "The database doesn't exist, so it is not possible to delete records from it.\n";
        return;
    }
    // Compute the index
    unsigned long index = hashFunction(teacherName);

    hashTableItem* currentItem = table->items[index];
    linkedListNode<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];

    while(true) {
        if(currentItem == NULL) {
            cout << "Record not present. Deletion aborted...\n"; 
            break;
        }

        if (currentItem->teacherName == teacherName) { // Returning the value only if it matches.

            currentItem->teacherDB = deleteNode(currentItem->teacherDB, studentName);
            break;
        }
    
        // Changing item to the items present in the overflowLinkedList of the corresponding index hash value
        if(overflowLinkedList != NULL) {
            currentItem = overflowLinkedList->item;
            overflowLinkedList = overflowLinkedList->next;
        }
    }
}

string hashTableDisplayAllDatabaseRecords(hashTable* table, string teacherName) {
    if(!doesDBExist(table, teacherName)) { // Database doesn't exist, so not possible to update it
        //TODO: Change where responses come from
        // return crow::response(404, "The database doesn't exist, so it is not possible to delete records from it.\n");
        return( "Database does not exist.\n");
    }

    // Compute the index
    unsigned long index = hashFunction(teacherName);

    hashTableItem* currentItem = table->items[index];
    linkedListNode<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];

    while(true) {
        if(currentItem == NULL) {
            cout << "Record not present. Deletion aborted...\n"; 
            break;
        }

        if (currentItem->teacherName == teacherName) { // Returning the value only if it matches.

            return( inOrderTraversal(currentItem->teacherDB, "") );
            break;
        }
    
        // Changing item to the items present in the overflowLinkedList of the corresponding index hash value
        if(overflowLinkedList != NULL) {
            currentItem = overflowLinkedList->item;
            overflowLinkedList = overflowLinkedList->next;
        }
    }

    return( "Database does not exist.\n");
}


void printTable(hashTable* table) {
    cout << "\nHASH TABLE\n\n-------------------" << endl;
    
    for (int index = 0; index < table->hashLimit; index++) {
        
        if (table->items[index]) {
            cout << "Index:" << index << ", " << table->items[index] << endl;
        }
        
        linkedListNode<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];
        while (overflowLinkedList) {
            cout << "Index:" << index << ", " << overflowLinkedList->item << endl;

            overflowLinkedList = overflowLinkedList->next;
        }
    }
    cout << "-------------------\n\n";
}

// int main() {
//     // int hashVal = hashFunction("mayhul");

//     // cout << hashVal << endl;

//     // hashVal = hashFunction("soham");

//     // cout << hashVal << endl;

//     hashTable* tablePointer = new hashTable(CAPACITY);

//     //! NOTE: rohan, soham and mayhul each have hash value of 6 for the current hashing function.

//     hashTableInsert(tablePointer, "mayhul", "buri-buri"); // Name followed by nick name
//     hashTableInsert(tablePointer, "rohan", "batman");

//     printTable(tablePointer);


//     // Testing hashSearch
//     cout << hashSearch(tablePointer, "rohan") << endl;

//     // Testing printSearch
//     printSearch(tablePointer, "rohan");
//     printSearch(tablePointer, "soham");


//     return 0;
// }