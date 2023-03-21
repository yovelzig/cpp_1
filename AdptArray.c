#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"
// נעזרתי בקוד של פתרון השאלה ממועד א של תכנות מערכות 1
typedef struct AdptArray_
{
    int size;
    PElement *pElemArr;
    DEL_FUNC delF;
    COPY_FUNC copyF;
    PRINT_FUNC printF_;
} AdptArray_, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyF_, DEL_FUNC delF_, PRINT_FUNC printF_)
{
    PAdptArray p = (PAdptArray)malloc(sizeof(AdptArray_));
    if (p == NULL)
    {
        printf("error in allocate memory");
        return NULL;
    }
    p->size = 0;
    p->pElemArr = (PElement *)calloc(1, sizeof(PElement));
    if (p->pElemArr == NULL)
    {
         printf("error in allocate memory");
        return NULL;
    }
     
    p->delF = delF_;
    p->printF_ = printF_;
    p->copyF = copyF_;

    return p;
}

Result SetAdptArrayAt(PAdptArray p, int index, PElement NewElem)
{
    if (p == NULL)
    {
        printf("empty arr");
        return FAIL;
    }
    else
    {
        PElement *newArr;
        if (p->size <= index)
        {
            newArr = (PElement *)calloc((index + 1), (sizeof(PElement)));
            if (newArr == NULL)
            {
                printf("error in allocate memory");
                return FAIL;
            }
            else
            {
                memcpy(newArr, p->pElemArr, (p->size) * sizeof(PElement));
                free(p->pElemArr);
                p->pElemArr = newArr;
                p->pElemArr[index] = p->copyF(NewElem);
                p->size = index + 1;
                return SUCCESS;
            }
        }
        else
        {
            if (p->pElemArr[index]!= NULL)
            {                       
            p->delF(p->pElemArr[index]);
            free(p->pElemArr[index]);
            p->pElemArr[index] = p->copyF(NewElem);
            }
        }
        return SUCCESS;
    }
}
void DeleteAdptArray(PAdptArray p)
{
    if (p == NULL)
    {
        return;
    }
    for (int i = 0; i < p->size; i++)
    {
        if (p->pElemArr[i] != NULL)
        {
            p->delF(p->pElemArr[i]);
        }
    }
    free(p->pElemArr);
    free(p);
}
PElement GetAdptArrayAt(PAdptArray p, int index)
{
    if (p == NULL)
    {
        printf("empty arr");
        return NULL;
    }
    PElement curr = p->pElemArr[index];
    if (curr != NULL)
    {
        PElement copy = p->copyF(curr);
        return copy;
    }
    else
    return NULL;
}
int GetAdptArraySize(PAdptArray p)
{
    if (p == NULL)
    {
        printf("empty arr");
        return -1;
    }
    int currS = p->size;
    return currS;
}
void PrintDB(PAdptArray p)
{
    if (p == NULL)
    {
        printf("error");
        return;
    }
    if (p->pElemArr == NULL)
    {
        printf("error");
        return;
    }
    for (int i = 0; i < p->size; i++)
    {
        if (p->pElemArr[i] != NULL)
        {
            p->printF_(p->pElemArr[i]);
        }
    }
}
