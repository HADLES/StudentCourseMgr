github仓库


假定有一个n门课程，每门课程有：课程编号，课程名称，课程性质（公共课、必修课、选修课），总学时，授课学时，实验或上机学时、学分、开课学期等信息，学生可按要求（总学分不得少于60）自由选课。试设计一选修课程系统，使之能提供以下功能。

1、系统以菜单方式工作
2、课程信息录入功能--输入
3、课程信息查询功能--输出
4、课程信息查询功能--算法

查询方式
按照学分查询。
按课程性质查询
5、学生选秀课程（可选）


同C工程目录下需要的文件有
mydefines.h
Course.h
CStack.h
Student.h
input.txt
main.cpp



按照顺序构建：课程信息结构体、用于存储课程信息的CStack结构体、包含课程信息的Student结构体、
--
Course.h
CStack.h
Student.h
--

=======================================================
Course.h文件
#define COURSE_H  1
#ifndef float
#include <float.h>
#define INPUT_CHAR_SIZE 15

typedef struct CourseNode{
	char no[INPUT_CHAR_SIZE];
	char name[INPUT_CHAR_SIZE];
	char type[INPUT_CHAR_SIZE];
	float totalTime;
	float givingCourseTime;
	float practiceTime;
	float operatingTime;
	float score;
	
	char info[INPUT_CHAR_SIZE*2];
}Course;
#endif

=======================================================
CStack.h文件
#define CSTACK_H  1

#ifndef COURSE_H
#include "Course.h"
#endif

typedef struct CStackNode {
	int size;
	Course courses[MAXSIZE/2];
} CStack;

=======================================================
Student.h文件
#define STUDENT_H 1

#ifndef COURSE_H
#include "Course.h"
#endif
#define COURSE_NUM 8
typedef struct StudentNode {
	Course course[COURSE_NUM];
} Student;

=======================================================
包含宏定义的头文件
mydefines.h
//调试时，指输入学分
#define DEBUG  1

#define foreach(T,N)  for(int i = 0; i < N ; i++,*T++)
//和上面的foreach配对使用
#define reset_pointer(T,N)  for(int i = 0; i < N ; i++,*T--)

#define NEW_COURSE (Course*)malloc(sizeof(Course))

#define new_Course() (Course*)malloc(sizeof(Course))

#define _DECLARE_COURSE_MEMERS_\
	Course *course = NEW_COURSE; \
	char no[INPUT_CHAR_SIZE]; \
	char name[INPUT_CHAR_SIZE]; \
	char type[INPUT_CHAR_SIZE]; \
	float totalTime; \
	float givingCourseTime; \
	float practiceTime; \
	float operatingTime; \
	float score; \
	char info[INPUT_CHAR_SIZE*2]; \
	 
#define _PUSH_CSTACK_\
	strcpy(course->no,no); \
	strcpy(course->name,name); \
	strcpy(course->type,type); \
	course->totalTime=totalTime; \
	course->givingCourseTime=givingCourseTime; \
	course->practiceTime=practiceTime; \
	course->operatingTime=operatingTime; \
	course->score=score; \
	strcpy(course->info,info); \
	int idx=++stack.size-1; \
	++num; \
	stack.courses[idx]=*course; \
	 
#define OUT_FILE_PATH "output.txt"

#define QUERY_BY_TYPE(_T_);\
	FILE *fp;\
	fp = fopen(OUT_FILE_PATH,"r");\
	if(fp == NULL) {\
		printf("打开不了本地文件!\n ");\
		system("pause");\
		exit(0);\
	}\
	while(!feof(fp)) {\
		_DECLARE_COURSE_MEMERS_\
		fscanf(fp,"%s %s %s %f %f %f %f %f %s\n",&no,&name,&type,&totalTime,&givingCourseTime,&practiceTime,&operatingTime,&score,&info);\
		if(0==strcmp(type,_T_)) {\
			fflush(stdin);\
			_PUSH_CSTACK_\
			printf("%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",\
			       no,\
			       name,\
			       type,\
			       totalTime,\
			       givingCourseTime,\
			       practiceTime,\
			       operatingTime,\
			       score,\
			       info\
			      );\
		}\
	} \
	fclose(fp);\
	 
//stack.courses[idx]=*course不含指针则直接复制
//memcpy(&stack.courses[idx],&course,sizeof(Course));//会出现乱码,适用于指针

=======================================================
入口函数文件
main.cpp
#define MAXSIZE 100
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

#include "Course.h"
#include "CStack.h"

#include "mydefines.h"

CStack stack;//栈顶，数据结构
CStack tmpStack;
int num=0;//课程数

//课程指针数组
void print_sheet_head();
void print_stack(CStack stack);

char ShowMenu();
void AddCourse(CStack &stack);
void LoadFromCmd();
void LoadFromFile(char loadfilepath[],char write2diskpath[]);
void QueryCourse();
//降序打印
void printByOrderDesc();

int main(int argc, char** argv) {
	//1、系统以菜单方式工作-输入
	//2、课程信息录入功能-输出
	//3、课程信息浏览功能-输出
	//4、信息查询功能-算法
	//5、学生选修课程(可选项)
	stack.size=0;
	char opt;//stdio.h里的函数
	while((opt=ShowMenu())!='0') {
		switch(opt) {
			case '1'://录入课程信息
				AddCourse(stack);
				continue;
			case '2'://输出课程信息
				print_stack(stack);
				getchar();
				continue;
			case '3'://查询课程信息
				QueryCourse();
				continue;
			case '4':
				printf("学生选修课程");
				continue;
		}
	}
	printf("退出");
	return 0;
}

char ShowMenu() {
	system("cls");
	printf("\t\t=======================================\n");
	printf("\t\t\t\t操作方式\n");
	printf("\t\t\t\t(1)录入课程信息\n");
	printf("\t\t\t\t(2)输出课程信息\n");
	printf("\t\t\t\t(3)查询课程信息\n");
	printf("\t\t\t\t(0)退出\n");
	printf("\t\t=======================================\n");
	printf("\t\t请输入选项:");
	char c=getchar();
	fflush(stdin);
	return c;
}

//打印表头
void print_sheet_head() {
//	printf("课程编号\t课程名称\t课程性质\t总学时\t授课学时\t实验学时\t上机学时\t学分\t开课信息\n");
	printf("课程编号  课程名称  课程性质  总学时  授课学时  实验学时  上机学时  学分  开课信息\n");
}
//添加一个课程
void AddCourse(CStack &stack) {
	char c;
	fflush(stdin);
	while(true) {
		system("cls");
		printf("\n\n\t\t=========  输出课程信息[查询]  ==========\n");
		printf("\t\t(1)控制台录入\n\t\t(2)文件录入\n\t\t(0)返回主菜单\n\t\t(1/2/0):");
		if((c=getchar())=='0')
			break;
		switch(c) {
			case '1':
				LoadFromCmd();
				continue;
			case '2':
				LoadFromFile((char *)"input.txt",(char *)"output.txt");//不进行强制类型转化的话，会报错
				break;
		}
	}
}
//以控制台输入的方式，录入课程信息
void LoadFromCmd() {
	printf("根据表头依次输入,以为空格分开,例如:\n");
	printf("002 数学 必修课 120 60 30 30 6 数学在我们身边\n");
	print_sheet_head() ;
	_DECLARE_COURSE_MEMERS_//宏定义，在mydefines.h里定义,声明course成员属性
	scanf("%s %s %s %f %f %f %f %f %s",
	      &no,
	      &name,
	      &type,
	      &totalTime,
	      &givingCourseTime,
	      &practiceTime,
	      &operatingTime,
	      &score,
	      &info
	     );
	_PUSH_CSTACK_//宏定义，在mydefines.h里定义,属性添加到CStack里面
	system("pause");
}

//以文件读取方式，录入课程信息
void LoadFromFile(char loadfilepath[],char write2diskpath[]) {
	FILE *fp;
	FILE *fout;
	fp = fopen(loadfilepath,"r");                  //打开文件
	fout=fopen(write2diskpath,"a");
	if(fp == NULL) {
		printf("打开不了录入文件!\n ");
		system("pause");
		exit(0);                                 //头文件需要有 stdlib.h
	} else {
		while(!feof(fp)) {//fscanf()格式化字符串结尾若没有\n,会出现多读一次最后一行的情况
			_DECLARE_COURSE_MEMERS_//宏定义,在mydefines.h里定义,声明course成员属性
			fscanf(fp,"%s %s %s %f %f %f %f %f %s\n",&no,&name,&type,&totalTime,&givingCourseTime,&practiceTime,&operatingTime,&score,&info);
			fflush(stdin);
//			printf("%s %s %s %0.1f %0.1f %0.1f %0.1f %0.1f %s\n",no,name,type,totalTime,givingCourseTime,practiceTime,operatingTime,score,info);
//			printf(" %s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",no,name,type,totalTime,givingCourseTime,practiceTime,operatingTime,score,info);
			_PUSH_CSTACK_//宏定义，在mydefines.h里定义,属性添加到CStack里面
			if(NULL==fout) {
				printf("注意无法写入本地文件，请检查路径!\n");
				system("pause");
			} else {
				fprintf(fout,"%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",
				        no,
				        name,
				        type,
				        totalTime,
				        givingCourseTime,
				        practiceTime,
				        operatingTime,
				        score,
				        info
				       );
			}
		}
	}
	print_stack(stack);
	system("pause");
	fclose(fp);
	fclose(fout);
	system("cls");
}
//查询课程
void QueryCourse() {
	fflush(stdin);
	printf("\n\n\t\t=========  输出课程信息[查询]  ==========\n");
	if(stack.size==0) {
		printf("\t\t\t暂无课程信息\n");
		system("pause");
		return;
	}
	char c;
	while(true) {
		system("cls");
		printf("\n\n\t\t=========  输出课程信息[查询]  ==========\n");
		printf("\t\t(1)按照学分查询[降序打印]\n\t\t(2)按照课程性质查询\n\t\t(0)返回主菜单\n\t\t(1/2/0):");
		if((c=getchar())=='0')
			break;
		switch(c) {
			case '1':
				printByOrderDesc();
				system("pause");
				continue;
			case '2':
				printf("\t\tA/a.公共课 B/b.必修课 C/c.选修课:\n\t\t");
				fflush(stdin);//不刷新缓存的话会被下面的getchar()收获 
				char abc=getchar();
				if(abc=='A'||abc=='a') {
					QUERY_BY_TYPE("公共课");
				} else if(abc=='B'||abc=='b') {
					QUERY_BY_TYPE("必修课");
				} else if(abc=='C'||abc=='c') {
					QUERY_BY_TYPE("选修课");
				}
				system("pause");
				continue;
		}
	}
}

/**
*按照学分降序排列和打印
**/
void printByOrderDesc() {
	tmpStack=stack;//拷贝
	for(int i=0; i<num-1; i++) {//冒泡排序
		for(int j=0; j<num-i-1; j++) {
			if(tmpStack.courses[j].score<tmpStack.courses[j+1].score) {//比较各课程分数大小，前者一项后一项小时，替换顺序，也就是，大的在前，小得在后 ，最终打印结果为降序
				Course c=tmpStack.courses[j];
				tmpStack.courses[j]=tmpStack.courses[j+1];
				tmpStack.courses[j+1]=c;
			}
		}
	}
	print_stack(tmpStack);
}

//遍历和打印栈
void print_stack(CStack stack) {
	print_sheet_head();
	for(int i=0; i<stack.size; i++) {
//		printf("\%4s\t%4s\t%4s\t%0.1f\t%0.1f\t%0.1f\t%0.1f\t%0.1f\t%8s\n",
		printf("%s  %s  %s  %0.1f  %0.1f  %0.1f  %0.1f  %0.1f %s\n",
		       stack.courses[i].no,
		       stack.courses[i].name,
		       stack.courses[i].type,
		       stack.courses[i].totalTime,
		       stack.courses[i].givingCourseTime,
		       stack.courses[i].practiceTime,
		       stack.courses[i].operatingTime,
		       stack.courses[i].score,
		       stack.courses[i].info
		      );
	}
}

=======================================================
录入数据的文件
input.txt
001 英语 必须课 120 100 20 0 6 学英语,去国外
002 数学 必修课 120 60 30 30 6 数学在我们身边
003 思修 公共课 100 50 25 25 3 做个思想的伟人


