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
    bool add_label_to_image(const int segmentID, const int label);
    const int get_label_from_image(const int segmentID);
    bool delete_label_from_image(const int segmentID);
    void get_all_unlabeledSegments(int *segments);
    int num_of_unlabeledSegments();
    bool label_exist(int label);
    const int* get_segments_array();
    int count_num_labels_in_image(int label);
    ListNode<int,int>* get_unlabel_list();
    };

class ImageTagger {
    Map_tree<int,Image*>* images;
    int max_segments;

public:
    ImageTagger(int segments);
    ~ImageTagger();
    int get_segments();
    Image* get_image(int imageID);
    bool image_exist(int imageID);
    bool add_image(int imageID);
    bool delete_image(int imageID);
    int count_labels(int label);
    void count_label_recurse(TreeNode<int,Image*>* current, int* sum, int label);
    void initial_segments_arrays(TreeNode<int,Image*>* current, int label, int *index,
                                 int **images, int **segments);

    TreeNode<int,Image*>* get_root();
    void delete_all_data_fields(TreeNode<int,Image*>* tmp);
};


#endif //EX2_IMAGETAGGER_H
