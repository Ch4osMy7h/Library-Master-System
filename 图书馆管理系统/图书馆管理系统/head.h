#pragma once
#include<stdio.h>
#include <time.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>


//书本结构体
struct Book
{
	//图书编号
	char id[105];
	//图书名称
	char name[105];
	//专业领域
	char professional_field[105];
	//单价
	int price;
	//作者
	char author[105];
	//出版社
	char publication[105];
	//存在状态
	int isborrowed;
	//借书人姓名
	char borrowed_name[105];
	//性别
	char borrowed_sex[105];
	//学号
	char borrowed_id[105];
	//借书时间
	int year;
	int month;
	int day;
};
//书本链表结构体
struct BookNode
{
	struct Book book;
	struct BookNode* next;
};


//学生结构体
struct Student
{
	//学生号
	char id[105];
	//姓名
	char name[105];
	//性别
	char sex[105];
	//借了几本书
	int borrown;
	//借的书的编号
	char borrow_id[15][105];
};
//学生链表结构体
struct StudentNode
{
	struct Student student;
	struct StudentNode* next;
};
//图书链表首指针
static struct BookNode* bookroot = NULL;
//学生链表首指针
static struct StudentNode* studentroot = NULL;
//打印书本内容
void printBook(struct Book* book);
void printBookNode(struct BookNode* bookNode);
//添加图书
void addBook(char id[], char name[], char professional_field[], int price, char author[], char publication[], int isborrowed, char borrowed_name[], char borrowed_sex[], char borrowed_id[], int year, int month, int day);
//按照编号查找图书
struct BookNode* findbooknodebyid(char id[]);
//按照作者查找图书
struct BookNode* findbooknodebyauthor(char author[]);
//按照学号查找图书
struct BookNode* findbooknodebyprofessional_field(char professional_field[]);
//修改图书
void editBook();
//删除图书
void deleteBook(char id[]);
//打印所有图书
void printAllBook();
//保存到文件中
void saveBook();
//从文件中读取
void readBook();

//打印学生信息
void printStudent(struct Student* student);
//打印所有学生信息
void printAllStudent();
//添加学生
void addStudent(char id[], char name[], char sex[], int borrown, char borrow_id[][105]);
//按照学生号查找
struct StudentNode* findstudentnodebyid(char id[]);
//保存学生信息
void saveStudent();
//读取学生信息
void readStudent();
//删除学生信息
void deleteStudent(char id[]);
//修改学生信息
void editStudent();

