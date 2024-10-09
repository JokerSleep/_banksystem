#pragma once
#include "list.h"

#define FILENAME "user_information.txt"

//把链表中的数据写入文件中
void SaveUser(Node**  List);
//读取文件里的数据并写入链表
void ReadUser(Node** List);
