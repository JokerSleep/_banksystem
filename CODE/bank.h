#ifndef  _BANK_H_
#define  _BANK_H_

#include "res.h"
#include "list.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//初始化数据
void init_data(Node* List);
//初始化界面
void init_menu(Node* List);
//用户菜单
void user_menu(Node** List,Node* list);
//登录
Node* denglu(Node* List);
//查看余额
void showMoney(Node* list);
//存款
void addMoney(Node** List,Node** list);
//取款
void takeMoney(Node** List,Node** list);
//转账
void sendMoney(Node** List,Node** list);

//注册用户
void addUser();
//判断用户是否已存在
bool cheakName(Node* List,char* name);
//管理的可执行操作
void managerOption(Node** List);
void changeUser(Node** List); 
void delUser(Node** List);  

#endif