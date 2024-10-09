#include "bank.h"

void init_data(Node* List){
    //将链表的数据写入到文件
    FILE* fp = fopen(FILENAME,"r");
    //将文件指针移向末尾
    fseek(fp,0,SEEK_END);
    //计算文件长度
    int fileLen=ftell(fp);
    //将文件指针移向头
    fseek(fp,0,SEEK_SET);
    if(fileLen <= 0){
        printf("数据初始化中...\n");
        //创建已存在的几个用户
        User u1,u2,u3;
        strcpy(u1.userId,"张三"),strcpy(u1.passWord,"333"),u1.money=300;
        strcpy(u2.userId,"李四"),strcpy(u2.passWord,"444"),u2.money=400;
        strcpy(u3.userId,"王五"),strcpy(u3.passWord,"555"),u3.money=500;
        tail_insert(List,u1);
        tail_insert(List,u2);
        tail_insert(List,u3);
        //将数据写入文件
        SaveUser(&List);
        sleep(1);
        printf("->数据初始化完成<-\n");
        if(NULL == fp){
            printf("->数据初始化失败<-\n");
            fclose(fp);
            return;
        }
        fclose(fp);
        return;
    }
    printf("->文件中已有数据,无需初始化<-\n");
    fclose(fp);
}

void init_menu(Node* List){
    printf("----欢迎使用银行系统----\n");
    while (1)
    {
        ReadUser(&List);
        printf(" 请选择要进行的操作：\n");
        printf(" 1 -> 普通用户登录\n");
        printf(" 2 -> 管理用户登录\n");
        printf(" 3 -> 用户注册\n");
        printf(" 4 -> 退出系统\n");
        int choose;
        scanf("%d",&choose);
        if(1 == choose){
            //用户登录系统
            Node* pUser = denglu(List);
            if (pUser){
                printf("登陆成功!正在进入系统...\n");
                sleep(1);
                user_menu(&List,pUser);
            }else{
                printf("->您输入的账户不存在或您输入的密码有误<-\n");
            }
        }else if (2 == choose){
            char admin[NAME_LEN];
            char adminPassWord[PASSWORD_LEN];
            char ADMIN[NAME_LEN]="ADMINER";
            char ROOTPASSWORD[PASSWORD_LEN]="4";
            printf("->开始验证管理员身份<-\n");
            printf("请输入管理员账号：\n");
            scanf("%s",admin);
            printf("请输入管理员密码：\n");
            scanf("%s",adminPassWord);
            printf("正在验证...\n");
            sleep(1);
            if (0 == strcmp(admin,ADMIN)){
                if (0 == strcmp(adminPassWord,ROOTPASSWORD)){
                    //管理用户登录系统
                    printf("->身份验证通过<-\n");
                    printf("正在进入管理系统...\n");
                    sleep(1);
                    managerOption(&List);
                }else{
                    printf("->身份验证未通过<-\n");
                    printf("\n");
                }
            }else{
                printf("->未授权的身份<-\n");
                printf("\n");
            }     
        }else if(3 == choose){
            addUser(&List);

        }else if(4== choose){
            printf("正在退出...\n");
            sleep(1);
            break;
        }
        else printf("->无效操作，请重试<-\n"),printf("\n");
    }
    printf("------感谢使用本银行系统------\n");
}

void user_menu(Node** List,Node* list){
    int choose;
    while (1)
    {   
        printf(" 请选择要使用的功能：\n");
        printf(" 1 -> 查看当前账户余额\n"); 
        printf(" 2 -> 存款\n");  
        printf(" 3 -> 取款\n");  
        printf(" 4 -> 转账\n");   
        printf(" 5 -> 退出当前账户\n");
        scanf("%d",&choose);
        switch (choose)
        {   
            case 1:    showMoney(list);            break;
            case 2:    addMoney(List,&list);       break;
            case 3:    takeMoney(List,&list);      break;
            case 4:    sendMoney(List,&list);      break; 
            case 5:    return;                     break;
            default:   printf("->无效操作<-\n");      break;
        }
    }
}
//登录
Node* denglu(Node* List){
    char userName[NAME_LEN];
    char userPassWord[PASSWORD_LEN];
    bool flag;
    printf("请输入您要登录的账户：\n");
    scanf("%s",userName);
    //判断用户是否存在
    flag = cheakName(List,userName);
    if (!flag) return NULL;

    printf("请输入您的账户密码：\n");
    scanf("%s",userPassWord);

    printf("正在核对账户信息，请耐心等待...\n");
    sleep(1);

    //查询是否存在该用户
    Node* pTemp = List->pNext;
    while (pTemp)
    {
        //找到了该用户名称
        if (0 == strcmp(pTemp->data.userId,userName))
        {
            //将用户名匹配的文件中的密码与输入的密码进行对比
            if (0 == strcmp(pTemp->data.passWord,userPassWord))
            {
                //返回该用户的节点
                return pTemp;
            }else{
                break;
            }
        }
        pTemp=pTemp->pNext;
    }
    return NULL;
}

void showMoney(Node* list){
    printf("您当前账户余额是：%g\n",list->data.money);
    sleep(1);
    printf("\n");
}
void addMoney(Node** List,Node** list){
    double cun;
    printf("请输入要存入的金额：\n");
    scanf("%lf",&cun);
    printf("正在存入...\n");
    //修改账户金额数据
    (*list)->data.money += cun;
    sleep(1);
    printf("->存入成功<-\n");
    //修改后的数据重新写入文件
    SaveUser(List);
    printf("\n");
}
void takeMoney(Node** List,Node** list){
    double qu;
    printf("请输入取出金额：\n");
    scanf("%lf",&qu);
    //判断余额是否足够
    if (qu <= (*list)->data.money)
    {   
        printf("正在取出...\n");
        (*list)->data.money -= qu;
        sleep(1);
        printf("->取出成功<-\n");
        //修改后的金额写入文件
        SaveUser(List);
    }else{
        printf("->取出失败,余额不足,请输入合理范围<-\n");
        sleep(1);
    }
    printf("\n");
}
//把开始的三个数据写入文件
void sendMoney(Node** List,Node** list){
    char toUser[NAME_LEN];
    double send;
    bool flag;
    printf("请输入要转入账户的名称：\n");
    scanf("%s",toUser);
    //增加条件判断
    //判断链表中是否已经存在该用户名
    flag = cheakName((*List),toUser);
    if (!flag){
        printf("->该账户不存在,无法转账<-\n");
        return;
    }
    printf("请输入要该转入账户的金额：\n");
    scanf("%lf",&send);
    //判断当前账户余额是否足够
    if (send > (*list)->data.money)
    {
        printf("->当前余额不足<-\n");
        sleep(1);
        printf("\n");
        return;
    }
    Node* pTemp = (*List)->pNext;
    while (pTemp)
    {
        if (0 == strcmp(toUser,pTemp->data.userId))
        {   
            printf("正在转出...\n");
            //当前账户金额改变
            (*list)->data.money -= send;
            //转入账户金额改变
            pTemp->data.money += send;
            //将修改完的数据写入文件
            SaveUser(List);
            sleep(1);
            printf("->转出成功<-\n");
            printf("\n");
            return;
        }
        pTemp=pTemp->pNext;
    }
    printf("->未查询到要转入的账户<-\n");
    sleep(1);
    printf("\n");
    return;
}
//注册用户
void addUser(Node** List){
    char newUser[NAME_LEN];
    char newPassWord[PASSWORD_LEN];
    double kai;
    bool flag;
    printf("请输入账户名称：\n");
    scanf("%s",newUser);
    //增加条件判断
    //判断链表中是否已经存在该用户名
    flag = cheakName((*List),newUser);
    if (flag){
        printf("->该账户已存在,添加失败<-\n");
        return;
    }
    printf("请输入账户密码：\n");
    scanf("%s",newPassWord);
    printf("请输入要存入该账户的金额：\n");
    scanf("%lg",&kai);
    printf("正在创建用户...\n");
    sleep(1);
    //创建临时结构体存储数据
    User newU;
    strcpy(newU.userId,newUser),strcpy(newU.passWord,newPassWord),newU.money=kai;
    //使用尾插法将新建节点插入链表
    tail_insert((*List),newU);
    //将用户数据添加进文件
    SaveUser(List);
    printf("->创建用户成功<-\n");
    printf("\n");
}

bool cheakName(Node* List,char* name){
    Node* cheakName = List->pNext;
    while (cheakName)
    {
        if (0 == strcmp(name,cheakName->data.userId))
            {
                return true;
            }
        cheakName=cheakName->pNext;
    }
    return false;
}
void managerOption(Node** List){
    int option;
    printf("->成功进入管理系统<-\n");
    while (1)
    {
        printf(" 请选择要进行的管理操作：\n");
        printf(" 1 -> 查看账户信息\n");  
        printf(" 2 -> 修改账户信息\n"); 
        printf(" 3 -> 删除账户\n");   
        printf(" 4 -> 退出管理页面\n");
        scanf("%d",&option);
        ReadUser(List);
        switch (option)
        {
            case 1:     showAll((*List));                       break;
            case 2:     changeUser(List);                       break;
            case 3:     delUser(List);                          break;
            case 4:     return;                                 break;
            default:    printf("->无效操作<-\n");                break;
        }
    }
}
void changeUser(Node** List){
    char changeUser[NAME_LEN];
    bool flag;
    printf("请输入要修改的账户名称：\n");
    scanf("%s",changeUser);
    //遍历链表查找是否存在该用户
    //判断链表中是否存在要修改的用户名
    flag = cheakName((*List),changeUser);
    if (false == flag){
        printf("->未查找到该账户,无法修改<-");
        printf("\n");
        return;
    }
    //确定链表中存在该用户
    Node* cpTemp = (*List)->pNext;
    while (cpTemp){
        if (0 == strcmp(changeUser,cpTemp->data.userId)){   
            char cNewName[NAME_LEN];
            char cNewPassWord[PASSWORD_LEN];
            double cNewMoney;
            printf("请输入要修改的数据:  ");
            printf("账户名: ");
            scanf("%s",cNewName);
            printf("账户密码: ");
            scanf("%s",cNewPassWord);
            printf("账户金额(该项需填入整数): ");
            scanf("%lg",&cNewMoney);
            printf("正在修改...\n");
            sleep(1);
            strcpy(cpTemp->data.userId,cNewName);
            strcpy(cpTemp->data.passWord,cNewPassWord);
            cpTemp->data.money=cNewMoney;
            //将修改后的数据写入文件
            SaveUser(List);
            printf("->修改完成<-\n");
            printf("\n");
            return;
        }
        cpTemp=cpTemp->pNext;
    }
    printf("->在文件中未查找到该用户<-\n");
    printf("\n");
    return;
}
void delUser(Node** List){
    char delUser[NAME_LEN];
    printf("请输入要删除的账户名称：\n");
    scanf("%s",delUser);
    //遍历链表查找是否存在该用户
    Node* dpTemp = (*List)->pNext;
    //查找删除用户的前一个节点
    Node* delUserFront = (*List)->pNext;
    while (NULL != dpTemp){
        if (0 == strcmp(delUser,dpTemp->data.userId)){
            //找到了该用户
            //如果该用户是第一个的节点
            if ((*List)->pNext==dpTemp){   
                printf("正在删除...\n");
                (*List)->pNext=dpTemp->pNext;
                free(dpTemp);
                sleep(1);
                SaveUser(List);
                printf("->该用户已删除<-\n");
                printf("\n");
                return;
            }
            //如果该用户是最后仅剩的节点
            if ( ((*List)->pNext==dpTemp) && (NULL == dpTemp->pNext)){   
                printf("正在删除...\n");
                (*List)->pNext=NULL;
                free(dpTemp);
                sleep(1);
                SaveUser(List);
                printf("->该用户已删除<-\n");
                printf("\n");
                return;
            }
            //删除中间节点
            while (NULL != delUserFront){
                if (delUserFront->pNext==dpTemp){
                    //找到了要删除用户的前一个节点
                    delUserFront->pNext=dpTemp->pNext;
                    printf("正在删除...\n");
                    free(dpTemp);
                    sleep(1);
                    //将修改好的数据写入文件
                    SaveUser(List);
                    printf("->该用户已删除<-\n");
                    printf("\n");
                    return;
                }
                delUserFront=delUserFront->pNext;
            }   
        }
        dpTemp=dpTemp->pNext;
    }
    printf("->在文件中未查找到该用户<-\n");
    printf("\n");
    return;
}