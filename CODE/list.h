#pragma once
#include "res.h"

//链表节点类型
typedef struct node{
    User          data;
    struct node*  pNext;
}Node;
//链表节点大小
#define SIZE sizeof(Node)

//创建链表头
Node* createList();
//创建节点
Node* createNode(User data);
//数据插入 尾插
void tail_insert(Node* List,User data);
//读取链表里面所有信息
void showAll(Node* List);
//删除链表
void removeList(Node* list);
