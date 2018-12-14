//
// Created by nadav on 12/5/2018.
//

#include "library1.h"
#include "node_list.h"

void *Init(){
    Node_list<int,void*> *list;
    try {
        list = new Node_list<int,void*>();
    }catch (std::exception& e){
        return NULL;
    }
    return (void*)list;
}

StatusType Add(void *DS, int key, void* value, void** node){
    if(DS == nullptr || node == nullptr){
        return INVALID_INPUT;
    }
    try {
        ((Node_list<int,void*>*)DS)->add_node(key,value);
    }catch(std::exception& e){
        return ALLOCATION_ERROR;
    }
    *node=((Node_list<int,void*>*)DS)->get_first();
    return SUCCESS;
}

StatusType Find(void *DS, int key, void** value){
    if(DS == nullptr || value == nullptr){
        return INVALID_INPUT;
    }
    ListNode<int,void*>* result=((Node_list<int,void*>*)DS)->find(key);
    if(result == nullptr)
        return FAILURE;

    *value=result->get_data();
    return SUCCESS;
}

StatusType Delete(void *DS, int key){
    if(DS == nullptr){
        return INVALID_INPUT;
    }
    ListNode<int,void*>* result=((Node_list<int,void*>*)DS)->find(key);
    if(result == nullptr){
        return  FAILURE;
    }

    ((Node_list<int,void*>*)DS)->remove_node(result);
    return SUCCESS;
}

StatusType DeleteByPointer(void *DS, void* p){
    if(DS == nullptr || p == nullptr){
        return INVALID_INPUT;
    }

    ((Node_list<int,void*>*)DS)->remove_node((ListNode<int,void*>*)p);

    return SUCCESS;
}

StatusType Size(void *DS, int *n){
    if(DS == nullptr || n == nullptr){
        return INVALID_INPUT;
    }

    *n=((Node_list<int,void*>*)DS)->get_size();

    return SUCCESS;
}

void Quit(void** DS){
    if(DS == nullptr)
        return;

    auto tmp=(Node_list<int,void*>*)(*DS);
    delete tmp;

    *DS=NULL;
}