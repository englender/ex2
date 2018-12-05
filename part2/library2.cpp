//
// Created by ronien on 05/12/2018.
//

#define EMPTY_SEG -1
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
//StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
//    if(DS == nullptr || imageID<=0 || segmentID<0 ||
//            segmentID>=((ImageTagger*)DS)->get_segments() || label<=0)
//        return INVALID_INPUT;
//
//    if(!((ImageTagger*)DS)->image_exist(imageID))
//        return FAILURE;         //the image with imageID does not exist in tree
//
//    Image *image_to_update=((ImageTagger*)DS)->images->find(imageID);
//
//    if(!image_to_update->AddLabelToImage(segmentID,label))
//        return FAILURE;         //there is already a label in the segmentID of the image
//
//    return SUCCESS;
//}
//
//StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
//    if(DS == nullptr || imageID<=0 || segmentID<0 ||
//       segmentID>=((ImageTagger*)DS)->get_segments() || label==NULL)
//        return INVALID_INPUT;
//
//    if(!((ImageTagger*)DS)->image_exist(imageID))
//        return FAILURE;         //the image with imageID does not exist in tree
//
//    int segment_label=((ImageTagger*)DS)->get_label(imageID,segmentID);
//    if(segment_label==EMPTY_SEG)
//        return FAILURE;
//
//}