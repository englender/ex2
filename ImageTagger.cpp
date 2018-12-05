//
// Created by nadav on 12/4/2018.
//
#define EMPTY_SEG -1
#include "ImageTagger.h"

//----------------------------------------------------------------------------//
//-----------------------------Image Implement--------------------------------//
//----------------------------------------------------------------------------//

Image::Image(const int imageID, const int segments): imageID(imageID),
                                                                 max_segments(segments){
    this->segments_array=(int*)malloc(this->max_segments* sizeof(int));

    this->unlabled_segments=new Node_list<int,int>();

    for (int i = 0; i < segments; i++) {                //initialize the structs
        this->segments_array[i]=EMPTY_SEG;
        this->unlabled_segments->add_node(i,EMPTY_SEG);
    }
}

Image::~Image(){
    free(this->segments_array);

}

int Image::get_imageID(){
    return this->imageID;
}

bool Image::AddLabelToImage(const int segmentID, const int label){

    if(segments_array[segmentID]!= EMPTY_SEG)
        return false;

    segments_array[segmentID]=label;
    ListNode<int,int>* node_to_add=this->unlabled_segments->find(segmentID);
    this->unlabled_segments->remove_node(node_to_add);
    return true;
}

const int Image::GetLabelFromImage(const int segmentID){
    return segments_array[segmentID];       //if there is no label returns -1
}

bool Image::DeleteLabelFromImage(const int segmentID){
    if(segments_array[segmentID] == EMPTY_SEG)
        return false;
    segments_array[segmentID]=EMPTY_SEG;
    this->unlabled_segments->add_node(segmentID,EMPTY_SEG);
    return true;
}

Node_list<int,int>* Image::GetAllUnLabeledSegments(){
    return this->unlabled_segments;
};


//----------------------------------------------------------------------------//
//---------------------------ImageTagger Implement----------------------------//
//----------------------------------------------------------------------------//

ImageTagger::ImageTagger(int segments) : images(), max_segments(segments){
}