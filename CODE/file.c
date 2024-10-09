#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//把链表中的数据写入文件中
void SaveUser(Node** List){
    FILE* fSave = fopen(FILENAME,"w");
    if(NULL == fSave){
		printf("文件打开失败\n");
        return;
	}

    Node* pTemp = (*List)->pNext;
    while(pTemp)
    {
        fwrite(pTemp->data.userId,1,sizeof(pTemp->data.userId),fSave);
        fwrite(pTemp->data.passWord,1,sizeof(pTemp->data.passWord),fSave);
        fwrite(&(pTemp->data.money),1,sizeof(pTemp->data.money),fSave);
        pTemp = pTemp->pNext;
    }

    fclose(fSave);
}

//读取文件里的数据写入链表
void ReadUser(Node** List){
    FILE* fp = fopen(FILENAME,"r");
    if(NULL == fp){
		printf("文件打开失败\n");
        return;
	}
    //先清空链表
    removeList(*List);
    //将文件指针移向末尾
    fseek(fp,0,SEEK_END);
    //计算文件长度
    int fileLen=ftell(fp);
    //将文件指针移向头
    fseek(fp,0,SEEK_SET);
    User uTemp;
   
    for (int i = 0; i < (fileLen/SIZE_USER); i++){
        fread(uTemp.userId,1,sizeof(uTemp.userId),fp);
        fread(uTemp.passWord,1,sizeof(uTemp.passWord),fp);
        fread(&(uTemp.money),1,sizeof(uTemp.money),fp);
        //将数据写入链表
        tail_insert((*List),uTemp);
    }
    
    fclose(fp);
}
