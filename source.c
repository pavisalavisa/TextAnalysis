/*Napisati program koji cita iz teksta rijec po rijec
i radi rijecnik svih rijeci koje se nelaze u tekstu
Rijecnik se izraduje na nacin da se u vezanu listu zapisuje smao prvo slovo
zatim se ta rijec sprema u binarno stablo na koje pokazuje pokazivac koji se nalazi u cvoru
vezane liste
Slova u vezanoj listi moraju biti sortirana
Ispisati sve rijeci abecednim redosljedom
a) Ukoliko ide nova rijec u stablo poveca se brojac u cvoru vezane liste
b)ukoliko se ric ponavlja povecamo brojac
c) Ispisati razl rijeci abecedno s brojem ponavljanja
d) ispisati koliko rijeci pocinju s pocetnim slovom koje je u listi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _listNode;
typedef struct _listNode* Position;
struct _treeNode;
typedef struct _treeNode* treePosition;

typedef struct _listNode{
    char firstLetter;
    int wordsCounter;
    Position next;
    treePosition root;
}_LISTNODE;

typedef struct _treeNode{
    char word [64];
    int wordCounter;
    treePosition left;
    treePosition right;
}_TREENODE;

Position createListNode();
Position createTreeNode();
int readFromFile(char*,Position*);
int sortedInsert(Position,char*);
int insertAt(Position ,char*);
int addWordToTree(Position ,char*);
treePosition binaryTreeInsert(treePosition,char*);
int startProgram();
int printRijecnik(Position);
int printTree(treePosition root);

int main(int argc,char** argv){
    startProgram();
    return 0;
}

int startProgram(){
    Position list=createListNode();
    readFromFile("ulaz.txt",&list);
    printRijecnik(list);
    return 0;
}

int printRijecnik(Position list){
    if(list==NULL){
        printf("NULL pointer exception!\n");
        return -1;
    }
    Position iter=list;
    while(iter->next!=NULL){
        printf("%c, broj rijeci:%d\n\n",iter->next->firstLetter,iter->next->wordsCounter);
        printTree(iter->next->root);
        iter=iter->next;
    }
    return 0;
}

int printTree(treePosition root){
    if(root==NULL){
        return 0;
    }
    printTree(root->left);
    printf("\t %s broj ponavljanja--- %d\n",root->word,root->wordCounter);
    printTree(root->right);

    return 0;
}

Position createListNode(){
    Position p=(Position)malloc(sizeof(_LISTNODE));
    if(p==NULL){
        printf("Error allocating memory\n");
        return NULL;
    }
    p->firstLetter='\0';
    p->wordsCounter=0;
    p->next=NULL;
    p->root=NULL;
    return p;
}
Position createTreeNode(){
    treePosition p=(treePosition)malloc(sizeof(_TREENODE));
    if(p==NULL){
        printf("Error allocating memory!\n");
        return NULL;
    }
    memset(p->word,0,64);
    p->left=NULL;
    p->right=NULL;
    p->wordCounter=0;
    return p;
}
int readFromFile(char* fName,Position* list){
    if(fName==NULL){
        printf("Invalid file name!\n");
        return -1;
    }
    if(list==NULL){
        printf("NULL pointer exception!\n");
        return -2;
    }

    FILE* fp=fopen(fName,"r");
    if(fp==NULL){
        printf("Error reading file!\n");
        return -3;
    }
    char buffer[64];
    Position iter=NULL;
    while(!feof(fp)){
        iter=*list;
        fscanf(fp," %s",buffer);
        sortedInsert(*list,buffer);
    }
    fclose(fp);
}
int sortedInsert(Position list,char* buff){
    if(list==NULL||buff==NULL){
        printf("NULL pointer exception!\n");
        return -1;
    }
    Position iter=list;
    while(iter->next!=NULL && iter->next->firstLetter < buff[0]){
        iter=iter->next;
    }
    insertAt(iter,buff);
    addWordToTree(iter->next,buff);
    return 0;
}

int insertAt(Position node,char*buff){
    if(node==NULL){
        printf("NULL pointer exception!\n");
        return -1;
    }
    if(node->next!=NULL &&node->next->firstLetter==buff[0]){
        node->wordsCounter++;
        return 0;
    }
    Position tmp=createListNode();
    tmp->firstLetter=buff[0];
    tmp->next=node->next;
    node->next=tmp;
    tmp->wordsCounter++;
    return 0;
}

int addWordToTree(Position node,char* buffer){
    if(node==NULL||buffer==NULL){
        printf("Null pointer exception!\n");
        return -1;
    }
    node->root=binaryTreeInsert(node->root,buffer);
    return 0;
}

treePosition binaryTreeInsert(treePosition root,char* buffer){
    if(root==NULL){
        treePosition tmp=createTreeNode();
        strcpy(tmp->word,buffer);
        tmp->wordCounter++;
        return tmp;
    }
    if(strcmp(root->word,buffer)==0){
        root->wordCounter++;
    }
    else if(strcmp(root->word,buffer)<0){
        root->right=binaryTreeInsert(root->right,buffer);
    }
    else{
        root->left=binaryTreeInsert(root->left,buffer);
    }
    return root;
}
