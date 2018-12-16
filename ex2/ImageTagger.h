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

    /*  Image Constructor
   *  Input:    imageID and number of max segments possible for this image
   *  Output:   return pointer to a new Image
   */
    Image(const int imageID,const int segments);

    /*
    * Image Destructor
   */
    ~Image();

    /*  add_label_to_image:
     *  Description:  add given label to a given segment for this image, if the
     *                segment already labeled - does nothing
     *  Input:        segmentID - number of the segment to modify
     *                label - the new value for the given segment
     *  Output:       return FALSE if the segment already labeled (nothing happened),
     *                else modify the segment and return TRUE
   */
    bool add_label_to_image(const int segmentID, const int label);

    /*  delete_label_from_image:
     *  Description:  delete given label from a given segment for this image, if the
     *                segment does not labeled - does nothing
     *  Input:        segmentID - number of the segment to modify
     *  Output:       return FALSE if the segment does not labeled (nothing happened),
     *                else delete the label and return TRUE
   */
    bool delete_label_from_image(const int segmentID);

    /*  get_label_from_image:
     *  Description:  returns the label of the given segment for this image
     *  Input:        segmentID - number of the segment to modify
     *  Output:       return the label of the segment, if the segment is unlabeled return EMPTY_SEG(=-1)
     */
    const int get_label_from_image(const int segmentID);

    /*  get_all_unlabeledSegments:
     *  Description:  receives pointer to integer array and updates it with keys of all unlabeled segments
     *  Input:        segment - pointer to an integer array
     *  Output:       array of all unlabeled segments (O(s) - s=number of unlabeled segments
     */
    void get_all_unlabeledSegments(int *segments);

    /*  num_of_unlabeledSegments:
     *  Description:  return the number of unlabeled segments
     *  Input:        none.
     *  Output:       number of unlabeled segments
     */
    int num_of_unlabeledSegments();

    /*  label_exist:
     *  Description:  checks if the given label exist in this image
     *  Input:        label - the label to search for
     *  Output:       TRUE - if the label exist, else FALSE
     */
    bool label_exist(int label);

    /*  get_segments_array:
     *  Description:  return pointer for the beginning of the segments array
     *  Input:        none.
     *  Output:       return pointer for the beginning of the segments array
    */
    const int* get_segments_array();

    /*  count_num_labels_in_image:
     *  Description:  counts the number of appearances of the label in this image
     *  Input:        label - the label to search for
     *  Output:       return the number of appearances
     */
    int count_num_labels_in_image(int label);

    /*  get_unlabel_list:
    *  Description:   return pointer for the first node of the unlabeled segments list
    *  Input:         none.
    *  Output:        return pointer for the first node of the unlabeled segments list
    */
    ListNode<int,int>* get_unlabel_list();
    };



class ImageTagger {
    Map_tree<int,Image*>* images;
    int max_segments;

public:

    /*  ImageTagger Constructor:
    *  Input:   number of max segments possible for the inside images
    *  Output:  return pointer to a new ImageTagger
    */
    ImageTagger(int segments);

    /*
    * Image Destructor
   */
    ~ImageTagger();

    /*  get_segments:
    *  Description: return the max segments of this ImaggeTagger
    *  Input:       none.
    *  Output:      return the max segments
    */
    int get_segments();

    /*  get_image:
    *  Description: finding the image with the given image ID
    *  Input:       imageID - the ID of the image to find
    *  Output:      return pointer to the correct image, if the image does not
    *               exist - return nullptr.
    */
    Image* get_image(int imageID);

    /*  image_exist:
    *  Description: return if the given image ID exist in the ImageTagger or not
    *  Input:       imageID - the ID of the image to find
    *  Output:      return TRUE if the image exist, else FALSE
    */
    bool image_exist(int imageID);

    /*  add_image:
    *  Description: adding a new image to the struct, only if an image with the
    *               same ID does not exist
    *  Input:       imageID - the ID of the image to add
    *  Output:      return TRUE if the image does not exist and the new one was added,
    *               else, the image already exist and return FALSE
    */
    bool add_image(int imageID);

    /*  delete_image:
    *  Description: Deleting an image from the struct, only if an image with the
    *               same ID exist
    *  Input:       imageID - the ID of the image to delete
    *  Output:      return TRUE if the image exist and the delete completed,
    *               else, the image does not exist and return FALSE
    */
    bool delete_image(int imageID);

    /*  count_labels:
    *  Description: counting the sum of appearances of the given label in
    *               this ImageTagger
    *  Input:       label - the label to find and count
    *  Output:      return the sum of the appearances of the label
    */
    int count_labels(int label);

    /*  count_label_recurse:
    *  Description: recursive function, used by "count_labels"
    *  Input:       current - the current TreeNode to check (recursively)
     *              sum - global counter of appearances
     *              label - the label to find and count
    *  Output:      none.
    */
    void count_label_recurse(TreeNode<int,Image*>* current, int* sum, int label);

    /*  initial_segments_arrays:
    *  Description: initializing the images and segments array, according to "GetAllSegmentsByLabel"
    *  Input:       current - the current TreeNode to check (recursively)
    *               label - the label to find and count
    *               index - index of the last int in the arrays
    *  Output:      images - A pointer to an array which will hold the IDs of the images containing segments tagged with label. Note that you need to allocate the array inside the function.
    *               segments - A pointer to an array which will hold the segments of the images containing segments tagged with label. Note that you need to allocate the array inside the function.
    *
    */
    void initial_segments_arrays(TreeNode<int,Image*>* current, int label,
                                 int *index, int **images, int **segments);

    /*  get_root:
    *  Description: return pointer to the root of the ImageTagger
    *  Input:       none.
    *  Output:      return pointer to the root of the ImageTagger
    */
    TreeNode<int,Image*>* get_root();

    /*  delete_all_data_fields:
    *  Description: scanning the ImageTagger struct and deleting all the "Data" fields
    *               of each node.
    *  Input:       tmp - the current TreeNode to check (recursively)
    *  Output:      none.
    */
    void delete_all_data_fields(TreeNode<int,Image*>* tmp);
};


#endif //EX2_IMAGETAGGER_H
