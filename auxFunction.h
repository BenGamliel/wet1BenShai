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
           int size1, int size2, int * maxId, int * maxAmount, int * size) {
    Lecture **t1Player = new Lecture*[size1];
    Lecture **t2Player = new Lecture*[size2];
    t1->inOrderToArray(t1Player);
    t2->inOrderToArray(t2Player);
    Lecture **mergedArr= new Lecture*[size1 + size2];
    Lecture_Key *mergedKeys =new Lecture_Key[size1 + size2];
    int i = 0, j = 0, k = 0;
    int noChallenges = 0;
    Lecture_Key key1;
    Lecture_Key key2;
    while (i < size1 && j < size2) {
        key1 =  Lecture_Key(t1Player[i]->getHour(),
                           t1Player[i]->getRoom());
        key2 =  Lecture_Key(t2Player[j]->getHour(),
                           t2Player[j]->getRoom());
        compareLectures cmp;
        if (cmp(key1, key2)) {
            mergedArr[k] = t1Player[i];
            mergedKeys[k] = key1;
            if (t1Player[i]->getChallenges() == 0)
                noChallenges++;
            i++;
        } else {
            mergedArr[k] = t2Player[j];
            mergedKeys[k] = key2;
            if (t2Player[j]->getChallenges() == 0)
                noChallenges++;
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < size1) {
        mergedArr[k] = t1Player[i];
        key1 =  Lecture_Key(t1Player[i]->getCoins(),
                           t1Player[i]->getId());
        mergedKeys[k] = key1;
        if (t1Player[i]->getChallenges() == 0)
            noChallenges++;
        i++;
        k++;
    }

    // If there are more elements in second array
    while (j < size2) {
        mergedArr[k] = t2Player[j];
        key2 =  Lecture_Key(t2Player[j]->getCoins(),
                           t2Player[j]->getId());
        mergedKeys[k] = key2;
        if (t2Player[j]->getChallenges() == 0)
            noChallenges++;
        j++;
        k++;
    }
    int newSize = size1 + size2 - noChallenges;
    Lecture **filteredArr = new Lecture*[newSize];
    Lecture_Key *filteredKeys = new Lecture_Key[newSize];
    int y = 0;
    for (int x = 0; x < size1 + size2; x++) {
        if (mergedArr[x]->getChallenges() != 0) {
            if (mergedArr[x]->getChallenges() > *maxAmount){
                *maxAmount =  mergedArr[x]->getChallenges();
                *maxId = mergedArr[x]->getId();
            }else if(mergedArr[x]->getChallenges() == *maxAmount){
                if (mergedArr[x]->getId() < *maxId)
                    *maxId = mergedArr[x]->getId();
            }
            filteredArr[y] = mergedArr[x];
            filteredKeys[y] = mergedKeys[x];
            y++;
        }
    }
    AVLTree<Lecture *, Lecture_Key , compareLectures> *newTree = new AVLTree<Lecture *, Lecture_Key , compareLectures>(
            filteredArr, &filteredKeys, newSize);
    *size = newSize;
    delete[] filteredArr;
    delete[] filteredKeys;
    delete[] mergedArr;
    delete[] mergedKeys;
    delete[] t1Player;
    delete[] t2Player;
    return newTree;
}




#endif //PP_AUXFUNCTION_H
