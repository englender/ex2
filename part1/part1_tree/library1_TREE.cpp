//
// Created by nadav on 12/5/2018.
//

#include "library1.h"
#include "map_tree.h"


void *Init(){
    Map_tree<int,void*> *tree;
    try {
        tree = new Map_tree<int,void*>();
    }catch  (std::exception& e){
        return NULL;
    }
    return (void*)tree;
}

StatusType Add(void *DS, int key, void* value, void** node){
    if(DS == nullptr || node == nullptr){
        return  INVALID_INPUT;
    }
    try {
        ((Map_tree<int,void *>*)DS)->add_node(key,value);
    }catch (std::exception& e){
        return ALLOCATION_ERROR;
    }
    *node=((Map_tree<int,void*>*)DS)->find(key);
    return SUCCESS;
}

StatusType Find(void *DS, int key, void** value){
    if(DS == nullptr || value == nullptr){
        return INVALID_INPUT;
    }
    TreeNode<int,void*>* result=((Map_tree<int,void*>*)DS)->find(key);
    if(result == nullptr)
        return FAILURE;

    *value=result->get_data();
    return SUCCESS;

}

StatusType Delete(void *DS, int key){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    TreeNode<int,void*>* result=((Map_tree<int,void*>*)DS)->find(key);
    if(result == nullptr){
        return FAILURE;
    }

    ((Map_tree<int,void*>*)DS)->remove_node(result);
    return SUCCESS;
}

StatusType DeleteByPointer(void *DS, void* p){
    if(DS == nullptr || p == nullptr){
        return  INVALID_INPUT;
    }

    ((Map_tree<int,void*>*)DS)->remove_node((TreeNode<int,void*>*)p);
    return SUCCESS;

}

StatusType Size(void *DS, int *n){
    if(DS == nullptr || n == nullptr){
        return INVALID_INPUT;
    }

    *n=((Map_tree<int,void*>*)DS)->get_size();
    return SUCCESS;
}

void Quit(void** DS){
    if(DS== nullptr)
        return;;

    auto tmp=(Map_tree<int,void*>*)(*DS);
    delete tmp;
    *DS=NULL;
}