//
// Created by ronien on 05/12/2018.
//

#define EMPTY_SEG -1
#include "library2.h"
#include "ImageTagger.h"

void *Init(int segments){
    if(segments<=0)
        return NULL;

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
        if(!((ImageTagger*)DS)->add_image(imageID))
            return FAILURE;
    }catch (std::exception& e){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType DeleteImage(void *DS, int imageID){
    if(DS== nullptr || imageID<=0)
        return INVALID_INPUT;

    if(!((ImageTagger*)DS)->delete_image(imageID))
        return FAILURE;                     //image does not exist

    return SUCCESS;

}
StatusType AddLabel(void *DS, int imageID, int segmentID, int label){
    if(DS == nullptr || imageID<=0 || segmentID<0 ||
            segmentID>=((ImageTagger*)DS)->get_segments() || label<=0)
        return INVALID_INPUT;

    Image *image_to_update=((ImageTagger*)DS)->get_image(imageID);

    if(image_to_update== nullptr)
        return FAILURE;         //the image with imageID does not exist in tree

    if(!image_to_update->add_label_to_image(segmentID,label))
        return FAILURE;         //there is already a label in the segmentID of the image

    return SUCCESS;
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label){
    if(DS == nullptr || imageID<=0 || segmentID<0 ||
       segmentID>=((ImageTagger*)DS)->get_segments() || label==NULL)
        return INVALID_INPUT;

    Image *image_to_update=((ImageTagger*)DS)->get_image(imageID);

    if(image_to_update== nullptr)
        return FAILURE;         //the image with imageID does not exist in tree

    int segment_label=image_to_update->get_label_from_image(segmentID);

    if(segment_label==EMPTY_SEG)
        return FAILURE;         //there is no label in the segmentID

    *label=segment_label;
    return SUCCESS;

}

StatusType DeleteLabel(void *DS, int imageID, int segmentID){
    if(DS == nullptr || imageID<=0 || segmentID<0 ||
       segmentID>=((ImageTagger*)DS)->get_segments())
        return INVALID_INPUT;

    Image *image_to_update=((ImageTagger*)DS)->get_image(imageID);

    if(image_to_update== nullptr)
        return FAILURE;         //the image with imageID does not exist in tree

    if(!image_to_update->delete_label_from_image(segmentID))
        return FAILURE;         //there is no label for the image in segmentID

    return SUCCESS;
}

StatusType GetAllUnLabeledSegments(void *DS, int imageID, int **segments,
                                   int *numOfSegments){
    if(DS == nullptr || imageID<=0 || segments == nullptr ||
            numOfSegments == nullptr)
        return INVALID_INPUT;

    Image *image_to_update=((ImageTagger*)DS)->get_image(imageID);

    if(image_to_update== nullptr)
        return FAILURE;         //the image with imageID does not exist in tree

    *numOfSegments=image_to_update->num_of_unlabeledSegments();
    if(*numOfSegments==0) {
        *segments = nullptr;
        return FAILURE;         //there is no segment without label
    }
    *segments=(int*)malloc((sizeof(int))*(*numOfSegments));
    if(*segments == nullptr){
//        free(*segments);
        return ALLOCATION_ERROR;
    }
//    image_to_update->get_all_unlabeledSegments(*segments);

    ListNode<int,int>* node_ptr=image_to_update->get_unlabel_list();
    for (int i = 0; i <*numOfSegments ; i++) {
        *((*segments)+i) = node_ptr->get_key();
        node_ptr=node_ptr->get_next();
    }

    return SUCCESS;
}

StatusType GetAllSegmentsByLabel(void *DS, int label, int **images,
                                 int **segments, int *numOfSegments){
    if(DS == nullptr||images == nullptr|| segments == nullptr ||
            numOfSegments == nullptr || label <= 0)
        return INVALID_INPUT;

    *numOfSegments=((ImageTagger*)DS)->count_labels(label);

    if(*numOfSegments==0){
        *images=NULL;
        *segments=NULL;
        return SUCCESS;
    }

    *images=(int*)(malloc(*numOfSegments*sizeof(int)));
    if(*images == nullptr)
        return ALLOCATION_ERROR;
    *segments=(int*)(malloc(*numOfSegments*sizeof(int)));
    if(*segments == nullptr){
        free(*images);
        return ALLOCATION_ERROR;
    }
    int index=0;
    TreeNode<int,Image*>* tmp =((ImageTagger*)DS)->get_root();
    ((ImageTagger*)DS)->initial_segments_arrays(tmp,label,&index,images,segments);

    return SUCCESS;
}

void Quit(void** DS){
    if(DS== nullptr || *DS==nullptr)
        return;

    ((ImageTagger*)*DS)->delete_all_data_fields(((ImageTagger*)*DS)->get_root());
    delete ((ImageTagger*)*DS);
    *DS=NULL;
}