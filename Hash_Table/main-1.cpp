#include <iostream>
using namespace std;
#define CAPACITY 50000 // Size of the Hash Table

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

// Hash-Table
class hashTable {
    
public:
    hashTableItem** items;
    int size=0;
    int count;

    // Member functions
    hashTable() {
        
    }
    hashTable(int size) {
        this->size = size;
        this->items = new hashTableItem*[size];
        // All elements of the items array, which contains pointers, are by-default NULL.
    }
  
};

// Create hash items
hashTableItem* create_item(string key, string value) {
    // Creates a pointer to a new hash table item
    hashTableItem* item =  new hashTableItem(key, value);  
    
    return item;
}

// create hash table
hashTable* create_table(int size) {
    hashTable* table = new hashTable(size);
    return table;
}

// Hashing function
int hashFunction(string name){
  int hash = 0;
  for(int i = 0; i< name.length(); i++){
    hash += name[i];
  }
  return hash % CAPACITY; 
}

// insertion
// implement later used be ht
void handleCollision(hashTable* table, unsigned long index, hashTableItem* item) {
}

void hashTableInsert(hashTable* table, string key, string value) {
    // Create the item
    hashTableItem* item = create_item(key, value);

    // Compute the index
    unsigned long index = hashFunction(key);

    hashTableItem* current_item = table->items[index];
    
    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            cout << ("Insert Error: Hash Table is full\n") << endl;;
            // Remove the create item
            return;
        }
        
        // Insert directly
        table->items[index] = item; 
        table->count++;
    }

    else {
            // Scenario 1: We only need to update value
            if (current_item->key ==  key) {
                table->items[index]->value = value;
                return;
            }
        else {
            // Scenario 2: Collision
            // We will handle case this a bit later
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

    // Ensure that we move to a non NULL item
    if (item != NULL) {
        if (item->key == key) {
            return item->value;
        }
    }
    return NULL;
}

// yeh printing
void printSearch(hashTable* table, string key) {
    string val = hashSearch(table, key);
    if (val == "") {
        cout << "Key:"<< key <<" does not exist" << endl;
        return;
    }
    else {
        cout << "Key:"<< key <<", Value:" << val << endl;
    }
}

void printTable(hashTable* table) {
    cout << "\nHASH TABLE\n----------" << endl;
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            cout << "Index:" << i << ", Key:" << table->items[i]->key << ", Value:" << table->items[i]->value << endl;
        }
    }
    cout << "-------------------\n\n";
}



int main() {
  int hash = hashFunction("mayhul");
  
  cout << hash;
}