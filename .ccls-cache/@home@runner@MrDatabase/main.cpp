#include <iostream>
#include <strings.h>
using namespace std;
#define CAPACITY 50000 // Size of the Hash Table

// A Hash table is an array of items, which themselves are a {key: value} pair.
// Hash-Item
class hashTableItem {
    string key;
    string value;

    hashTableItem() {
      key = "";
      value = "";
    }

    hashTableItem(string )
};

// Hash-Table
class hashTable {
    hashTableItem** items;
    int size;
    int count;
};

// Create hash items items
hashTableItem* create_item(string key, string value) {
    // Creates a pointer to a new hash table item
    hashTableItem* item =  new hashTableItem(key, value);  
    return item;
}

// 
HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;

    return table;
}

// Hashing function
int test_hash_function(string name){
  int hash = 0;
  for(int i = 0; i< name.length(); i++){
    hash += name[i];
  }

  // NOTE: We must return a number within the capacity of the hash table. Otherwise, we may access an unbound memory location, leading to an error.
  return hash % CAPACITY; 

int main() {
  std::cout << "Hello World!\n";
  int hash = test_hash_function("mayhul");

  cout << hash;
}