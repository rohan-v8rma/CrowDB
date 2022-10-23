
template <class T>
class linkedList {
public:
    T* item = NULL; 
    linkedList* next = NULL;

    linkedList() {

    }

    linkedList(T* item) {
        this->item = item;
    }

    void insert(T* item) {
        if(this->item == NULL) {
            this->item = item;
            return;
        }

        linkedList* tempPtr = this;
        
        while(tempPtr->next != NULL) {
            tempPtr = tempPtr->next;
        }

        tempPtr->next = new linkedList(item);
    }
};