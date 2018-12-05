//
// Created by nadav on 12/4/2018.
//
#include "map_tree.h"
#include "library2.h"
#include "node_list.h"

#ifndef EX2_IMAGETAGGER_H
#define EX2_IMAGETAGGER_H

class Image {
    int imageID;
    int max_segments;

    int *segments_array;
    Node_list<int,int>* unlabled_segments;

public:
    Image(const int imageID,const int segments);
    ~Image();
    int get_imageID();
    bool AddLabelToImage(const int segmentID, const int label);
    const int GetLabelFromImage(const int segmentID);
    bool DeleteLabelFromImage(const int segmentID);
    Node_list<int,int>* GetAllUnLabeledSegments();

};

class ImageTagger {
    Map_tree<int,Image>* images;
    int max_segments;

public:
    ImageTagger(int segments);
//    ~ImageTagger();
    bool image_exist(int imageID);  //check if need to static
    bool add_image(int imageID);
    bool delete_image(int imageID);

};


#endif //EX2_IMAGETAGGER_H
