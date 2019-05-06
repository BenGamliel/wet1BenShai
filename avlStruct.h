
#ifndef WET1_AVL_H
#define WET1_AVL_H


#include <iostream>


template<class T, class K>
class AVLNode {
private:
    //Struct of each vertex in the AVL tree
    K key_;
    T data_;
    AVLNode<T, K> *left;
    AVLNode<T, K> *right;
    AVLNode<T, K> *parent;
    int factor,height;

    //Methods for the object node
public:
    //Default constructor with no inputs
    AVLNode<T, K>()
            : key_(), data_(), left(NULL), right(NULL), parent(NULL), factor(0) ,height(0) {}

    AVLNode<T, K>(const T& data,const K& key,AVLNode<T,K>* parent)
            : key_(key), data_(data), left(NULL), right(NULL), parent(parent), factor(0) ,height(0) {}

    //Constructor with data and key inputs
    AVLNode<T, K>(const T &data, const K &key) : key_(key), data_(data),
                                                 left(NULL), right(NULL),
                                                 parent(NULL) {}

    //Destructor because must
    ~AVLNode<T, K>() {
        this->left = NULL;
        this->right = NULL;
    }

    //Method that return the node data
    T &getData() {
        return this->data_;
    }

    int &getFactor(){
        return this->factor;
    }

    int &getHeight(){
        return this->height;
    }

    //Method that return the node key
    const K &getKey() const {
        return this->key_;
    }

    void setData(T data) {
        this->data_ = data;
    }

    void setFactor(int factor){
        this->factor = factor;
    }
    void setHeight(int height){
        this->height = height;
    }

    void setKey(K key) {
        this->key_ = key;
    }

    //Method that return the left son of node
    AVLNode<T, K> *getLeft() {
        //if (!this->left) return NULL;
        return this->left;
    }

    //Method that return the right son of node
    AVLNode<T, K> *getRight() {
        //if (!this->right) return NULL;
        return this->right;
    }

    //Method that return the parent of node
    AVLNode<T, K> *getParent() {
        //if (!this->parent) return NULL;
        return this->parent;
    }

    //Method that set the left son
    void setLeftSon(AVLNode<T, K> *left) {
        this->left = left;
    }

    //Method that set the right son
    void setRightSon(AVLNode<T, K> *right) {
        this->right = right;
    }

    //Method that set the parent
    void setParent(AVLNode<T, K> *parent) {
        this->parent = parent;
    }

};


template<class T, class K, class Compare = std::less<K> >
class AVLTree {
private:
    int size;
    friend class AVLNode<T,K>;
    AVLNode<T, K> *root;


    void deleteData(AVLNode<T, K> *root);

    void deleteSubTree(AVLNode<T, K> *node);

    //Delete one node from tree and balance
    //void deleteAVLNode(AVLNode<T, K> *node, K key);

    AVLNode<T, K> *sortedArrayToAVL(T *values, K **keys, int x, int y);

public:
    //Constructor
    AVLTree() : size(0), root(NULL) {};
    void deleteData();
    AVLTree(T *values, K ** keys, int size) {
        this->root = sortedArrayToAVL(values, keys, 0, size - 1);
    }

    ~AVLTree() {
        if (this->root) {
            deleteSubTree(root);
        }
    }

    //Get the root of tree
    AVLNode<T, K> *getRoot() {
        return this->root;
    };


    //Get the balance factor of vertex
    int balanceFactor(AVLNode<T, K> *root) const;

    //Get The Height of sub-tree
    int getHeight(AVLNode<T, K> *node) const;

    //Insert new node to the tree with data and key given
    void insert(const T &data, const K &key);

    void deleteBYKey(const K &key);

    //Rotate right
    void rotateRight(AVLNode<T, K> *root);

    //Rotate left
    void rotateLeft(AVLNode<T, K> *root);

    //Find the minimum in the tree
    AVLNode<T, K> *findMin(AVLNode<T, K> *root);

    //Find in tree
    AVLNode<T, K> *findBYKey(const K &key);

    //Find in tree
    AVLNode<T, K> *find(AVLNode<T, K> *root, const K &key);

    AVLNode<T, K> *nextINOrder(AVLNode<T, K> *root, const K &key);

    //Print inorder
    void printInOrder(AVLNode<T, K> *root) const;

    //Print inorder
    void printInOrder() const;


    void inOrderToArray(T *arr);

    void inOrderToArray(AVLNode<T, K> *node, T *arr, int *iterator);

    void inOrderToArrayKeys(K **arr);

    void inOrderToArrayKeys(AVLNode<T, K> *node, K **arr, int *iterator);

    int getSize() const{
        return this->size;
    }

    void swap_node(AVLNode<T, K> *a, AVLNode<T, K> *b) {
        K key = a->getKey();
        T data = a->getData();
        a->setKey(b->getKey());
        a->setData(b->getData());
        b->setKey(key);
        b->setData(data);
    }

    void removeLeaf(AVLNode<T,K>* node);
    void removeSingleN(AVLNode<T,K>* node);
    void removeDoubleN(AVLNode<T,K>* node);
    void update(AVLNode<T,K>* node);

    void updateroot();

    void roll_LR(AVLNode<T, K> *node1);

    void roll_RR(AVLNode<T, K> *node);

    void roll_LL(AVLNode<T, K> *node1);

    void roll_RL(AVLNode<T, K> *node1);

    void roll(AVLNode<T, K> *node);

};

//Insert new node to the tree
//template<class T, class K, class Compare>
//bool AVLTree<T, K, Compare>::insert(const T &data, const K &key) {
//    //if(this->find(root,key)) return false;
//    AVLNode<T, K> *new_node = new AVLNode<T, K>(data, key);
//    if (!this->root) {
//        this->root = new_node;
//    } else {
//        this->insertAVLNode(this->root, new_node);
//    }
//    this->size++;
//    return true;
//
//}

//inser new node to the tree
//Param: generic data, generic tree
template <class T, class K, class Compare>
void AVLTree<T, K, Compare>::insert(const T& data, const K& key) {
    if (!root) {
        root = new AVLNode<T,K>(data, key);
        size++;
        return ;
    }

    bool fLeft = true;
    AVLNode<T,K>* current = root;
    AVLNode<T,K>* previous = current->getParent();
    while (current) {
        previous = current;
        fLeft = Compare()(key, current->getKey()) != false;
        current = fLeft ? current->getLeft() : current->getRight();
    }

    AVLNode<T,K>* new_node = new AVLNode<T,K>(data, key, previous);
    if (fLeft) {
        previous->setLeftSon(new_node);
    } else {
        previous->setRightSon(new_node);
    }

    update(new_node);
    roll(new_node);
    updateroot();
    size++;


}



//Calculate the heigth fo given node
template<class T, class K, class Compare>
int AVLTree<T, K, Compare>::getHeight(AVLNode<T, K> *node) const {
    int height = 0;
//    if(!node->getRight()){
//        height = 1 + getHeight(node->getLeft());
//    }
//    else if(!node->getLeft()){
//        height = 1 + getHeight(node->getRight());
//    }
    if (node) {
        int left = getHeight(node->getLeft());
        int right = getHeight(node->getRight());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}



//Recursive delete
template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::deleteSubTree(AVLNode<T, K> *node) {
    if (node) {
        deleteSubTree(node->getLeft());
        deleteSubTree(node->getRight());
        delete node; // Post Order Deletion
    }
}


//Calculate the height of left sub tree minus height of right sub tree
template<class T, class K, class Compare>
int AVLTree<T, K, Compare>::balanceFactor(AVLNode<T, K> *root) const {
    int balance = 0;
    if (root) {
        balance = getHeight(root->getLeft()) - getHeight(root->getRight());
    }
    return balance;
}



template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::rotateLeft(AVLNode<T, K> *root) {
    AVLNode<T, K> *newroot = root->getRight();
    root->setRightSon(newroot->getLeft());
   // newroot->getLeft()->setParent(root);
    newroot->setLeftSon(root);

    if (root->getParent() == NULL) {
        this->root = newroot;
        newroot->setParent(NULL);
    } else {
        if (root->getParent()->getLeft() == root) {
            root->getParent()->setLeftSon(newroot);
        } else {
            root->getParent()->setRightSon(newroot);
        }
        newroot->setParent(root->getParent());
    }
    root->setParent(newroot);
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::rotateRight(AVLNode<T, K> *root) {
    // Rotate node
    AVLNode<T, K> *newroot = root->getLeft();
    root->setLeftSon(newroot->getRight());
    newroot->setRightSon(root);

    // Adjust tree
    if (root->getParent() == NULL) {
        this->root = newroot;
        newroot->setParent(NULL);
    } else {
        if (root->getParent()->getLeft() == root) {
            root->getParent()->setLeftSon(newroot);
        } else {
            root->getParent()->setRightSon(newroot);
        }
        newroot->setParent(root->getParent());
    }

    root->setParent(newroot);
}

template<class T, class K, class Compare>
AVLNode<T, K> *AVLTree<T, K, Compare>::findBYKey(const K &key) {
    return find(this->root, key);
}

template<class T, class K, class Compare>
AVLNode<T, K> *AVLTree<T, K, Compare>::find(AVLNode<T, K> *root, const K &key) {
    if (root) {
        if (root->getKey() == key)
            return root; // Found
        else if (Compare()(key, root->getKey()))
            return find(root->getLeft(), key);
        else
            return find(root->getRight(), key);
    }
    return NULL;
}

template<class T, class K, class Compare>
AVLNode<T, K> *AVLTree<T, K, Compare>::findMin(AVLNode<T, K> *root) {
    if (!root) return NULL;
    if (!root->getLeft()) return root;
    else {
        return findMin(root->getLeft());
    }
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::printInOrder() const {
    return this->printInOrder(this->root);
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::printInOrder(AVLNode<T, K> *root) const {
    if (root) {
        printInOrder(root->getLeft());  // Left
        std::cout << root->getKey();// Parent
        std::cout << " ";
        printInOrder(root->getRight()); // Right
    }
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::inOrderToArray(T *arr) {
    int iterator = 0;
    return inOrderToArray(this->root, arr, &iterator);
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::inOrderToArray(AVLNode<T, K> *root, T *arr,
                                          int *iterator) {
    if (root) {
        inOrderToArray(root->getLeft(), arr, iterator);
        (arr)[*iterator] = root->getData();
        (*iterator)++;
        inOrderToArray(root->getRight(), arr, iterator);
    }
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::inOrderToArrayKeys(K **arr) {
    int iterator = 0;
    inOrderToArrayKeys(this->root, arr, &iterator);
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::inOrderToArrayKeys(AVLNode<T, K> *root, K **arr,
                                                int *iterator) {
    if (root) {
        inOrderToArrayKeys(root->getLeft(), arr, iterator);
        ((*arr))[*iterator] = root->getKey();
        (*iterator)++;
        inOrderToArrayKeys(root->getRight(), arr, iterator);
    }
}

template<class T, class K, class Compare>
AVLNode<T, K> *AVLTree<T, K, Compare>::sortedArrayToAVL(T *values, K **keys,
                                                        int x, int y) {
    if (x > y)
        return NULL;
    int mid = (x + y) / 2;
    AVLNode<T, K> *root = new AVLNode<T, K>(values[mid], ((*keys))[mid]);
    root->setLeftSon(sortedArrayToAVL(values, keys, x, mid - 1));
    root->setRightSon(sortedArrayToAVL(values, keys, mid + 1, y));
    return root;
}

template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::deleteBYKey(const K &key)  {
    AVLNode<T,K>* current = this->root;
    while (Compare()(key, current->getKey()) || Compare()(current->getKey(), key)) {
        current = Compare()(key, current->getKey()) ? current->getLeft() : current->getRight();
    }

    AVLNode<T,K>* parent = current->getParent();
    if (!current->getLeft() && !current->getRight()) {
        removeLeaf(current);
    } else if (!current->getRight() || !current->getLeft()) {
        removeSingleN(current);
    } else {
        removeDoubleN(current);
    }

    //Lets balance the tree
    update(parent);
    roll(parent);
    updateroot();
    this->size--;
}



template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::removeLeaf(AVLNode<T,K>* node) {
    if (!node->getParent()) {
        delete node;
         this->root= NULL;
        return;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeftSon(NULL);
    } else {
        node->getParent()->setRightSon(NULL);
    }
    delete (node);
}


template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::removeSingleN(AVLNode<T,K>* node) {
    if (node->getLeft()) { // has left
        if (!node->getParent()) {
            this->root = node->getLeft();
            this->root->setParent(NULL);
            delete node;
            return;
        }
        if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeftSon(node->getLeft());
        } else {
            node->getParent()->setRightSon(node->getLeft());
        }
        node->getLeft()->setParent(node->getParent());
    } else {
        if (!node->getParent()) {
            this->root = node->getRight();
            this->root->setParent(NULL);
            delete node;
            return;
        }
        if (node == node->getParent()->getLeft()) {
            node->getParent()->setLeftSon(node->getRight());
        } else {
            node->getParent()->setRightSon(node->getRight());
        }
        node->getRight()->setParent(node->getParent());
    }
    delete node;
}



template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::removeDoubleN(AVLNode<T,K>* node) {
    AVLNode<T,K>* node1 = node;
    node = node1->getRight();
    while (node->getLeft()) {
        node = node->getLeft();
    }

    swap_node(node1, node);

    if (!node->getRight()) {
        removeLeaf(node);
    } else {
        removeSingleN(node);
    }
}


template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::update(AVLNode<T,K>* node) {
    while (node) {
        int left_h = node->getLeft() ? node->getLeft()->getHeight() : -1;
        int right_h = node->getRight() ? node->getRight()->getHeight() : -1;
        node->setFactor(left_h - right_h);
        node->setHeight(std::max(left_h, right_h) + 1) ;
        node = node->getParent();
    }
}



template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::updateroot() {
    if (!this->root) return;
    while (this->root->getParent()) {
        this->root = this->root->getParent();
    }
}


//Roll left
template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::roll_LL(AVLNode<T,K>* node1) {
    AVLNode<T,K>* node = node1->getLeft();
    if (!node) return;
    int height_node1_r = node1->getRight() ? getHeight(node1->getRight()) : -1;
    int height_node_r = node->getRight() ? getHeight(node->getRight()) : -1;
    int height_a_left = node->getLeft() ? getHeight(node->getLeft()) : -1;
    node->setParent(node1->getParent()) ;
    if (node1->getParent() && node1 == node1->getParent()->getLeft())
        node1->getParent()->setLeftSon(node);
    else if (node1->getParent()) {
        node1->getParent()->setRightSon(node);
    }
    node1->setParent(node);
    node1->setLeftSon(node->getRight()) ;
    if (node->getRight()) {
        node->getRight()->setParent(node1);
    }
    node->setRightSon(node1);
    node1->setHeight(std::max(height_node1_r, height_node_r) + 1) ;
    node1->setFactor(height_node_r - height_node1_r) ;
    node->setHeight(std::max(node1->getHeight(), height_a_left) + 1) ;
    node->setFactor(height_a_left - node1->getHeight()) ;
}

template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::roll_RR(AVLNode<T,K>* node) {
    AVLNode<T,K>* node1 = node->getRight();
    if (!node1) {
        return;
    }
    int height_node_l = node->getLeft() ? node->getLeft()->getHeight() : -1;  //Height
    int height_node1_r = node1->getRight() ? node1->getRight()->getHeight() : -1;   ////Height
    int height_node1_l = node1->getLeft() ? node1->getLeft()->getHeight() : -1;   ////Height
    node1->setParent(node->getParent());
    if (node->getParent() && node == node->getParent()->getLeft())
        node->getParent()->setLeftSon(node1);
    else if (node->getParent()) {
        node->getParent()->setRightSon(node1);
    }

    node->setParent(node1);

    node->setRightSon(node1->getLeft()) ;

    if (node1->getLeft()) {
        node1->getLeft()->setParent(node);
    }

    node1->setLeftSon(node);

    node->setHeight(std::max(height_node_l, height_node1_l) + 1);
    node->setFactor(height_node_l - height_node1_l);
    node1->setHeight(std::max(node->getHeight(), height_node1_r) + 1);
    node1->setFactor(node->getHeight() - height_node1_r);
}

template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::roll_LR(AVLNode<T,K>* node1) {
    AVLNode<T,K>* node = node1->getLeft();
    roll_RR(node);
    roll_LL(node1);
}

template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::roll_RL(AVLNode<T,K>* node1) {
    AVLNode<T,K>* node = node1->getRight();
    roll_LL(node);
    roll_RR(node1);
}

//Decide how to roll
template <class T,class K,class Compare>
void AVLTree<T,K,Compare>::roll(AVLNode<T,K>* node) {
    AVLNode<T,K>* current = node;
    while (current) {
        int current_factor = current->getFactor();
        if (current_factor >= -1 && current_factor <= 1) {
            current = current->getParent();
            continue;
        }
        int left_factor = current->getLeft() ? current->getLeft()->getFactor() : -1;
        int right_factor = current->getRight() ? current->getRight()->getFactor() : -1;
        if (current_factor == 2 && left_factor >= 0) {
            roll_LL(current);
        } else if (current_factor == 2 && left_factor == -1) {
            roll_LR(current);
        } else if (current_factor == -2 && right_factor <= 0) {
            roll_RR(current);
        } else if (current_factor == -2 && right_factor == 1) {
            roll_RL(current);
        }
        current = current->getParent();
    }
}

//template<class T, class K, class Compare>
//void AVLTree<T, K, Compare>::deleteBYKey(const K &key) {
//    AVLNode<T, K> *newnode = this->find(root, key);
//    this->printInOrder();
//    std::cout << "\n" << std::endl;
//    this->deleteAVLNode(newnode, newnode->getKey());
//    size--;
//}
//
//template<class T, class K, class Compare>
//void AVLTree<T, K, Compare>::deleteAVLNode(AVLNode<T, K> *node, K key) {
//    if (node == root && this->size == 1) {
//        delete root;
//        root = NULL;
//    }
//    else if (node == root && this->size == 2 && !node->getRight()) {
//        AVLNode<T,K>* node1 = root;
//        this->root=root->getLeft();
//        this->root->setParent(NULL);
//        delete node1;
//    }
//    else if (node == root && this->size == 2 && !node->getLeft()) {
//        AVLNode<T,K>* node1 = root;
//        this->root=root->getRight();
//        this->root->setParent(NULL);
//        delete node1;
//    }
//    else if(node == root && this->size > 2){
//        AVLNode<T, K> *node1 = nextINOrder(this->root, node->getKey());
//        if(node1 == NULL){
//            node1=root->getLeft();
//            swap_node(root,node1);
//            root->setLeftSon(node1->getLeft());
//            node1->getLeft()->setParent(root);
//            delete node1;
//        }
//        else{
//            this->swap_node(node1, node);
//            deleteAVLNode(node1, node1->getKey());
//        }
//
//    } else if (!node->getLeft() && !node->getRight() &&
//               node->getParent()->getLeft() == node) {
//        node->getParent()->setLeftSon(NULL);
//        delete node;
//    } else if (!node->getLeft() && !node->getRight() &&
//               node->getParent()->getRight() == node) {
//        node->getParent()->setRightSon(NULL);
//        delete node;
//    } else if (node->getLeft() && !node->getRight() &&
//               node->getParent()->getLeft() == node) {
//        node->getParent()->setLeftSon(node->getLeft());
//        node->getLeft()->setParent(node->getParent());
//        delete node;
//    } else if (node->getLeft() && !node->getRight() &&
//               node->getParent()->getRight() == node) {
//        node->getParent()->setRightSon(node->getRight());
//        node->getRight()->setParent(node->getParent());
//        delete node;
//    } else if (!node->getLeft() && node->getRight() &&
//               node->getParent()->getLeft() == node) {
//        node->getParent()->setLeftSon(node->getLeft());
//        node->getLeft()->setParent(node->getParent());
//        delete node;
//    } else if (!node->getLeft() && node->getRight() &&
//               node->getParent()->getRight() == node) {
//        node->getParent()->setRightSon(node->getRight());
//        node->getRight()->setParent(node->getParent());
//        delete node;
//    } else {
//        AVLNode<T, K> *node1 = nextINOrder(node, node->getKey());
//        this->swap_node(node1, node);
//        delete node1;
//        //deleteAVLNode(node1, node1->getKey());
//    }
//
//    //update(parent);
//    //Lets balance the tree
//    if(root) {
//        int balance = balanceFactor(root);
//        if (balance > 1) { // left tree unbalanced
//            if (balanceFactor(root->getLeft()) <
//                0) // right child of left tree is the cause
//                rotateLeft(root->getLeft()); // double rotation required
//            rotateRight(root);
//        } else if (balance < -1) { // right tree unbalanced
//            if (balanceFactor(root->getRight()) >
//                0) // left child of right tree is the cause
//                rotateRight(root->getRight());
//            rotateLeft(root);
//        }
//    }
//    //updateroot();
//}

//template <class T,class K,class Compare>
//void AVLTree<T,K,Compare>::updateroot() {
//    if (!this->root) return;
//    while (this->root->getParent()) {
//        this->root = this->root->getParent();
//    }
//}

//template <class T,class K,class Compare>
//void AVLTree<T,K,Compare>::update(AVLNode<T,K>* node) {
//    while (node) {
//        int left_h = node->getLeft() ? getHeight(node->getLeft()) : -1;
//        int right_h = node->getRight() ? getHeight(node->getRight()) : -1;
//        node->setFactor(left_h - right_h);
//        node->setHeight(std::max(left_h, right_h) + 1);
//        node = node->getParent();
//    }
//}

//Function to find Inorder Successor in a BST
template<class T, class K, class Compare>
AVLNode<T, K> *
AVLTree<T, K, Compare>::nextINOrder(AVLNode<T, K> *root, const K &key) {
    // Search the Node - O(h)
    AVLNode<T, K> *current = findBYKey(key);
    if (current == NULL) return NULL;
    if (current->getRight() != NULL) {  //Case 1: Node has right subtree
        return (findMin(current->getRight())); // O(h)
    } else {   //Case 2: No right subtree  - O(h)
        AVLNode<T, K> *successor = NULL;
        AVLNode<T, K> *ancestor = root;
        while (ancestor != current) {
            if (Compare()(current->getKey(), ancestor->getKey())) {
                successor = ancestor; // so far this is the deepest node for which current node is in left
                ancestor = ancestor->getLeft();
            } else
                ancestor = ancestor->getRight();
        }
        return successor;
    }
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::deleteData() {
    return deleteData(this->root);
}

template<class T, class K, class Compare>
void AVLTree<T, K, Compare>::deleteData(AVLNode<T, K> *root) {
    if (root) {
        deleteData(root->getLeft());
        deleteData(root->getRight());
        if(root->getData() != NULL){
            delete root->getData(); // Post Order Deletion
            root->getData() = NULL;
        }
    }
}




//template <class T,class K,class Compare>
//AVLNode* AVLTree<T,K,Compare>::remove(AVLNode* p,const K& key) // k key deletion from p tree
//{
//    if (!p) return 0;
//    if (Compare()(key,p->getKey()))
//        p->setLeftSon(remove(p->getLeft(), key));
//    else if (Compare()(p->getKey(),key))
//        p->setRightSon(remove(p->getRight(), key));
//    else //  k == p->key
//    {
//        AVLNode* q = p->getLeft();
//        AVLNode* r = p->getRight();
//        delete p;
//        if( !r ) return q;
//        AVLNode* min = findmin®;
//        min->right = removemin®;
//        min->left = q;
//        return balance(min);
//    }
//    return balance(p);
//}
//
//template <class T,class K,class Compare>
//AVLNode* AVLTree<T,K,Compare>::balance(AVLNode* p) // p node balance
//{
//    fixheight(p);
//    if( bfactor(p)==2 )
//    {
//        if( bfactor(p->right) < 0 )
//            p->right = rotateright(p->right);
//        return rotateleft(p);
//    }
//    if( bfactor(p)==-2 )
//    {
//        if( bfactor(p->left) > 0  )
//            p->left = rotateleft(p->left);
//        return rotateright(p);
//    }
//    return p; // no balance needed
//}
//
//// Searching the node with the minimal key in p tree
//template <class T,class K,class Compare>
//AVLNode* AVLTree<T,K,Compare>::findMin(AVLNode<T,K>* p){
//    AVLNode* current;
//    current = p->getLeft();
//    return current?findMin(p->getLeft)():p;
//}
//
//template <class T,class K,class Compare>
//void AVLTree<T,K,Compare>::fixheight(AVLNode* p)
//{
//    unsigned char hl = height(p->left);
//    unsigned char hr = height(p->right);
//    p->height = (hl>hr ? hl : hr) + 1;
//}


#endif //WET1_AVL_H