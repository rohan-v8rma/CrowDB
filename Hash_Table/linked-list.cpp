class Node { 

public:
    int originalKey;
    
    Node* dataBase;

    Node* next;

    // Data member
    Node() {
        this->value = -1;
        this->next = NULL;
    };
    
    Node(int value) {
        this->value = value;
    };
    
    
};

class linkedList {
    Node* head = NULL;
  
public:
    linkedList(int elementCt) {
        
        Node* tempPtr = head;     
      
        for(int elementNo = 1; elementNo <= elementCt; elementNo++) {
            printf("Enter element %d : ", elementNo);
            scanf("%d", &(tempPtr -> value));
            
            if(elementNo == elementCt) {
                tempPtr -> next = NULL;    
            }
            else {
                tempPtr -> next = new Node;
                tempPtr = tempPtr -> next;
            }
        };
    }
    
    // Function to insert a node at the end of the linked list.
    void insertNode(int value) {
        Node* tempPtr = head;
        while(tempPtr -> next != NULL) {
          tempPtr = tempPtr -> next;
        }
        tempPtr -> next = new Node(value);
    };

    // Function to delete the
    // node at given position
    void deleteNode(int value) {
        
    };
  
    // Function to print the
    // linked list.
    void displayList() {
        Node* tempPtr = this->head;
        int elementNo = 1;
        while( tempPtr ) { //? NULL has truth-value of 0, other pointer values have truth-value of 1
            printf("Element %d : %d\n", elementNo++, tempPtr -> value);
            tempPtr = tempPtr -> next;
        }
    }  
};

int main() {
  
}