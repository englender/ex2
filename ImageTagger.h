//
// Created by nadav on 12/4/2018.
//
#include "map_tree.h"
#include "library2.h"
#include "node_list.h"

#ifndef EX2_IMAGETAGGER_H
#define EX2_IMAGETAGGER_H

class ImageTagger {
    int imageID;
    int max_segments;

    int *segments_array;
    Node_list<int,int>* unlabled_segments;

public:
    ImageTagger(const int imageID,const int segments);
};

ImageTagger::ImageTagger(const int imageID, const int segments): imageID(imageID),
                                                                 max_segments(segments){
    this->segments_array=(int*)malloc(this->max_segments* sizeof(int));

    this->unlabled_segments=new Node_list<int,int>();

    for (int i = 0; i < segments; i++) {                //initialize the structs
        this->segments_array[i]=-1;
        this->unlabled_segments->add_node(i,-1);
    }
}

#endif //EX2_IMAGETAGGER_H
