//
// Created by DELL on 5/5/2018.
//

#ifndef WET1_AVL_H
#define WET1_AVL_H
#define nullptr 0
#include <math.h>
#include <iostream>
#define CONNECT(new_parent,new_child, side) \
    new_parent->side = new_child; \
    new_parent->side->parent = new_parent
#define MAX(arg1, arg2) \
    (arg1 < arg2) ? arg2 : arg1
#define UPDATE_HIGHT(a_node) \
    if (a_node != nullptr) { \
        if (a_node->right && a_node->left) {\
            a_node->hight = MAX(a_node->right->hight,a_node->left->hight); \
        } else if (a_node->right) { \
            a_node->hight = a_node->right->hight; \
        } else if (a_node->left) { \
            a_node->hight = a_node->left->hight; \
        } else {\
            a_node->hight = -1; \
        } \
        a_node->hight++; \
    }
#define UPDATE_SIZE(a_node) \
    if (a_node != nullptr) { \
        if (a_node->right && a_node->left) {\
            a_node->size = a_node->right->size + a_node->left->size; \
        } else if (a_node->right) { \
            a_node->size  = a_node->right->size; \
        } else if (a_node->left) { \
            a_node->size = a_node->left->size; \
        } else {\
            a_node->size = 0; \
        } \
        a_node->size++; \
    }

template <class T>
class AVL {
    
    AVL* parent;
    AVL* left;
    AVL* right;
    T* data;
    int hight;
    int size;
    
    //calculate balance factor
    int BF(){
        int left_hight=-1;
        int right_hight=-1;
        if(left) {
            left_hight=left->hight;
        }
        if(right) {
            right_hight=right->hight;
        }
        return left_hight - right_hight;
    }
    // connect 2 nodes by the correct order
    AVL* connect(AVL* par) {
        if (par == nullptr) {
            parent = nullptr;
        }
        else if (*(par->data) < *data)
        {
            CONNECT(par, this, right);
        }
        else
        {
            CONNECT(par, this, left);
        }
        return this;
    }
    //disconnect a node from it's parent
    void disconnect(){
        if (parent)
        {
            if ((parent->right) == this)
            {
                parent->right = nullptr;
            }
            else
            {
                parent->left = nullptr;
            }
            UPDATE_HIGHT(parent);
            UPDATE_SIZE(parent);
        }
    }
    //check if a node is a leakf
    bool isLeaf() {
        return (right == nullptr) && (left == nullptr);
    }
    //create an empty avl tree (an almost complete tree) size n
    static AVL* AVLempty(int n) {
        int h = ceil(log2(n+1))-1; //TODO verify ceil is acctually ceil
        int complete_size = 0;
        for (int i=0;i<=h;i++)
        {
            complete_size += pow(2,i);
        }
        int last_line_size = pow(2,h) - (complete_size - n);
        AVL* head = new AVL;
        createEmpty(head, h, &last_line_size);
        return head;
    }
    //recursive function used by AVLempty
    static int createEmpty(AVL* node, int curr_hight, int* last_line_size) {
        if (curr_hight < 0) return 0;
        if (curr_hight == 0)
        {
            node->hight = curr_hight;
            return 1;
        }
        int size_right=0, size_left=0;
        AVL *node_right= nullptr, *node_left = nullptr;
        if ((curr_hight>1 ) || (curr_hight==1 && *last_line_size>0))//create node
        {
            node_left = new AVL;
            if (curr_hight == 1)
            {
                (*last_line_size)--;
            }
            size_left = createEmpty(node_left, curr_hight-1, last_line_size);
            node->left = node_left;
            node_left->parent = node;
        }
        if ((curr_hight>1) || (curr_hight==1 && *last_line_size>0)) //create node
        {
            node_right = new AVL;
            if(curr_hight==1)
            {
                (*last_line_size)--;
            }
            size_right = createEmpty(node_right, curr_hight-1, last_line_size);
            node->right = node_right;
            node_right->parent = node;
        }
        node->size = size_left + size_right + 1;
        node->hight = curr_hight;
        return node->size;
    }
    
    // search recursively. recursion stops if we found the data or reached the
    // end of the search path. then return the equal if it exists, and if not
    // then the one its supposed to be connected to
    AVL* search(AVL* node, const T& t) const {
        if ( node && node->data!= nullptr)
        {
            if (t>(*(node->data)) && node->right)
            {
                return  search(node->right, t);
            }
            else if (t<*(node->data) && node->left )
            {
                return search(node->left, t);
            }
        }
        return node;
    }
    template <typename doSomething>
    void inorder(doSomething& func){
        
        if (left) {
            left->inorder(func);
        }
        func(this);
        if(right){
            right->inorder(func);
        }
    }
    template <typename doSomething>
    void inorderOpposite(doSomething& func){
        if(right){
            right->inorderOpposite(func);
        }
        func(this);
        if (left) {
            left->inorderOpposite(func);
        }
    }
    template <typename doSomething>
    void postorder(doSomething func) {
        if (left) {
            left->postorder(func);
        }
        if(right){
            right->postorder(func);
        }
        func(this);
    }
    //get the minimum
    AVL* min(AVL* node) {
        while(node->left) {
            node = node->left;
        }
        return node;
    }
    
    //fix the balance factor for each node in the tree after insertion of removal.
    AVL* fixBalanceFactor(AVL* node) {
        AVL* local_root;
        bool root_changed=false;
        for (AVL* par ; node != nullptr ; node=par) {
            par = node->parent;
            if (! (node->BF() < 2 && node->BF() > -2)) {
                if (par ==  nullptr) {
                    root_changed = true;
                }
                if (node->BF() == 2) {
                    if (node->left->BF() == -1) {
                        rollLeft(node->left);
                        local_root =rollRight(node);
                    } else {
                        local_root=rollRight(node);
                    }
                } else if (node->BF() == -2) {
                    if (node->right->BF() == 1) {
                        rollRight(node->right);
                        local_root=rollLeft(node);
                    } else {
                        local_root=rollLeft(node);
                    }
                }
            }
        }
        if (root_changed) {
            return local_root;
        }
        return nullptr;
    }
    //removes the node and connecr its child instead, returns the child
    // (the child is a node with correct hight and size)
    AVL* removeOneChild(AVL* node, AVL* swap_data, AVL** root_ptr) {
        if (node->right == nullptr) {
            if (node->parent== nullptr) {
                *root_ptr = node->left;
            }
            AVL* temp_node = node->left->connect(node->parent);
            node->left = nullptr;
            if (swap_data) {
                T* temp_data = node->data;
                node->data = swap_data->data;
                swap_data->data = temp_data;
            }
            delete node;
            return temp_node;
        } else {
            // second option: (node->left == nullptr)
            if (node->parent== nullptr) {
                *root_ptr = node->right;
            }
            AVL* temp_node = node->right->connect(node->parent);
            node->right = nullptr;
            if (swap_data) {
                T* temp_data = node->data;
                node->data = swap_data->data;
                swap_data->data = temp_data;
            }
            delete node;
            return temp_node;
        }
    }
    
    AVL* removeLeaf(AVL* node,AVL* swap_data , AVL** root_ptr) {
        AVL* parent_node = node->parent;
        if (*(parent_node->data) < *(node->data)) {
            parent_node->right = nullptr;
        } else {
            parent_node->left = nullptr;
        }
        if (swap_data) {
            T* temp_data = node->data;
            node->data = swap_data->data;
            swap_data->data = temp_data;
        }
        delete node;
        UPDATE_HIGHT(parent_node);
        parent_node->size--;
        return parent_node;
    }
    AVL* rollLeft(AVL* node){
        AVL* child = node->right;
        AVL* pre_parent =node->parent;
        
        if (child->left) {
            CONNECT(node, child->left, right);
        } else {
            node->right = nullptr;
        }
        UPDATE_HIGHT(node);
        UPDATE_SIZE(node);
        CONNECT(child, node, left);
        UPDATE_HIGHT(child);
        UPDATE_SIZE(child);
        child->connect(pre_parent);
        UPDATE_HIGHT(pre_parent);
        UPDATE_SIZE(pre_parent);
        return child;
    }
    AVL* rollRight(AVL* node){
        AVL* child = node->left;
        AVL* pre_parent =node->parent;
        if (child->right) {
            CONNECT(node, child->right, left);
        } else {
            node->left  = nullptr;
        }
        UPDATE_HIGHT(node);
        UPDATE_SIZE(node);
        CONNECT(child, node, right);
        UPDATE_HIGHT(child);
        UPDATE_SIZE(child);
        child->connect(pre_parent);
        UPDATE_HIGHT(pre_parent);
        UPDATE_SIZE(pre_parent);
        return child;
    }
    
    AVL(T* d ): parent(nullptr), left(nullptr), right(nullptr),data(d),
                hight(0), size(1){}
public:
    
    int getSize(){
        return size;
    }
    
    AVL() :  parent(nullptr), left(nullptr), right(nullptr),data(nullptr),
             hight(-1), size(0){}
    
    ~AVL() {
        if (right){
            right->postorder(destroy());
        }
        if (left) {
            left->postorder(destroy());
        }
        if (data) {
            delete data;
        }
    }
    
    
    T* get(const T& t) {
        if (size == 0) {
            return nullptr;
        }
        AVL* temp = search(this,t);
        if (temp->data != nullptr) {
            if(*(temp->data) == t) {
                return temp->data;
            }
        }
        return  nullptr;
    }
    
    // insert new data to the tree
    bool insert(const T& t, AVL** root_ptr) {
        T* new_data = new T(t);
        if (size == 0) {
            data = new_data;
            size++;
            hight++;
            return true;
        }
        AVL* node = search(this, *new_data);
        AVL* new_node = new AVL(new_data);
        
        if (*(node->data)<*new_data || *(node->data)>*new_data) {
            new_node->connect(node);
        } else {
            delete new_node;
            return false;
        }
        
        // FIX hights
        for(int i=1 ; node && node->hight<i ; i++) {
            node->hight = i;
            node= node->parent;
        }
        
        //Fix sizes
        node = new_node->parent;
        for(int i=(*root_ptr)->hight-node->hight;node && i>=0;i--) {
            UPDATE_SIZE(node);
            node = node->parent;
        }
        AVL* new_root = fixBalanceFactor(new_node->parent);
        if (new_root) {
            *root_ptr = new_root;
        }
        return true;
    }
    
    
    bool remove(const T& data, AVL** root_ptr) { //TODO exceptions?
        AVL* node = search(this, data);
        if (*(node->data) < data || *(node->data) > data) {
            return false;
        }
        if (parent==nullptr && isLeaf()) {
            delete this->data;
            this->data = nullptr;
            node->size = 0;
            node->hight = 0;
            return true;
        }
        if (node->isLeaf() && node->parent==nullptr) {
            delete node->data;
            node->hight = 0;
            node->size = 0;
        } else if (node->isLeaf()) {
            node = removeLeaf(node,nullptr,root_ptr);
        } else if (node->right == nullptr || node->left == nullptr) {
            node = removeOneChild(node,nullptr,root_ptr);
        } else {
            AVL* next = min(node->right);
            //  node = next->parent;
            if (next->isLeaf()) {
                node = removeLeaf(next, node, root_ptr);
            } else {
                node = removeOneChild(next,node, root_ptr);
            }
        }
        AVL* temp_node = node;
        //now "node"'s hight is supposed to be corrct. fix the above
        for(; node  ; node=node->parent) { // TODO
            UPDATE_HIGHT(node);
        }
        node = temp_node;
        //fix sizes
        for(; temp_node ; ) {
            UPDATE_SIZE(temp_node);
            temp_node=temp_node->parent;
        }
        AVL* new_root = (*root_ptr)->fixBalanceFactor(node);
        if (new_root) {
            *root_ptr = new_root;
        }
        return true;
    }
    
    // assistance classes:
    class destroy {
    public:
        void operator()(AVL* node) {
            if (node){
                if (node->right==nullptr && node->left==nullptr) {
                    node->disconnect();
                    delete node;
                }
            }
        }
    };
};


#endif //WET1_AVL_H
