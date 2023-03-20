#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AdptArray_ {
    PElement *pElement;
    int size;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (!pArr) {
        exit(EXIT_FAILURE);
    }
    pArr->pElement = NULL;
    pArr->size = 0;
    pArr->copyFunc = copyFunc;
    pArr->delFunc = delFunc;
    pArr->printFunc = printFunc;
    return pArr;
}

void DeleteAdptArray(PAdptArray pArr) {
    if (!pArr) {
        return;
    }
    for (int i = 0; i < pArr->size; ++i) {
        if (pArr->pElement[i]) {
            pArr->delFunc(pArr->pElement[i]);
            pArr->pElement[i] = NULL;
        }
    }
    free(pArr->pElement);
    pArr->pElement = NULL;
    free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem) {
    if (!pArr) {
        return FAIL;
    }
    if (idx >= pArr->size) {
        PElement *newpElemArr = (PElement *) calloc(idx + 1, sizeof(PElement));
        if (!newpElemArr) {
            return FAIL;
        }
        memcpy(newpElemArr, pArr->pElement, pArr->size * sizeof(PElement));
        free(pArr->pElement);
        pArr->pElement = newpElemArr;
        pArr->size = idx + 1;
    }
    if (pArr->pElement[idx]) {
        pArr->delFunc(pArr->pElement[idx]);
    }
    pArr->pElement[idx] = pArr->copyFunc(pNewElem);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pArr, int index) {
    if (!pArr || !pArr->pElement[index]) {
        return NULL;
    }
    return pArr->copyFunc(pArr->pElement[index]);
}

int GetAdptArraySize(PAdptArray pArr) {
    return pArr ? pArr->size : -1;
}

void PrintDB(PAdptArray pArr) {
    if (!pArr) {
        return;
    }
    for (int i = 0; i < pArr->size; ++i) {
        if (pArr->pElement[i]) {
            pArr->printFunc(pArr->pElement[i]);
        }
    }
}
