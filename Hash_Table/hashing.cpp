#include <iostream>
#include "../user-defined-header-files/linked-list.h"

using namespace std;
#define CAPACITY 10 // Size of the Hash Table

// A Hash table is an array of items, which themselves are a {key: value} pair.
// Hash-Item
class hashTableItem {
    
public:
    string key;
    string value;

    // Member functions
    hashTableItem() {
      key = "";
      value = "";
    }

    hashTableItem(string key, string value) {
      this->key = key;
      this->value = value;
    }
};

// Overloaded the stream insertion operator for easily printing `hashTableItem` instance variables
ostream& operator << (ostream& out, hashTableItem* item) {
    out << "Key: " << item->key << ", Value: " << item->value;
    return out;
}

// Hash-Table
class hashTable {
    
public:
    hashTableItem** items;
    linkedList<hashTableItem>** overflowLinkedLists;
    int hashLimit = 10; // Available hash values are 0 to 9. The maximum amount of maps the hash table can contain is 10 in this case, but it is possible that two keys have the same hash value and hash value is unoccupied.
    int count = 0;

    // Member functions
    hashTable() {
        this->items = new hashTableItem*[hashLimit];
        // All elements of the items array, which contains pointers, are by-default NULL.
        this->overflowLinkedLists = new linkedList<hashTableItem>*[hashLimit];
    }

    hashTable(int hashLimit) {
        this->hashLimit = hashLimit;
        this->items = new hashTableItem*[hashLimit];
        // All elements of the items array created above, which contains pointers, are by-default NULL. We need to allocate memory for each of them separately.
        this->overflowLinkedLists = new linkedList<hashTableItem>*[hashLimit];
    }   
  
};

// Hashing function
int hashFunction(string name){
  int hash = 0;
  for(int i = 0; i< name.length(); i++){
    hash += name[i];
  }
  return hash % CAPACITY; 
}

void handleCollision(hashTable* table, unsigned long index, hashTableItem* item) { // `index` is the corresponding index position of the hash.
    linkedList<hashTableItem>* head = table->overflowLinkedLists[index];

    if (head == NULL) { // Since overflow hasn't occured as of yet, we need to allocate memory for the overflow linked list.
        head = new linkedList<hashTableItem>;
    }

    head->insert(item); // Takes care of both cases. When linked-list is empty as well as when it has some elements.

    table->overflowLinkedLists[index] = head;
}

void hashTableInsert(hashTable* table, string key, string value) {
    // Create the item
    hashTableItem* item = new hashTableItem(key, value);

    // Compute the index
    unsigned long index = hashFunction(key);

    hashTableItem* currentItem = table->items[index];
    
    if (currentItem == NULL) { // Key does not exist.
        if (table->count == table->hashLimit) {
            // Hash Table Full
            cout << ("Insert Error: Hash Table is full\n") << endl;
            // Remove the create item
            return;
        }
        
        // Insert directly
        table->items[index] = item; 
        table->count++;
    }

    else {
            // Scenario 1: The key of the received item and the pre-existing item is same so we only need to update the value.
            if (currentItem->key ==  key) {
                table->items[index]->value = value;
                return;
            }
        else {
            // Scenario 2: Collision
            handleCollision(table, index, item);
            return;
        }
    }
}

// hash-search

string hashSearch(hashTable* table, string key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hashFunction(key);
    hashTableItem* item = table->items[index];
    linkedList<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];

    // Ensure that we move to a non NULL item
    while(item != NULL) {
        if (item->key == key) { // Returning the value only if it matches.
            return item->value;
        }

        // Changing item to the items present in the overflowLinkedList of the corresponding index hash value
        if(overflowLinkedList != NULL) {
            item = overflowLinkedList->item;
            overflowLinkedList = overflowLinkedList->next;
        }
        else {
            break; // For the condition when the item's key doesn't match, as well as the overflowLinkedList is NULL, so no more elements are left to check. So, we can safely terminate the while loop.
        }

    }
    return "";
}

// yeh printing
void printSearch(hashTable* table, string key) {
    string val = hashSearch(table, key);
    if (val == "") {
        cout << "Key:"<< key <<" does not have a corresponding value." << endl;
        return;
    }
    else {
        cout << "Key:"<< key <<", Value:" << val << endl;
    }
}

void printTable(hashTable* table) {
    cout << "\nHASH TABLE\n\n-------------------" << endl;
    
    for (int index = 0; index < table->hashLimit; index++) {
        
        if (table->items[index]) {
            cout << "Index:" << index << ", " << table->items[index] << endl;
        }
        
        linkedList<hashTableItem>* overflowLinkedList = table->overflowLinkedLists[index];
        while (overflowLinkedList) {
            cout << "Index:" << index << ", " << overflowLinkedList->item << endl;

            overflowLinkedList = overflowLinkedList->next;
        }
    }
    cout << "-------------------\n\n";
}

int main() {
    // int hashVal = hashFunction("mayhul");

    // cout << hashVal << endl;

    // hashVal = hashFunction("soham");

    // cout << hashVal << endl;

    hashTable* tablePointer = new hashTable(CAPACITY);

    //! NOTE: rohan, soham and mayhul each have hash value of 6 for the current hashing function.

    hashTableInsert(tablePointer, "mayhul", "buri-buri"); // Name followed by nick name
    hashTableInsert(tablePointer, "rohan", "batman");

    printTable(tablePointer);


    // Testing hashSearch
    cout << hashSearch(tablePointer, "rohan") << endl;

    // Testing printSearch
    printSearch(tablePointer, "rohan");
    printSearch(tablePointer, "soham");


    return 0;
}