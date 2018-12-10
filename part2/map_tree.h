//
// Created by nadav on 11/29/2018.
//

#ifndef EX2_MAP_TREE_H
#define EX2_MAP_TREE_H

#include <iostream>
#include <algorithm>
//#include "map_tree.cpp"
//#include "library1.h"

using namespace std;
#define MAX_BF 2
#define MIN_BF -2
#define EVEN_BF 0

template <class K, class D>
class TreeNode{
    K key;
    D data;
    int height;

    TreeNode* left_son;
    TreeNode* right_son;
public:
    TreeNode(const K& key, const D& data);

    const K& get_key();
    D* get_data();
    const int get_height();

    TreeNode* get_left_son();
    TreeNode* get_right_son();

    void set_left_son(TreeNode* left_son);
    void set_right_son(TreeNode* right_son);
    void set_height();
    int get_right_height();
    int get_left_height();
    int get_balance_factor();

    ostream& printNode(ostream& os);

};

template <class K, class D>
class Map_tree {
    TreeNode<K,D>* root;
    int size;

public:
    Map_tree();
    ~Map_tree();
    void delete_recurse(TreeNode<K,D>* node_to_delete);

    TreeNode<K,D>* get_root();
    void set_root(TreeNode<K,D>* new_root);

    int get_size() const;

    TreeNode<K,D>* find(const K& key);
    TreeNode<K,D>* find_recurse(const K& key, TreeNode<K,D>* current_node);
    void add_node(const K& key,const D& data);
    void remove_node(TreeNode<K,D>* node_to_remove);

    void add_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa);
    TreeNode<K,D>* roll_left(TreeNode<K,D>* current_node);
    TreeNode<K,D>* roll_right(TreeNode<K,D>* current_node);
    TreeNode<K,D>* roll_LL(TreeNode<K,D>* b, TreeNode<K,D>* a);
    TreeNode<K,D>* roll_RR(TreeNode<K,D>* b, TreeNode<K,D>* a);
    TreeNode<K,D>* roll_LR(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a);
    TreeNode<K,D>* roll_RL(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a);
    void reconnect_to_papa(TreeNode<K,D>* papa, TreeNode<K,D>* tmp_son);
    TreeNode<K,D>* find_papa(const K& key, TreeNode<K,D>* current_node);
    ostream& printTree(ostream& os);
    ostream& print(ostream& os, TreeNode<K,D>* node_to_print);

    void remove_son_with_no_grandsons(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;
    void remove_son_with_one_grandson(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;
    void remove_son_with_two_grandson(TreeNode<K,D>* papa, TreeNode<K,D>* node_to_remove) ;
    void swap_right_sons(TreeNode<K,D>* a,TreeNode<K,D>* b);

    void delete_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa);

    };


//----------------------------------------------------------------------------//
//------------------------------TreeNode Implement--------------------------------//
//----------------------------------------------------------------------------//
template <class K, class D>
TreeNode<K,D>::TreeNode(const K& key, const D& data) : key(key), data(data), height(0),
                                               left_son(nullptr),
                                               right_son(nullptr){
}

template <class K, class D>
const K& TreeNode<K,D>::get_key() {
    return this->key;
}

template <class K, class D>
D* TreeNode<K,D>::get_data() {
    return &this->data;
}

template <class K, class D>
TreeNode<K,D>* TreeNode<K,D>::get_left_son(){
    if(this->left_son== nullptr){
        return nullptr;
    }
    return this->left_son;
}

template <class K, class D>
TreeNode<K,D>* TreeNode<K,D>::get_right_son(){
    if(this->right_son== nullptr){
        return nullptr;
    }
    return this->right_son;
}

template <class K, class D>
void TreeNode<K,D>::set_left_son(TreeNode<K,D>* left_son){
    if(left_son== nullptr)
        this->left_son= nullptr;
    else{
        this->left_son=left_son;
    }
}

template <class K, class D>
void TreeNode<K,D>::set_right_son(TreeNode<K,D>* right_son){
    if(right_son== nullptr)
        this->right_son= nullptr;
    else{
        this->right_son=right_son;
    }
}

template <class K, class D>
void TreeNode<K,D>::set_height(){
    /*
     * sets the node's height. max height between his sons +1
     * if the node has no sons - height is set to 0
     */
    int left_height=this->get_left_height();
    int right_height=this->get_right_height();
    this->height=(std::max(left_height,right_height)+1);
}

template <class K, class D>
const int TreeNode<K,D>::get_height(){
   return this->height;
}

template <class K, class D>
int TreeNode<K,D>::get_right_height(){
    if(this->right_son == nullptr)
        return -1;
    return this->right_son->height;
}

template <class K, class D>
int TreeNode<K,D>::get_left_height(){
    if(this->left_son == nullptr)
        return -1;
    return this->left_son->height;
}

template <class K, class D>
int TreeNode<K,D>::get_balance_factor(){
    /*
     * returns node's balance factor - the difference between left son height and right son height
     */
    return (this->get_left_height())-(this->get_right_height());
}

template <class K, class D>
ostream& TreeNode<K,D>::printNode(ostream& os) {
    /*
     * inside function for printing
     * prints "Key: XXX | Left: XXX | Right: XXX | Height: XXX | BF: XXX "
     */
    os << "Key: " << this->get_key() << " | Left: ";
    if(this->get_left_son()== nullptr)
        os << "-";
    else
        os << this->get_left_son()->get_key();

    os << " | Right: ";
    if(this->get_right_son()== nullptr)
        os << "-";
    else
        os << this->get_right_son()->get_key();
    os << " | Height: " << this->height << " | BF: " << this->get_balance_factor();


    os << endl;

    return os;
}



//----------------------------------------------------------------------------//
//------------------------------TreeNode Tree Implement---------------------------//
//----------------------------------------------------------------------------//

template <class K, class D>
Map_tree<K,D>::Map_tree() : root(nullptr),size(0){
}

template <class K, class D>
Map_tree<K,D>::~Map_tree() {
    delete_recurse(this->root);
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::get_root(){
    return this->root;
}
template <class K, class D>
void Map_tree<K,D>::set_root(TreeNode<K,D>* new_root){
    this->root=new_root;
}

template <class K, class D>
int Map_tree<K,D>::get_size() const{
    return this->size;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find(const K& key){
    return find_recurse(key,this->root);
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find_recurse(const K& key, TreeNode<K,D>* current_node) {
    /*
     * finds the node with the sent key, and returns that node
     * if there is no node with the key in the tree, returns null
     */
    if (current_node == nullptr)                //stop conditions - arrived at bottom of the tree
        return nullptr;

    else if (current_node->get_key() == key)    //stop conditions - found the required node
        return current_node;

    TreeNode<K, D> *node_ptr;
    if (current_node->get_key() > key) {        //the required key is smaller than the current, continue left
        node_ptr = find_recurse(key, current_node->get_left_son());
    } else {                                    //the required key is bigger than the current, continue right
        node_ptr=find_recurse(key, current_node->get_right_son());
    }
    return node_ptr;                            // ?????? roni - not sure we need this ??????
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::find_papa(const K& key, TreeNode<K,D>* papa) {
    /*
     * receives key of node to add/remove, and the tree's root node
     * returns the father of the node to add/remove
     */
    if(papa == nullptr || papa->get_key()==key){
        return nullptr;
    }
    if(papa->get_right_son()== nullptr && papa->get_left_son()== nullptr)
        return papa;
    if(papa->get_key()<key && papa->get_right_son()!= nullptr &&
            papa->get_right_son()->get_key()==key)
        return papa;                //papa_key<key and also it has right_son_key==key
    if(papa->get_key()<key && papa->get_right_son()== nullptr)
        return papa;                //if papa_key<key and also it has no right son
    if(papa->get_key()>key && papa->get_left_son()!= nullptr &&
            papa->get_left_son()->get_key()==key)
        return papa;                //papa_key>key and also it has left_son_key==key
    if(papa->get_key()>key && papa->get_left_son()== nullptr)
            return papa;            //if papa_key>key and also it has no left son

    if(papa->get_key()<key)         //the required key is bigger than the current, continue right
        return find_papa(key,papa->get_right_son());

    return find_papa(key,papa->get_left_son());
}


template <class K, class D>
void Map_tree<K,D>::add_node(const K& key,const D& data){
    /*
     * receives the key and data of new node to add
     * finds the node's father and add it to the tree as his son
     * corrects the BF of the tree after adding the node
     */
    TreeNode<K,D>* new_node = new TreeNode<K,D>(key, data);
    TreeNode<K,D>* papa=this->find_papa(new_node->get_key(),this->get_root());

    if(papa== nullptr)                                  // Empty tree
        this->set_root(new_node);
    else if(papa->get_key() > new_node->get_key()){
        papa->set_left_son(new_node);
    }else{
        papa->set_right_son(new_node);
    }
    add_correct(new_node->get_key(),this->get_root(), nullptr);
    this->size++;
}

template <class K, class D>
void Map_tree<K,D>::remove_node(TreeNode<K,D>* node_to_remove) {
    /*
     * receives node to remove.
     * finds it's father and removes him as his son, then removes the node
     * corrects BF of tree after removing the node
     */
    TreeNode<K,D>* papa=find_papa(node_to_remove->get_key(), this->get_root());
    K* key=new K(node_to_remove->get_key());
    if(node_to_remove->get_right_son()== nullptr &&
            node_to_remove->get_left_son()== nullptr) {              //no grandsons

        remove_son_with_no_grandsons(papa, node_to_remove);
    }
    else if(node_to_remove->get_right_son()== nullptr ||
             node_to_remove->get_left_son()== nullptr){             //only one grandson
        remove_son_with_one_grandson(papa, node_to_remove);
    }else{
        remove_son_with_two_grandson(papa, node_to_remove);
    }
    delete_correct(*key,this->get_root(), nullptr);
    delete key;
    this->size--;
}

template <class K, class D>
void Map_tree<K,D>::delete_recurse(TreeNode<K,D>* node_to_delete){
    /*
     * function called from Map_tree destructor
     * receives the tree's root and removes all nodes in the tree
     */
    if(node_to_delete== nullptr)
        return;

    delete_recurse(node_to_delete->get_left_son());
    delete_recurse(node_to_delete->get_right_son());
    delete node_to_delete;

}

template <class K, class D>
void Map_tree<K,D>::remove_son_with_no_grandsons(TreeNode<K,D>* papa,
                                                 TreeNode<K,D>* node_to_remove) {
    if(papa == nullptr){                         //then node to remove is root
        this->set_root(nullptr);
    }
    else if(node_to_remove->get_key()>papa->get_key()) {          //then node to remove is papa's right son
        papa->set_right_son(nullptr);
    }else{
        papa->set_left_son(nullptr);
    }
    delete node_to_remove;
}

template <class K, class D>
void Map_tree<K,D>::remove_son_with_one_grandson(TreeNode<K,D>* papa,
                                                 TreeNode<K,D>* node_to_remove) {

    if(node_to_remove->get_right_son()!= nullptr)
        reconnect_to_papa(papa,node_to_remove->get_right_son());
    else
        reconnect_to_papa(papa,node_to_remove->get_left_son());

    delete node_to_remove;
}

template <class K, class D>
void Map_tree<K,D>:: remove_son_with_two_grandson(TreeNode<K,D>* papa,
                                                  TreeNode<K,D>* node_to_remove) {
    TreeNode<K, D> *node_to_switch = node_to_remove->get_right_son();
    TreeNode<K, D> *node_to_switch_PAPA = node_to_remove;
    while(node_to_switch->get_left_son()!= nullptr){
        node_to_switch_PAPA=node_to_switch;
        node_to_switch=node_to_switch->get_left_son();
    }
    TreeNode<K, D> *tmp_ptr = node_to_remove->get_left_son();
    node_to_remove->set_left_son(nullptr);
    node_to_switch->set_left_son(tmp_ptr);

    swap_right_sons(node_to_remove,node_to_switch);
    reconnect_to_papa(papa,node_to_switch);

    if(node_to_switch_PAPA!=node_to_remove) {             //example 2,3
        reconnect_to_papa(node_to_switch_PAPA, node_to_remove);
        if (node_to_remove->get_right_son() != nullptr) {
            node_to_switch_PAPA->set_left_son(node_to_remove->get_right_son());
        } else {
            node_to_switch_PAPA->set_left_son(nullptr);
        }
    }
    else{                                               //node_to_switch_PAPA=node_to_remove. example 1,4
        if (node_to_remove->get_right_son() != nullptr){
            tmp_ptr=node_to_remove->get_right_son();
            node_to_remove->set_right_son(nullptr);
            node_to_switch->set_right_son(tmp_ptr);
        }else{
            node_to_switch->set_right_son(nullptr);
        }
    }
    delete node_to_remove;

}

template <class K, class D>
void Map_tree<K,D>::swap_right_sons(TreeNode<K,D>* a,TreeNode<K,D>* b) {
    if(a->get_right_son()==b){
        TreeNode<K,D> *tmp=b->get_right_son();
        b->set_right_son(a);
        a->set_right_son(tmp);

    }else{
        TreeNode<K,D> *tmp=a->get_right_son();
        a->set_right_son(b->get_right_son());
        b->set_right_son(tmp);
    }
}

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//


template <class K, class D>
ostream& Map_tree<K,D>::printTree(ostream& os) {
    TreeNode<K,D>* current_node=this->get_root();
    if(current_node == nullptr)
        return os << "Empty Tree!!!" << endl;
    return this->print(os, this->get_root());

}

template <class K, class D>
ostream& Map_tree<K,D>::print(ostream& os, TreeNode<K,D>* node_to_print){
    node_to_print->printNode(os);
    if(node_to_print->get_left_son()!= nullptr)
        this->print(os,node_to_print->get_left_son());

    if(node_to_print->get_right_son()!= nullptr)
        this->print(os,node_to_print->get_right_son());

    return os;
}

//----------------------------------------------------------------------------//
//------------------------------Roll Implement--------------------------------//
//----------------------------------------------------------------------------//

template <class K, class D>
void Map_tree<K,D>::add_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa){
    if (current_node->get_key() == key) {
        return;
    }
    TreeNode<K,D>* tmp_ptr;
    if (current_node->get_key() > key) {
        add_correct(key, current_node->get_left_son(),current_node);
        current_node->set_height();
        if(current_node->get_balance_factor()==MAX_BF)
            if(papa== nullptr)
                this->set_root(roll_left(current_node));
            else {
                tmp_ptr=roll_left(current_node);
                reconnect_to_papa(papa, tmp_ptr);
            }
    } else {
        add_correct(key, current_node->get_right_son(),current_node);
        current_node->set_height();
        if(current_node->get_balance_factor()==MIN_BF)
            if(papa== nullptr)
                this->set_root(roll_right(current_node));
            else {
                tmp_ptr = roll_right(current_node);
                reconnect_to_papa(papa, tmp_ptr);
            }
    }

}

template <class K, class D>
void Map_tree<K,D>::delete_correct(const K& key, TreeNode<K,D>* current_node, TreeNode<K,D>* papa) {
    if (current_node == nullptr) {
        return;
    }
    TreeNode<K,D>* tmp_ptr;
    if (current_node->get_key() > key) {
        delete_correct(key, current_node->get_left_son(), current_node);
    } else {
        delete_correct(key, current_node->get_right_son(), current_node);
    }
    current_node->set_height();

    if (current_node->get_balance_factor() == MAX_BF) {
        if (papa == nullptr) {
            this->set_root(roll_left(current_node));
        }
        else {
            tmp_ptr = roll_left(current_node);
            reconnect_to_papa(papa, tmp_ptr);
        }
    }
    else if(current_node->get_balance_factor()==MIN_BF){
        if(papa== nullptr) {
            this->set_root(roll_right(current_node));
        }
        else {
            tmp_ptr = roll_right(current_node);
            reconnect_to_papa(papa, tmp_ptr);
        }
    }
}


template <class K, class D>
void Map_tree<K,D>::reconnect_to_papa(TreeNode<K,D>* papa, TreeNode<K,D>* tmp_son){

    if(papa== nullptr){                         //if(tmp_son==root)
        this->set_root(tmp_son);
        return;
    }
    if(tmp_son->get_key()>papa->get_key()){

        papa->set_right_son(tmp_son);
    }else{
        papa->set_left_son(tmp_son);
    }
}



template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_left(TreeNode<K,D>* current_node){
    if(current_node->get_left_son()->get_balance_factor()>=EVEN_BF){
        return roll_LL(current_node,current_node->get_left_son());
    }
    else{
        return roll_LR(current_node,current_node->get_left_son()->get_right_son(),
                current_node->get_left_son());
    }
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_right(TreeNode<K,D>* current_node){
    if(current_node->get_right_son()->get_balance_factor()<=EVEN_BF) {
        return roll_RR(current_node->get_right_son(), current_node);
    }
    else{
        return roll_RL(current_node->get_right_son(),
                current_node->get_right_son()->get_left_son(),current_node);
    }
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_LL(TreeNode<K,D>* b, TreeNode<K,D>* a){
// b is root: BF=2
// a is left son of b: BF>=0
// a<b
    b->set_left_son(a->get_right_son());
    a->set_right_son(b);

    b->set_height();
    a->set_height();

    if(b==this->root)
        this->root=a;
    return a;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_RR(TreeNode<K,D>* b, TreeNode<K,D>* a){
// a is root: BF=-2
// b is right son of a: BF<=0
// a<b
    a->set_right_son(b->get_left_son());
    b->set_left_son(a);

    a->set_height();
    b->set_height();

    if(a==this->root)
        this->root=b;

    return b;
}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_LR(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a){
// c is root: BF=2
// a is left son of c: BF=-1
// b is right son of a
// a<b<c
    a->set_right_son(b->get_left_son());
    b->set_left_son(a);
    c->set_left_son(b);             //not sure if necessary

    c->set_left_son(b->get_right_son());
    b->set_right_son(c);

    c->set_height();
    a->set_height();
    b->set_height();

    if(c==this->root)
        this->root=b;

    return b;

}

template <class K, class D>
TreeNode<K,D>* Map_tree<K,D>::roll_RL(TreeNode<K,D>* c, TreeNode<K,D>* b, TreeNode<K,D>* a) {
// a is root: BF=-2
// c is right son of a: BF=1
// b is left son of c
// a<b<c
    a->set_right_son(b);
    c->set_left_son(b->get_right_son());             //not sure if necessary
    b->set_right_son(c);

    a->set_right_son(b->get_left_son());
    b->set_left_son(a);

    a->set_height();
    c->set_height();
    b->set_height();

    if(a==this->root)
        this->root=b;

    return b;
};
#endif //EX2_MAP_TREE_H
