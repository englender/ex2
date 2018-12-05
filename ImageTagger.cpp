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
    /*
     * recieves the segmentID and label to add to the relevent segmentID
     * if the segment already has a label returns false
     * updates the segments ID label, and removes it from unlabeled_segments list
     */
    if(segments_array[segmentID]!= EMPTY_SEG)       //return false if segment
        return false;                               // already labeled

    segments_array[segmentID]=label;
    ListNode<int,int>* node_to_remove=this->unlabled_segments->find(segmentID);
    this->unlabled_segments->remove_node(node_to_remove);
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

ImageTagger::ImageTagger(int segments) : max_segments(segments){
    this->images=new Map_tree<int,Image>;
}

int ImageTagger::get_segments(){
    return this->max_segments;
}

bool ImageTagger::image_exist(int imageID){
    /*
     * we code "find" to return father of the relevant key if it's not exist
     * so we need to check if the returning node have the same key that was sent
     *
     * ~~~~we need to think if we want to change the original find~~~~~~~~~
     * */
    if(this->images->find(imageID)== nullptr)
        return false;           //if there is no image with imageID
    return true;
}


bool ImageTagger::add_image(int imageID){
    /*
     * return false if the imageID already exist, and the add was not completed
     * else, adds create new Image with the imageID, add it to the tree,
     * and return true
    */
    if(this->image_exist(imageID))
        return false;                       //the image already exists
    Image *new_image=new Image(imageID,this->max_segments);
    this->images->add_node(imageID,*new_image);
    return true;
}
bool ImageTagger::delete_image(int imageID) {
    if(!this->image_exist(imageID))
        return false;
//    this->images->remove_node()           //???
}

bool ImageTagger::is_segment_labeled(int imageID, int segmentID){
    /*
     * recieves an image that exists in the tree and a segment ID
     * returns true if segment is labled and false if it isn't
     */
    Image *new_image=this->images->find(imageID);
    if(new_image->GetLabelFromImage(segmentID)== EMPTY_SEG)
        return false;
    return true;
}