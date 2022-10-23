
template <class T>
class linkedListNode {
public:
    T* item = NULL; 
    linkedListNode* next = NULL;

    linkedListNode() {

    }

    linkedListNode(T* item) {
        this->item = item;
    }

    void insert(T* item) {
        if(this->item == NULL) {
            this->item = item;
            return;
        }

        linkedListNode* tempPtr = this;
        
        while(tempPtr->next != NULL) {
            tempPtr = tempPtr->next;
        }

        tempPtr->next = new linkedListNode(item);
    }
};