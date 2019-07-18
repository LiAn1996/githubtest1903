#ifndef _COMMON_H_
#define _COMMON_H_

#include<stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<sqlite3.h>

#include<pthread.h>
#include<sys/select.h>
#include<sys/time.h>

#include<sys/wait.h>
#include<signal.h>
#include<time.h>


#define STAFF_DATABASE 	 "staff_manage_system.db"   //数据库地址


#define USER_LOGIN 		0x00000000  // login	登陆    0x00000001
#define USER_MODIFY 	0x00000001  // user-modification  修改
#define USER_QUERY 		0x00000002  // user-query   查询

#define ADMIN_LOGIN 	0x10000000  // login	登陆    0x00000001
#define ADMIN_MODIFY 	0x10000001 // admin_modification
#define ADMIN_ADDUSER 	0x10000002 // admin_adduser
#define ADMIN_DELUSER 	0x10000004 // admin_deluser
#define ADMIN_QUERY 	0x10000008  //hitory_query
#define ADMIN_HISTORY 	0x10000010  //hitory_query

#define QUIT 			0x11111111

#define ADMIN 0	//管理员
#define USER  1	//用户
#define NAMELEN 16
#define DATALEN 128
#define History_limit 50

typedef struct staff_info
{
    int  no;           // 员工编号
	int usertype;		//ADMIN 1  USER 2
	char name[16];		//姓名
	char passwd[8];		//密码
	int  age;			//年龄
	char phone[12];		//电话
	char addr[128];		//地址
	char work[128];		//职位
	char date[128];		//入职年月
	int  level;			//等级
	double salary;		//工资

}staff_info_t;

typedef struct Hist_Struct{
		char time[DATALEN];
			char words[DATALEN];
}HIST;

/*定义双方那个通信的结构提信息*/
typedef struct
{
	int  msgtype;   			//请求的消息类型
	int  usertype;			//ADMIN 1 USER 2
	char username[16];		//姓名
	char passwd[8];			//登录密码
	char recvmsg[128];		//通信的消息
	int  flags;				//标志位
	staff_info_t info;		//员工信息
	HIST hist;
}MSG;


/*定义线程处理的结构体信息*/
typedef struct thread_data{
		int acceptfd;
		pthread_t thread;
	    int state; //线程状态
	    MSG *msg; 
		void *prvi_data;
}thread_data_t;

//扩展:线程链表信息
typedef struct thread_node{
	thread_data_t data;
	struct thread_node *next;
}linklist, *plinklist;

#endif
