#include <iostream>

#define CAPACITY 10

using namespace ::std;

int hashFunction(string name){
  int hash = 0;
  for(int i = 0; i< name.length(); i++){
    hash += name[i];
  }
  return hash % CAPACITY; 
}

int main() {
  cout << to_string(2223.2) << endl;

  cout << hashFunction("lijo") << endl;
}
