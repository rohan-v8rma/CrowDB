# Basic stuff

## Definition part

- A Hash Table in C/C++ (Associative array) is a data structure that maps keys to values. This uses a hash function to compute indexes for a key.
Based on the Hash Table index, we can store the value at the appropriate location.

- If two different keys get the same index, we need to use other data structures (buckets) to account for these collisions.

- The whole benefit of using a Hash Table is due to it’s very fast access time. While there can be a collision, if we choose a very good hash function, this chance is almost zero.
So, on average, the `time complexity is a constant O(1)` access time. This is called Amortized Time Complexity.

- Any Hash Table implementation has the following three components:

  - A good Hash function to map keys to values
  - A Hash Table Data Structure that supports insert, search and delete operations.
  - A Data Structure to account for collision of keys

## Deep-Dive

### Choose a hash function
### 


# Paths for Project

## Non-relational database

Upon calling the program using the API accompanied with the name of the user (Mayhul, Rohan, etc), the linked list of objects containing name:value pairs details of a person is returned.

```cpp
class detail {
  string nameOfDetail;
  double valueOfDetail;
}
```

The details of the person can be age, height, weight, etc. 

## Relational database

Upon calling the program using the API accompanied with the name of the database, the AVL tree of objects containing records of multiple people is returned.

This avl can be sorted in a variety of ways (by age, height, weight, etc).

```cpp
class record {
  string name;
  int age;
  double height;
  double weight;
} 
```


# Doubts

1. How do we identify whether the person trying to access the program using the API is a new user or an existing user?


# Report Explanations

1. This is an experimental unsecured database, where anyone knowing the username/database-name can access, without any pass phrase.

# TODO

## Constructor Format

Node(string s):data(s),next(NULL) {};
Node(string s,Node* nd):data(s),next(nd) {};


