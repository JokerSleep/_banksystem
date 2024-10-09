#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>

#define NAME_LEN 20
#define PASSWORD_LEN 20

//定义用户结构体
typedef struct user
{
    char    userId[NAME_LEN];
    char    passWord[PASSWORD_LEN];
    double  money;
}User;
//结构体大小
#define SIZE_USER sizeof(User)
