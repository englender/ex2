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
    this->segments_array=new int[max_segments] ;

    this->unlabled_segments=new Node_list<int,int>();

    for (int i = 0; i < segments; i++) {                //initialize the structs
        this->segments_array[i]=EMPTY_SEG;
        this->unlabled_segments->add_node(i,EMPTY_SEG);
    }
}

Image::~Image(){
    delete[] this->segments_array;
    delete (unlabled_segments);
}


bool Image::add_label_to_image(const int segmentID, const int label){
    /*
     * receives the segmentID and label to add to the relevant segmentID
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

void Image::get_all_unlabeledSegments(int *segments){

    ListNode<int,int>* node_ptr=this->unlabled_segments->get_first();

    for (int i = 0; i <this->num_of_unlabeledSegments() ; i++) {
        segments[i]=node_ptr->get_key();
        node_ptr=node_ptr->get_next();
    }
}


ListNode<int,int>* Image::get_unlabel_list(){
    return this->unlabled_segments->get_first();
}


int Image::num_of_unlabeledSegments(){
    return this->unlabled_segments->get_size();
}

bool Image::label_exist(int label){
    for (int i = 0; i < this->max_segments; i++) {
        if(this->segments_array[i]==label)
            return true;
    }
    return false;
}

const int* Image::get_segments_array() {

    return this->segments_array;
}

int Image::count_num_labels_in_image(int label) {
    int sum = 0;
    for (int i = 0; i < this->max_segments; i++) {              // loop scanning all segments of current image
        if (this->get_segments_array()[i] == label) {
            sum++;
        }
    }
    return sum;
}
//----------------------------------------------------------------------------//
//---------------------------ImageTagger Implement----------------------------//
//----------------------------------------------------------------------------//

ImageTagger::ImageTagger(int segments) : max_segments(segments){
    this->images=new Map_tree<int,Image*>;
}

ImageTagger::~ImageTagger(){
    delete (this->images);
}

int ImageTagger::get_segments(){
    return this->max_segments;
}

Image* ImageTagger::get_image(int imageID){
    /*
     * returns Image type with the imageID
     * returns nullptr in case there is no image with the imageID
     */
    TreeNode<int,Image*>* image_node= this->images->find(imageID);

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
     * else, create new Image with the imageID, add it to the tree,
     * and return true
    */
    if(this->image_exist(imageID))
        return false;                       //the image already exists
    Image *new_image=new Image(imageID,this->max_segments);
    this->images->add_node(imageID,new_image);
    return true;                            //image added
}
bool ImageTagger::delete_image(int imageID) {
    TreeNode<int,Image*>* image_node= this->images->find(imageID);
    if(image_node == nullptr)
        return false;           //image does not exist
    Image* image_to_delete = image_node->get_data();
    delete (image_to_delete);
    this->images->remove_node(image_node);

    return true;                //image removed
}

int ImageTagger::count_labels(int label){
    int sum=0;
    this->count_label_recurse(this->images->get_root(),&sum,label);

    return sum;
}


void ImageTagger::count_label_recurse(TreeNode<int,Image*>* current, int *sum, int label){
    if(current== nullptr)
        return;

    count_label_recurse(current->get_left_son(), sum, label);
    count_label_recurse(current->get_right_son(), sum, label);

    if((current->get_data())->label_exist(label))
        (*sum)+=(current->get_data())->count_num_labels_in_image(label);

}



void ImageTagger::initial_segments_arrays(TreeNode<int,Image*>* current, int label,
                                          int *index, int **images,
                                          int **segments){
    if(current== nullptr)
        return;

    //in-order scan
    initial_segments_arrays(current->get_left_son(),label,index,images,segments);

    if((current->get_data())->label_exist(label)){
        for (int i = 0; i < this->max_segments; i++) {              // loop scanning all segments of current image
            if ((current->get_data())->get_segments_array()[i] == label) {
                (*images)[*index] = (int) (current->get_key());
                (*segments)[*index] = i;
                *index=(*index)+1;
            }
        }
    }

    initial_segments_arrays(current->get_right_son(),label,index,images,segments);

}

TreeNode<int,Image*>* ImageTagger::get_root(){
    return this->images->get_root();
}

void ImageTagger::delete_all_data_fields(TreeNode<int,Image*>* tmp) {
    if(tmp== nullptr)
        return;

    //pre-order scan
    delete (tmp->get_data());

    delete_all_data_fields(tmp->get_left_son());
    delete_all_data_fields(tmp->get_right_son());

}
