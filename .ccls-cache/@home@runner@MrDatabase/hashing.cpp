// 

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LinkedList
{
public:
    class Node
    {
    public:
        string data;
        Node* next = NULL;
        Node(string data){
          this->data = data;          
        };
        Node(string data, Node* next){
          this->data = data;
          this->next = next;
        };
    };
    
    Node* front; 

    //member functions
    
    LinkedList() //default constructor
    {
        front=NULL;
    }

    LinkedList(const LinkedList& ls) //copy constructor
    {
        deepCopy(ls);
    }

    ~LinkedList() //destructor
    {
        deleteList();
    }

    // Overloading of assignment operator
    LinkedList& operator = (const LinkedList& ls) {                  if(this!=&ls) {
          deleteList();
          deepCopy(ls);
        }   
        return *this;
    }

    bool insert(const string& s) {
        if(search(s)) {
            return false;
        }
        front=new Node(s,front);
        return true;
    }

    bool remove(const string& s) {
        Node* temp=front;
        if(temp==NULL) //list is empty
            return false;
        if(temp->data==s) //s is first string in list
        {
            front=temp->next;
            delete temp;
            return true;
        }
        else
        {
            while(temp->next!=NULL){
                if(temp->next->data==s)
                {
                    Node* deletedNode=temp->next;
                    temp->next=temp->next->next;
                    delete deletedNode;
                    return true;
                }
                temp=temp->next;
            }
            return false;
        }
    }

  bool search(const string& s) const
{
    Node* temp=front;
    while(temp!=NULL) //Traverse list
    {
        if(temp->data==s)
            return true;
        temp = temp->next;
    }
    return false;
}

  vector<string> get() const
{
    vector<string> str_vec;
    for(Node* temp=front;temp!=NULL;temp=temp->next)
        str_vec.push_back(temp->data);
    return str_vec;
}

  void deepCopy(const LinkedList& ls)
{
    front=NULL;
    if(ls.front!=NULL) //Only copy if ls is non-empty
    {
        Node* original=ls.front;
        Node* copy;
        copy=new Node(original->data, NULL);
        front=copy;
        original=original->next;
        while(original!=NULL) //Traverse the original copying each node
        {
            copy->next=new Node(original->data, NULL);
            copy=copy->next;
            original=original->next;
        }
    }
}

  void deleteList()
{
    Node* tmp;
    while(front!=NULL){
        tmp=front->next;
        delete front;
        front=tmp;
    }
}
};


      
class HashTable
{
public:
    HashTable(); //default constructor
    HashTable(int); //one parameter constructor
    HashTable(const HashTable&); //copy constructor
    ~HashTable(); //destructor
    HashTable& operator=(const HashTable&); //assignment operator
    bool insert(const string&);
    bool remove(const string&);
    bool search(const string&) const;
    int size() const; //return numOfItems
    int maxSize() const; //return arrSize
    int loadFactor() const;
    vector<string> intersection(const HashTable&) const;
    vector<string> unions(const HashTable&) const;
    vector<string> difference(const HashTable&) const;
private:
    LinkedList* arr;
    int arrSize;
    int numOfItems;
    int hashFunc(const string&) const;
    int getPrime(int) const;
    bool isPrime(int) const;
    void deepCopy(const HashTable& h);
    vector<string> get() const; //returns a vector of all the strings in the HashTable

    int HashTable::hashFunc(const string& s) const //hash function
{
    int hashVal=0,asc;
    for(int i=0;i<s.size();i++)
    {
        asc=s[i]>96?s[i]-96:s[i]-64;
        hashVal=(hashVal*32+asc)%arrSize;
    }
    cout<<hashVal<<endl;
    return hashVal;
}

int HashTable::getPrime(int n) const
{
    int i=2*n;
    while(!isPrime(i))
        i++;
    return i;
}

bool HashTable::isPrime(int n) const
{
    bool isPrime=true;
        for(int count=2;count<n && isPrime; count++)
            if(n%count==0)
                isPrime=false;
    return isPrime;
}

void HashTable::deepCopy(const HashTable& h)
{
    if(arr!=NULL)
        delete arr;
    numOfItems=h.size();
    arrSize=h.maxSize();
    arr=new LinkedList[arrSize];
    for(int i=0;i<arrSize;i++)
        arr[i]=h.arr[i];
}

vector<string> HashTable::get() const //returns a vector of all the strings in the hash table
{
    vector<string> v,tmp_v;
    for(int i=0;i<maxSize();i++)
    {
        tmp_v=arr[i].get();
        for(int j=0;j<tmp_v.size();j++)
            v.push_back(tmp_v[j]);
    }
    return v;
}

/*END OF PRIVATE MEMBER FUNCTIONS*/

/*==========================================================================*/

//PUBLIC MEMBER FUNCTIONS

HashTable::HashTable() //default constructor
{
    arrSize=101;
    arr=new LinkedList[arrSize];
    numOfItems=0;
}

HashTable::HashTable(int n) //creates a hash table to store n items where the size of the array is the smallest prime number >= 2*n
{
    arrSize=getPrime(n);
    arr=new LinkedList[arrSize];
    numOfItems=0;
}

HashTable::HashTable(const HashTable& h) //copy constructor
{
    deepCopy(h);
}

HashTable::~HashTable() //destructor
{
    for(int i=0;i<arrSize;i++)
        arr[i].deleteList();
    delete arr;
}

HashTable& HashTable::operator=(const HashTable& h) //assignment operator
{
    if(this!=&h)
    {
        if(h.arr!=NULL)
            delete arr;
        deepCopy(h);
    }
    return *this;
}

bool HashTable::insert(const string& s) //inserts string s if it doesn't exist in the hash table and returns 1 if insertion successful, 0 otherwise
{
    int hash=hashFunc(s);
    bool successOrFail=arr[hash].insert(s);
    numOfItems++;
    return successOrFail;
}

bool HashTable::remove(const string& s) //removes string s if s exist in the hash table and returns 1 if removal successful, 0 otherwise
{
    int hash=hashFunc(s);
    bool successOrFail=arr[hash].remove(s);
    numOfItems--;
    return successOrFail;
}

bool HashTable::search(const string& s) const //returns 1 if s exist in the hash table, 0 otherwise
{
    int hash=hashFunc(s);
    bool found=arr[hash].search(s);
    return found;
}

int HashTable::size() const //returns numOfItems
{
    return numOfItems;
}

int HashTable::maxSize() const //returns arrSize
{
    return arrSize;
}

int HashTable::loadFactor() const //returns the load factor of the hash table
{
    return numOfItems/arrSize;
}




};


int HashTable::hashFunc(const string& s) const //hash function
{
    int hashVal=0,asc;
    for(int i=0;i<s.size();i++)
    {
        asc=s[i]>96?s[i]-96:s[i]-64;
        hashVal=(hashVal*32+asc)%arrSize;
    }
    cout<<hashVal<<endl;
    return hashVal;
}

int main() {
  
  return 0;
}