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


bool Image::add_label_to_image(const int segmentID, const int label){
    /*
     * receives the segmentID and label to add to the relevent segmentID
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

const int Image::get_label_from_image(const int segmentID){
    return segments_array[segmentID];       //if there is no label returns -1
}

bool Image::delete_label_from_image(const int segmentID){
    /*
     * receives segmentID and removes the label from that segmentID
     * if there is no label, returns false
     * removes the label and adds the image to unlabeled list, and returns true
     */
    if(segments_array[segmentID] == EMPTY_SEG)
        return false;
    segments_array[segmentID]=EMPTY_SEG;
    this->unlabled_segments->add_node(segmentID,EMPTY_SEG);
    return true;
}

int* Image::get_all_unlabeledSegments(int *segments){
    segments=(int*)malloc(sizeof(this->num_of_unlabeledSegments()));

    ListNode<int,int>* node_ptr=this->unlabled_segments->get_first();

    for (int i = 0; i <this->num_of_unlabeledSegments() ; ++i) {
        segments[i]=node_ptr->get_key();
        node_ptr=node_ptr->get_next();
    }
    return segments;
}

int Image::num_of_unlabeledSegments(){
    return this->unlabled_segments->get_size();
}
//----------------------------------------------------------------------------//
//---------------------------ImageTagger Implement----------------------------//
//----------------------------------------------------------------------------//

ImageTagger::ImageTagger(int segments) : max_segments(segments){
    this->images=new Map_tree<int,Image>;
}

int ImageTagger::get_segments(){
    return this->max_segments;
}

Image* ImageTagger::get_image(int imageID){
    /*
     * returns Image type with the imageID
     * returns nullptr in case there is no image with the imageID
     */
    TreeNode<int,Image>* image_node= this->images->find(imageID);

    if(image_node== nullptr){
        return nullptr;
    }
    Image* image= (image_node->get_data());
    return image;
}


bool ImageTagger::image_exist(int imageID){
    /*
     * returns true/false if image exists/doesn't exist
     */
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
    TreeNode<int,Image>* image_node= this->images->find(imageID);

    if(image_node == nullptr)
        return false;           //image does not exist

    this->images->remove_node(image_node);
    return true;                //image removed
}

