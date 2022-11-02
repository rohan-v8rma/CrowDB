```
        ┌───┬─── Project overview
        │   │
        │   ├──► What does the project do
        │   │
        │   └──► Tech used
        │
        ├───┬─── Tech
        │   │
        │   ├──► Hashing
        │   │
        │   ├──► AVL
        │   │
        │   ├──► API
        │   │
        │   └──► Production Stuff
        │
        ├─────── Biblography + Further Aim

Links:

- https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus
- https://ddanilov.me/dockerized-cpp-build
- https://github.com/prince776/yt-projects/blob/master/cppREST/main.cpp
- https://crowcpp.org/master/getting_started/setup/linux/
```

#  Hash Table ka kuch tuh likha hain 

- A Hash Table in C/C++ (Associative array) is a data structure that maps keys to values. This uses a hash function to compute indexes for a key.
Based on the Hash Table index, we can store the value at the appropriate location.

- If two different keys get the same index, we need to use other data structures (buckets) to account for these collisions.

- The whole benefit of using a Hash Table is due to it’s very fast access time. While there can be a collision, if we choose a very good hash function, this chance is almost zero.
So, on average, the `time complexity is a constant O(1)` access time. This is called Amortized Time Complexity.

- Any Hash Table implementation has the following three components:

  - A good Hash function to map keys to values
  - A Hash Table Data Structure that supports insert, search and delete operations.
  - A Data Structure to account for collision of keys

## Deep-Dive for hash-map wala part

Yaha peh deep-dive/steps likhenge ki hamne kese hash map wala part kiya
Basically functions jo jo banaye hain uska quick overview

# AVL ka kuch kuch

yeh toh tune already readme banai hogi isme voh hee daal dio

## Deep-Dive for AVL wala part if needed

# API

yaha peh basic needs aur chaatne wali lines. Iska deep dive likhne ki zaroorat ni
Yaha peh pictures daalenge ki jisse intersting lagegega. Gyan kam jodna hian yaha peh

- Http methods used with their following demo client side request
  - GET
    ```
    domain.com?database_name=hello&name=drg&mode=sorted
    ```
    
  - POST
    ```
    curl -X POST https://domain.com/api/create
     -H 'Accept: application/json'
     -H 'Content-Type: application/json'
     -d '{"databse_name": "mayhulDB"}' // yeh stringified json hain. Iske baare mein padhlio google peh
    ```
    
  - PATCH
    ```
    curl -X PATCH https://domain.com/api/update
       -H 'Content-Type: application/json'
       -H 'Accept: application/json'
       -d '{"databse_name": "kuch bhi", "name": "Jason Sweet", "age": 1, ..etc}'
    ```
    
  - DELETE
    ```
    curl -X DELETE https://domain.com/api/delete?database_name=somthong&name=mayhul
     -H "Accept: application/json"
    ```
- Search and write about
  - `CRUD` api(jo ham basically banarae hain)
  - Checkout `crow` docs jo hame backend banane mein help karra hain

# Dependencies

1. Crow
Download the `.deb` file of the latest release from Crowcpp's github, [here](https://github.com/CrowCpp/Crow/releases/tag/v1.0+5).

Simply install the `.deb` file, no other setup required.

2. Boost
```bash
root@ubuntu$ sudo snap install libboost-all-dev
```


# Now making the project production ready...let say somewhat ready:)
- Common problems of building projects “natively” on a workstation
> merko bas seekhna tha yeh part toh ham yeh bhi karre hain lol. Yeh ni pata ki docker/github-action/cmake inme kya cheez kese decide karni hoti

  - First of all, let us discuss why building C/C++ projects directly on a workstation may become a problem. C++ does not provide a built-in dependency management mechanism and as a result, third parties are added using a mix of techniques: installing from Linux distro’s repositories (e.g. apt-get) or via “make install”, adding 3rd parties as git submodules and building them within the source tree, or using a half-baked solution like Conan.
  Unfortunately, all of them have certain disadvantages:
  
    - Installing dependencies on a dev machine makes the environment dirty and rarely the same as CI/CD or production, especially after updating the 3rd parties.
    
    - Adding 3rd parties as git submodules requires building them within the project’s source tree. In cases when a 3rd party is heavy (boost, Protobuf, Thrift, etc), this approach may slow down the build so significantly that developers become reluctant to clean a build directory or switch between branches.
      
    - Solutions like Conan often lack the right version of a certain dependency and adding it requires writing code in Python, which from my point of view is a bit too much.



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


# Doubts

1. How do we identify whether the person trying to access the program using the API is a new user or an existing user?

# Explanation of working of functions 

1. The api call `display_all_records` displays the contents of the avl tree database, using in order traversal. Which is why the students are displayed alphabetically. 

2. Currently, we are running this on local host, which is why our API calls have an IP address and a port in the URL, like so:
    ```console
    root@ubuntu~$ curl "http://127.0.0.1:3000/api/create_database?teacher_name=rachna"
    ``` 
    But, if we purchase or rent a domain name for our IP address, then we can make requests to that domain name, and it would be resolved

# Report Explanations

<!-- NOTE: Don't write this in report. -->
1. This is an experimental unsecured database, where anyone knowing the username/database-name can access, without any pass phrase.

# TODO

## Constructor Format

Node(string s):data(s),next(NULL) {};
Node(string s,Node* nd):data(s),next(nd) {};


