#include "list.h"

//创建链表头
Node* createList(){
    Node* List = (Node*)malloc(sizeof(Node));
    List->pNext=NULL;
    return List;
}

//创建节点
Node* createNode(User data){
    Node* pNew = (Node*)malloc(SIZE);
    if(NULL == pNew){
        printf("createNode函数中申请内存失败:%m\n");
        return NULL;
    }
    memset(pNew,0,SIZE);
    strcpy(pNew->data.userId,data.userId);
    strcpy(pNew->data.passWord,data.passWord);
    pNew->data.money = data.money;
    return pNew;
};
//尾插法并赋值
void tail_insert(Node* List,User data){
    if (NULL == List->pNext){
        List->pNext=createNode(data);
    }else{
        Node* newTail = List->pNext; //假设第一个节点是尾节点
        while (newTail->pNext) newTail=newTail->pNext;
        newTail->pNext=createNode(data);
    }
}



//打印链表内容
void showAll(Node* List){
    Node* pMove=List->pNext;
    printf("账户名称:    账户密码:    账户金额:\n");
    while (pMove)
    {
        printf("%s\t%s\t%lf\n",pMove->data.userId,pMove->data.passWord,pMove->data.money);
        pMove=pMove->pNext;
    }
    printf("\n");
}

void removeList(Node* list){
    Node * p = list;
    if (p->pNext){
        removeList(p->pNext);
        free(p->pNext);
    }else return;
    p->pNext = NULL;
}
