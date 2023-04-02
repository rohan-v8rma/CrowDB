# INDEX

- [INDEX](#index)
- [What are Hash Tables?](#what-are-hash-tables)
- [AVL trees](#avl-trees)
  - [A basic explanation](#a-basic-explanation)
  - [Balance Factor of AVL trees](#balance-factor-of-avl-trees)
- [API related information](#api-related-information)
  - [Routing in CROW](#routing-in-crow)
  - [Example HTTP requests](#example-http-requests)
  - [Hosting](#hosting)
  - [Basic Flow](#basic-flow)
- [Dependencies](#dependencies)
  - [1. Crow](#1-crow)
  - [2. Boost](#2-boost)
- [Initial steps to be taken towards making the project production ready](#initial-steps-to-be-taken-towards-making-the-project-production-ready)
- [Possible Directions for Project](#possible-directions-for-project)
  - [Non-relational database](#non-relational-database)
  - [Relational database](#relational-database)
- [Enhancements that can be made](#enhancements-that-can-be-made)
- [TODO](#todo)
  - [Constructor Format](#constructor-format)
- [Containerizing and scaling](#containerizing-and-scaling)
  - [CMake](#cmake)
  - [Dockerfile](#dockerfile)
  - [Docker-Networking](#docker-networking)
  - [Docker-Compose](#docker-compose)
  - [CI-CD Pipeline](#ci-cd-pipeline)
  - [Reference](#reference)
  - [Links](#links)

---

# What are Hash Tables?

- A Hash Table in C/C++ (Associative array) is a data structure that maps keys to values. This uses a hash function to compute indexes for a key.
Based on the Hash Table index, we can store the value at the appropriate location.

- If two different keys get the same index, we need to use other data structures (buckets) to account for these collisions.

- The whole benefit of using a Hash Table is due to it’s very fast access time. While there can be a collision, if we choose a very good hash function, this chance is almost zero.
So, on average, the `time complexity is a constant O(1)` access time. This is called Amortized Time Complexity.

- Any Hash Table implementation has the following three components:

  - A good Hash function to map keys to values
  - A Hash Table Data Structure that supports insert, search and delete operations.
  - A Data Structure to account for collision of keys

---

# AVL trees

## A basic explanation

- AVL Tree can be defined as a **self-balancing binary search tree** (a BST or a binary search tree is a tree where the value stored in a particular node is always greater than that of its left subtree and lower than the values in its right subtree) in which each node associates with a balance factor which is calculated by subtracting the height of its right subtree from that of its left subtree. 

- An AVL tree holds multiple advantages over a normal BST especially when it comes to BST operations such as searching, deleting and inserting. 

  Since the tree is balanced we are guaranteed a worst case time complexity of `O(log(N))`, as no skewed trees can exist.

## Balance Factor of AVL trees

The balance factor ensures that the BST remains balanced from both its child nodes, and is typically maintained between -1 to 1. 

If it exceeds these numbers from any end then the tree is said to be unbalanced.

To maintain the balance factor of each node, an AVL tree performs several kinds of rotations - 
- **Right-right** rotation - This is performed when the tree becomes unbalanced due to an insertion in the right subtree of the right subtree.
- **Left-left** rotation - Done when the tree is unbalanced due to insertion of a node in the left subtree of the left subtree.
- **Left-right** rotation - This involves 2 consecutive rotations, right-right and then left-left rotations.
- **Right-left** rotation - Similarly, this consists of a left-left rotation first and then a right-right rotation.

---

# API related information

## Routing in CROW

Routing is a fundamental concept in web development that allows you to map URLs to specific functions or code blocks that will handle the logic for that URL. 

Crow, being a C++ web framework, utilizes this concept to create HTTP or WebSocket web services.

When a client sends a request to the server, the request typically contains a URL that specifies the resource that the client is requesting. The server then uses routing to determine which function or code block should handle the request based on the requested URL.

In Crow, routing is implemented using a set of rules that match URLs to specific routes. These rules are defined using a syntax that is similar to regular expressions. For example, you might define a rule that matches any URL that starts with /users/ and is followed by a numeric ID:

```cpp
CROW_ROUTE(app, "/users/<int:id>")
([](const request& req, response& res, int id) {
    // Handle request for user with ID `id`
});
```

In this example, `CROW_ROUTE` is a macro that defines a new route for the specified URL pattern (`/users/<int:id>`). The pattern contains a variable (`<int:id>`) that matches a numeric ID, which is passed as an argument to the handling function.

When a request matches the specified URL pattern, Crow calls the associated handling function and passes it the request and response objects, as well as any captured variables from the URL pattern (in this case, the `id` variable).

Check out the [CROW docs](https://crowcpp.org/master/) for more information.

## Example HTTP requests

- GET
  ```bash
  curl "http://127.0.0.1:3000/api/display_student_record?teacher_name=rachna&student_name=mayhul"
  ```
  
- POST
  ```bash
  curl -X POST http://127.0.0.1:3000/api/create_database \
  -H 'Accept: text/plain' \
  -H 'Content-Type: application/json' \
  -d '{"teacher_name": "rachna"}'
  ```
  
- PATCH
  ```bash
  curl -X PATCH http://127.0.0.1:3000/api/update_database_record \
  -H 'Accept: text/plain' \
  -H 'Content-Type: application/json' \
  -d '{"teacher_name": "rachna", "student_name": "mayhul", "age": 19, "weight": 197, "cgpa": 9.7}'
  ```
  
- DELETE
  ```bash
  curl -X DELETE http://127.0.0.1:3000/api/delete_student_record
  -H "Accept: text/plain" \
  -H 'Content-Type: application/json' \
  -d '{"teacher_name": "rachna", "student_name": "mayhul"}'
  ```

## Hosting 

Currently, we are running this on local host, which is why our API calls have an IP address and a port in the URL, like so:

```console
root@ubuntu~$ curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"
``` 

But, if we were purchase or rent a domain name for our IP address OR used a hosting server, then we can make requests to that domain name, and it would be resolved

## Basic Flow 

- A shell script compiled using bash is used to perform API calls to the server running the CROW application in a C++ runtime environment. The code for our API is compiled into a binary using a C++ compiler like GCC or Clang.

  These API calls can also be performed by the user on his local machine to get the required data and make the necessary changes in our database.

> ***Note***: When you build and run a CROW application, you are essentially running a C++ program that uses the CROW framework to handle HTTP or WebSocket requests.

- We specifically use the `curl` command to get the data back from our server, this includes response codes (404, 503, 200, etc) which signify the result of our call. We also receive the data as a string.

- For our database, we use a hash table in which the teacher ID acts as the key and the head pointer of the AVL tree in which their student records are stored, acts as the value for the respective key.
- With respect to the collection of databases, the teacher ID is used as a unique primary key that can be used to identify the corresponding collection of student records.

- The AVL tree databases have every node representing a class data type, containing the details for a single student.

- The student details consist of 
  - Student name
  - Age
  - Weight
  - CGPA

- For every teacher ID (primary key), we implement the basic CRUD operations (Create, Read, Update, Delete) to make changes in the database.

- By using the alphabetic precedence of the names of students to rebalance our AVL tree, we can now easily access our data and use the AVL tree operations to access/manipulate the data.
    
  Balance can be regained by performing several kinds of rotations on the AVL tree - right-right, left-left, right-left or left-right rotations, described above.

- AVL trees also offer a lower time complexity of `O(log(N))` for searching, insertion and deletion that is more efficient as compared to the time complexity of regular Binary search trees, which is `O(N)`.

---

# Dependencies

## 1. Crow

Download the `.deb` file of the latest release from Crowcpp's github, [here](https://github.com/CrowCpp/Crow/releases/tag/v1.0+5).

Simply install the `.deb` file, no other setup required.

> ***Note***: In our repo, we have added a `crow_all.h` file in the `include` file which includes all the source code of CROW, so this step is NOT necessary.

## 2. Boost

```bash
root@ubuntu$ sudo apt install libboost-all-dev
```

---

# Initial steps to be taken towards making the project production ready

- Common problems of building projects “natively” on a workstation
> merko bas seekhna tha yeh part toh ham yeh bhi karre hain lol. Yeh ni pata ki docker/github-action/cmake inme kya cheez kese decide karni hoti

  - First of all, let us discuss why building C/C++ projects directly on a workstation may become a problem. 
  
  C++ does not provide a built-in dependency management mechanism and as a result, third parties are added using a mix of techniques: installing from Linux distro’s repositories (e.g. `apt`) or via `make install`, adding 3rd parties as git sub-modules and building them within the source tree, or using a half-baked solution like Conan.

  Unfortunately, all of them have certain disadvantages:
  
  - Installing dependencies on a dev machine makes the environment dirty and rarely the same as CI/CD or production, especially after updating the 3rd parties.
    
  - Adding 3rd parties as git submodules requires building them within the project’s source tree. In cases when a 3rd party is heavy (boost, Protobuf, Thrift, etc), this approach may slow down the build so significantly that developers become reluctant to clean a build directory or switch between branches.
      
  - Solutions like Conan often lack the right version of a certain dependency and adding it requires writing code in Python, which from my point of view is a bit too much.

---

# Possible Directions for Project

## Non-relational database

Upon calling the program using the API accompanied with the name of the user (Mayhul, Rohan, etc), the linked list of objects containing name:value pairs details of a person is returned.

```cpp
class detail {
  string nameOfDetail;
  double valueOfDetail;
}
```

The details of the person can be age, height, weight, etc. 

Have a username MASTER, which can be used to get the information of all people, or check which people have a value for a particular parameter-

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

---

# Enhancements that can be made

1. This is an experimental unsecured database, where anyone knowing the username/database-name can access, without any pass phrase.
2. For demonstration purposes, a very simple hash function has been used.
3. We can add support for getting database record by number, which can be obtained by taking the record using tree traversal. 
   
    We'll traverse the AVL tree database until the number that has been provided to us has been met.
4. identify whether the person trying to access the program using the API is a new user or an existing user
# TODO

## Constructor Format

Node(string s):data(s),next(NULL) {};
Node(string s,Node* nd):data(s),next(nd) {};

# Containerizing and scaling

## CMake
## Dockerfile
## Docker-Networking
## Docker-Compose
## CI-CD Pipeline

## Reference

```
Foo
 ├── include
 │   └── Foo
 │       ├── Foo.h
 │       └── ...
 ├── src
 │   ├── Foo.cpp
 │   └── ...
 |
 ├── build
 │   └── bin
 |
 ├── test
 |   ├── test-bash-scripts
 │   └── test-cpp-code     
 |
 └── libs
     ├── A
     │   ├── include
     │   │   └── A
     │   │       ├── A.h
     │   │       └── ...
     │   ├── src
     │   │   ├── A.cpp
     │   │   └── ...
     │   └── test
     │       └── ...
     └── B
         ├── include
         │   └── B
         │       ├── B.h
         │       └── ...
         ├── src
         │   ├── B.cpp
         │   └── ...
         └── test
             └── ...
```

## Links

- https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
- https://ddanilov.me/dockerized-cpp-build
- https://github.com/prince776/yt-projects/blob/master/cppREST/main.cpp
- https://crowcpp.org/master/getting_started/setup/linux/
