//
// Created by dell on 12/05/2019.
//

#ifndef PP_AUXFUNCTION_H
#define PP_AUXFUNCTION_H

#include "avlStruct.h"
#include "Lecture.h"

AVLTree<Lecture *, Lecture_Key , compareLectures> *
unionTrees(AVLTree<Lecture *, Lecture_Key , compareLectures> *t1,
           AVLTree<Lecture *, Lecture_Key , compareLectures> *t2,
           int size1, int size2) {
    Lecture **t1Lecture = new Lecture*[size1];
    Lecture **t2Lecture = new Lecture*[size2];
    t1->inOrderToArray(t1Lecture);
    t2->inOrderToArray(t2Lecture);
    Lecture **mergedArr= new Lecture*[size1 + size2];
    Lecture_Key *mergedKeys =new Lecture_Key[size1 + size2];
    int i = 0, j = 0, k = 0;
    Lecture_Key key1;
    Lecture_Key key2;
    while (i < size1 && j < size2) {
        key1 =  Lecture_Key(t1Lecture[i]->getHour(),
                           t1Lecture[i]->getRoom());
        key2 =  Lecture_Key(t2Lecture[j]->getHour(),
                           t2Lecture[j]->getRoom());
        compareLectures cmp;
        if (cmp.operator()(key1,key2)) {
            mergedArr[k] = t1Lecture[i];
            mergedKeys[k] = key1;
            i++;

        } else {
            mergedArr[k] = t2Lecture[j];
            mergedKeys[k] = key2;
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < size1) {
        mergedArr[k] = t1Lecture[i];
        key1 =  Lecture_Key(t1Lecture[i]->getHour(),
                           t1Lecture[i]->getRoom());
        mergedKeys[k] = key1;
        i++;
        k++;
    }

    // If there are more elements in second array
    while (j < size2) {
        mergedArr[k] = t2Lecture[j];
        key2 =  Lecture_Key(t2Lecture[j]->getHour(),
                           t2Lecture[j]->getRoom());
        mergedKeys[k] = key2;
        j++;
        k++;
    }
    AVLTree<Lecture *, Lecture_Key , compareLectures> *newTree = new AVLTree<Lecture *, Lecture_Key , compareLectures>(
            mergedArr, &mergedKeys, size1+size2);
    delete[] mergedArr;
    delete[] mergedKeys;
    delete[] t1Lecture;
    delete[] t2Lecture;
    return newTree;
}




#endif //PP_AUXFUNCTION_H
