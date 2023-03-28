#include <iostream>
#include <limits.h>
using namespace::std;

int getMax(int num1, int num2) {
    return ((num1 > num2) ? num1 : num2);
}

class Node {

    friend void preOrderTraversal(Node* rootNode);
    friend string inOrderTraversal(Node* rootNode, string result);

    friend Node* rightRotate(Node* rootPtr);
    friend Node* leftRotate(Node* rootPtr);

    friend int getHeight(Node* node);
    friend int getBalanceFactor(Node* node);
    
    friend Node* balanceBST(Node* node);

    friend Node* insertNode(Node* node, Node* studentNode);    

    friend Node* minimumNodeFinder(Node* treePtr);
    friend Node* deleteNode(Node* node, string studentName);

    friend Node* searchNode(Node* node, string studentName);

    friend int main();

private:

    // Student details
    string name;
    int age;
    double weight;
    double cgpa;

    // tree details
    int height;
    Node *left;
    Node *right;

public:
    Node() {
        name = "";
        age = -1;
        weight = 0;
        cgpa = 0;

        height = 0;
        left = NULL;
        right = NULL;
    }

    Node(string name, int age, double weight, double cgpa) { // This is a leaf node, since both left and right sub-trees are NULL.
        this->name = name;
        this->age = age;
        this->weight = weight;
        this->cgpa = cgpa;

        // We are considering height of leaf node as 0, according to the logic explained at the top.
        left = NULL;
        right = NULL;
    }

    Node(string name, int age, double weight, double cgpa, Node *left, Node *right) {

        this->name = name;
        this->age = age;
        this->weight = weight;
        this->cgpa = cgpa;

        // Objects are created and stored somewhere in memory so we can get their address and store it in the `left` and `right` pointer

        this->left = left;
        this->right = right;

        height = 1 + getMax(((left == NULL) ? -1 : left->height), ((right == NULL) ? -1 : right->height));
        
    }
};

// Visit the left node, then the root node, then the right node.
string inOrderTraversal(Node* rootNode, string result) {
    if(rootNode == NULL) {
        return result;
    }

    result += inOrderTraversal(rootNode->left, "");   

    result += string(rootNode->name) + ", " + to_string(rootNode->age) + ", " + to_string(rootNode->weight) + ", " + to_string(rootNode->cgpa) + ";\n";

    result += inOrderTraversal(rootNode->right, "");

    return result;   
}

int getHeight(Node* node) {
    if(node == NULL) {
        return -1;
        // Since leaf nodes have height of 0, NULL nodes that are child nodes of leaf nodes should have height even less, so they have height as -1.
    }
    else {
        return (node->height);
    }
}


Node* rightRotate(Node* rootPtr) {
    if(rootPtr == NULL) {
        return rootPtr;
    }

    Node* newRoot = rootPtr -> left;    
    
    if( newRoot == NULL) { //! To prevent segmentation fault and since there is no newRoot
        return rootPtr;
    } 
    
    // Assigning the right branch of the left child node of rootPtr (rootPtr -> left -> right), which is about to become root itself, to the left of rootPtr. Note that it can be NULL as well, which is okay, since we anyways need to remove the old left branch of rootPtr, other there would be duplicate branches in the tree.
    rootPtr->left = newRoot->right;     
    // Updating height of rootPtr after adding a branch to it.
    rootPtr->height = 1 + getMax(getHeight(rootPtr->left), getHeight(rootPtr->right));
    
    // Assigning the old rootPtr to the right sub-tree of the NEW root (which is 'rootPtr -> left' i.e., 'newRoot')
    newRoot -> right = rootPtr; 
    // Updating height of newRoot after adding a branch to it.
    newRoot->height = 1 + getMax(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

Node* leftRotate(Node* rootPtr) {
    if(rootPtr == NULL) {
        return rootPtr;
    }
    
    Node* newRoot = rootPtr -> right;
    
    if(newRoot == NULL) { //! To prevent segmentation fault and since there is no newRoot
        return rootPtr;
    }
    
    // Assigning the left branch of the right child node of rootPtr (rootPtr -> right -> left), which is about to become root itself, to the right of rootPtr. Note that it can be NULL as well, which is okay, since we anyways need to remove the old right branch of rootPtr, other there would be duplicate branches in the tree
    rootPtr->right = newRoot->left; 

    // Updating height of rootPtr after adding a branch to it.
    rootPtr->height = 1 + getMax(getHeight(rootPtr->left), getHeight(rootPtr->right));

    // Assigning the old rootPtr to the left sub-tree of the NEW root (which is 'rootPtr -> right' i.e., 'newRoot')
    newRoot -> left = rootPtr; 
    // Updating height of newRoot after adding a branch to it.
    newRoot->height = 1 + getMax(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

int getBalanceFactor(Node* node) {
    if(node == NULL) {
        return 0;
    }
    else {
        return ( getHeight(node->left) - getHeight(node->right) );
    }
}


// TODO: Not working with a normal bst. Only working as a helper
Node* balanceBST(Node* node) {
    if(node == NULL) {
        return node;
    }

    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
    // We don't perform a simple incrementation because it is possible that before insertion the left sub-tree had a height of 4 and right sub-tree had a height of 5. An element is inserted in the left sub-tree but still the height of the parent node remains same. 

    int balanceFactor = getBalanceFactor(node);

    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case (since balance factor is greater than 1 {left sub-tree larger, so right rotation needed} & balance factor of the left sub-tree is greater than or equal to 0 meaning there are more/equal nodes in the left sub-tree OF THE LEFT SUB-TREE compared to right sub-tree of the child node, so we can apply right rotation directly, unlike LR case.
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
        return rightRotate(node);
    }
        
    // Right Right Case (since balance factor is less than -1 {right sub-tree larger, so left rotation need} & balance factor of the right sub-tree is less than 0 meaning there are more/equal nodes in the right sub-tree OF THE RIGHT SUB-TREE compared to left sub-tree of the child node, so we can apply left rotation directly, unlike RL case.
    if (balanceFactor < -1 && getBalanceFactor(node->right) < 0) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
        
        node->left = leftRotate(node->left);        

        return rightRotate(node);
    }
 
    // Right Left Case
    if (balanceFactor < -1 && getBalanceFactor(node->right) >= 0) {
        node->right = rightRotate(node->right);

        return leftRotate(node);
    }    

    
    return node; // -1 <= balanceFactor <= 1
}

Node* insertNode(Node* node, Node* studentNode) {

    // 1. Performing regular recursive BST insertion
    if(node == NULL) {
        return new Node(studentNode->name, studentNode->age, studentNode->weight, studentNode->cgpa); // this will have height = 0;
    }

    if( studentNode->name < (node -> name) ) {
        node->left = insertNode(node->left, studentNode);
    }
    else if( studentNode->name > (node -> name) ) {
        node->right = insertNode(node->right, studentNode);
    }
    else {

        // Updating values
        node->age = studentNode->age;
        node->weight = studentNode->weight;
        node->cgpa = studentNode->cgpa;
        
        return node; // No need to go any further since no insertion took place
    }
    
    return balanceBST(node); 
}

Node* minimumNodeFinder(Node* treePtr) {
    
    while(treePtr != NULL && treePtr->left != NULL) { // Sequence of conditions is important in this case because if treePtr is actually NULL and we try to access 'left', we will get segmentation fault.
        
        treePtr = treePtr -> left; //? This is perfectly fine to do and won't mutate the original pointer since we are not derefencing the pointer before assignment.
    }
        
    return treePtr;
}

Node* deleteNode(Node* node, string studentName) {
    if(node == NULL) {
        cout << "Student record doesn't exist. Deletion aborted...\n";
        return node;
    }

    if(studentName < node->name) {
        node->left = deleteNode(node->left, studentName);
    }
    else if(studentName > node->name) {
        node->right = deleteNode(node->right, studentName);
    }
    else { // Node to be deleted found

        //? Node with 0 children
        if(node -> left == NULL && node -> right == NULL) {

            return NULL; // Instead of returning node, which would mean that the element would stay in the BST, we returned NULL which means the element would no longer be in BST.

        }

        //* Node with 1 child
        else if(node -> left == NULL) { // The left sub-tree is not present but right sub-tree is. So, instead of returning node, we directly return the pointer to its right sub-tree, removing the link to node.
            
            Node* temp = node -> right;
            
            delete node; //? de-allocating the memory allocated to node
            
            return temp;

        }
        //* Node with 1 child
        else if(node -> right == NULL) { // The right sub-tree is not present but left sub-tree is. So, instead of returning node, we directly return the pointer to its left sub-tree, removing the link to node.
            
            Node* temp = node -> left;
            
            delete node; //? de-allocating the memory allocated to node

            return temp;

        }

        //! Node with 2 child nodes
        Node* nodeSuccessor = minimumNodeFinder(node->right); // This won't be NULL in any case, since 'node' will DEFINITELY have 2 children, as cases of 0 and 1 children have been taken care of above.
        node->name = nodeSuccessor->name;
        node->age = nodeSuccessor->age;
        node->weight = nodeSuccessor->weight;

        //? Deleting the node we just used to replace value of 'node'
        //! It is logically OK to delete this key from RIGHT sub-tree, because, at this point, this key is unique in the right sub-tree of 'node' (NOT unique in the entire node BST, because node->key is also same)
        deleteNode(node->right, nodeSuccessor->name); 
        // This will go on recursively, if the successor's keep having 2 children, otherwise the above conditions will be satisfied
    }
    
    return balanceBST(node);
}

Node* searchNode(Node* node, string studentName) {
    if(node == NULL) {
        cout << "This student record is not present. Display operation aborted...\n";
        return NULL; // Node not present
    }

    if( studentName < (node -> name) ) {
        return searchNode(node->left, studentName);
    }
    else if( studentName > (node -> name) ) {
        return searchNode(node->right, studentName);
    }

    return node;
    //? Desired node found where studentName == node->name
}