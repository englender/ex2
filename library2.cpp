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