#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct node_s {
  int val;
  struct node_s * next;
} node_t ;
node_t* nodeInit(int val) {
  node_t* node=malloc(sizeof(node_t));
  node->val=val;
  node->next=NULL;
  return(node);
}
void nodeDel(node_t* node) {
  free(node);
}
node_t* nodeGetNext(node_t* node) {
  return(node->next);
}
void nodeSetNext(node_t* node, node_t* nxt) {
  node->next=nxt;
}
int nodeGetVal(node_t* node) {
  return(node->val);
}
void nodeSetVal(node_t* node, int val) {
  node->val=val;
}
int nodeIsLast(node_t* node) {
  return(((node->next)==NULL)? 1 : 0);
}

//////////////////////////////////////////////////////////////////////////////////////////
typedef struct linkedList_s {
  node_t* head;
} linkedList_t;
linkedList_t* linkedListInit() {
  linkedList_t* myLL=malloc(sizeof(linkedList_t));
  myLL->head=NULL;
  return(myLL);
}
void linkedListDel(linkedList_t* myLL) {
  node_t** revNode=(node_t**)malloc(0);
  int i=0;
  for(node_t* ptr=myLL->head;ptr!=NULL;ptr=ptr->next) {
    i++;
    revNode=(node_t**)realloc(revNode,(i*sizeof(node_t*)));
    *(revNode+i-1)=ptr;
    printf(">Discovered node ptr=%p\n",ptr);
  }
  for(int j=0;j<i;j++) {
    printf(">Deleted node ptr=%p\n",*(revNode+j));
    free(*(revNode+j));
  }
  free(revNode);
  free(myLL);
}
int linkedListEmpty(linkedList_t* myLL) {
  return((myLL->head==NULL)? 1 : 0);
}
node_t* linkedListGethead(linkedList_t* myLL) {
  return(myLL->head);
}
node_t* linkedListGettail(linkedList_t* myLL) {
  node_t* tail;
  for(node_t* ptr=myLL->head;ptr!=NULL;ptr=ptr->next) {
    tail=ptr;
  }
  return(tail);
}
void linkedListInsert(linkedList_t* myLL, node_t* myN) {
  if(linkedListEmpty(myLL)) {
    myLL->head=myN;
  } else {
    linkedListGettail(myLL)->next=myN;
  }
}
node_t* linkedListGetNxt(linkedList_t* myLL,node_t* myN) {
  node_t* nxt=NULL;
  for(node_t* ptr=myLL->head;ptr!=NULL;ptr=ptr->next) {
    if(ptr==myN) {
      nxt=myN->next; break;
    }
  }
  return(nxt);
}
node_t* linkedListGetPrev(linkedList_t* myLL,node_t* myN) {
  for(node_t* ptr=myLL->head;ptr!=NULL;ptr=ptr->next) {
    if(ptr->next==myN) {
      return(ptr);
    }
  }
  return(NULL);
}
node_t* linkedListPop(linkedList_t* myLL) {
  if(linkedListEmpty(myLL)) {
    return(NULL);
  } else {
    node_t* tail=linkedListGettail(myLL);
    linkedListGetPrev(myLL,tail)->next=NULL;
    return(tail);
  }
}
void linkedListPrint(linkedList_t* myLL) {
  printf("LinkedList:");
  for(node_t* ptr=myLL->head;ptr!=NULL;ptr=ptr->next) {
    printf("%d>",nodeGetVal(ptr));
  }
  printf("\n");
}
//////////////////////////////////////////////////////////////////////////////////////////
void nodeListMerge(node_t** nodeList,int l, int m, int r) {
  node_t** inNodeList=(node_t**)malloc((1+r-l)*sizeof(node_t*));
  int offset=l;
  for(int i=l;i<=r;i++) {
    *(inNodeList+i-offset)=*(nodeList+i);
  }
  int lPtr=0; //goes upto m-offset
  int rPtr=m-offset+1; //goes upto r-offset
  int outPtr=l;
  while((lPtr<=m-offset)&&(rPtr<=r-offset)) {
    if(((*(inNodeList+lPtr))->val)<((*(inNodeList+rPtr))->val)) {
      *(nodeList+outPtr)=(*(inNodeList+lPtr));
      lPtr+=1;
    } else {
      *(nodeList+outPtr)=(*(inNodeList+rPtr));
      rPtr+=1;
    }
    outPtr+=1;
  }
  while(lPtr<=m-offset) {
    *(nodeList+outPtr)=(*(inNodeList+lPtr));
    lPtr+=1;
    outPtr+=1;
  }
  while(rPtr<=r-offset) {
    *(nodeList+outPtr)=(*(inNodeList+rPtr));
    rPtr+=1;
    outPtr+=1;
  }
  free(inNodeList);
}

void nodeListMergeSort(node_t** nodeList,int l, int r) {
  if (r==l) {return;}
  int m=l+((r-l)/2);
  if(l!=m) {
    nodeListMergeSort(nodeList,l,m);
  }
  if(r!=(m+1)) {
    nodeListMergeSort(nodeList,m+1,r);
  }
  nodeListMerge(nodeList,l,m,r);
}

void linkedListMergeSort(linkedList_t* inLL) {
  node_t* ptr=inLL->head;
  node_t** nodeList=NULL;
  int numNode=0;
  while(ptr!=NULL) {
    nodeList=(node_t**)realloc(nodeList,(1+numNode)*sizeof(node_t*));
    *(nodeList+numNode)=ptr;
    ptr=ptr->next;
    numNode+=1;
  }
  /*for(int i=0;i<numNode;i++) {
    printf("UTK>>>%p:%d\n",*(nodeList+i),(*(nodeList+i))->val);
  }*/
  nodeListMergeSort(nodeList,0,numNode-1);
  inLL->head=*(nodeList);
  int i=0;
  while(i<(numNode-1)) {
    (*(nodeList+i))->next=*(nodeList+i+1);
    i+=1;
  }
  (*(nodeList+i))->next=NULL;
  free(nodeList);
}

//////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
  linkedList_t* myLL=linkedListInit();
  printf("UTK>>> Insert numbers>>>");
  for(int i=0;i<(15);i++) {
    int r=rand()%10;
    printf("%d ",r);
    node_t* myN=nodeInit(r);
    linkedListInsert(myLL,myN);
  }
  printf("\n");
  linkedListPrint(myLL);
  node_t* myN=linkedListPop(myLL);
  printf("Popped value=%d\n",myN->val);
  nodeDel(myN);
  linkedListPrint(myLL);
  printf("Merge sorting linked-list\n");
  linkedListMergeSort(myLL);
  printf("Deleting linked-list\n");
  linkedListPrint(myLL);
  linkedListDel(myLL);
  return(0);
}