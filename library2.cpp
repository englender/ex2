//
// Created by ronien on 05/12/2018.
//

#include "library2.h"
#include "ImageTagger.h"

void *Init(int segments){
    ImageTagger* DS;

    try {
        DS  = new ImageTagger(segments);
    }catch  (std::exception& e){
        return NULL;
    }
    return (void*)DS;
}

StatusType AddImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0)
        return INVALID_INPUT;

    try{
        if(((ImageTagger*)DS)->add_image(imageID)==false)
            return FAILURE;
    }catch (std::exception& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType DeleteImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0)
        return INVALID_INPUT;



}