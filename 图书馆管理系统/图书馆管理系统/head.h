#pragma once
#include<stdio.h>
#include <time.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>


//�鱾�ṹ��
struct Book
{
	//ͼ����
	char id[105];
	//ͼ������
	char name[105];
	//רҵ����
	char professional_field[105];
	//����
	int price;
	//����
	char author[105];
	//������
	char publication[105];
	//����״̬
	int isborrowed;
	//����������
	char borrowed_name[105];
	//�Ա�
	char borrowed_sex[105];
	//ѧ��
	char borrowed_id[105];
	//����ʱ��
	int year;
	int month;
	int day;
};
//�鱾����ṹ��
struct BookNode
{
	struct Book book;
	struct BookNode* next;
};


//ѧ���ṹ��
struct Student
{
	//ѧ����
	char id[105];
	//����
	char name[105];
	//�Ա�
	char sex[105];
	//���˼�����
	int borrown;
	//�����ı��
	char borrow_id[15][105];
};
//ѧ������ṹ��
struct StudentNode
{
	struct Student student;
	struct StudentNode* next;
};
//ͼ��������ָ��
static struct BookNode* bookroot = NULL;
//ѧ��������ָ��
static struct StudentNode* studentroot = NULL;
//��ӡ�鱾����
void printBook(struct Book* book);
void printBookNode(struct BookNode* bookNode);
//���ͼ��
void addBook(char id[], char name[], char professional_field[], int price, char author[], char publication[], int isborrowed, char borrowed_name[], char borrowed_sex[], char borrowed_id[], int year, int month, int day);
//���ձ�Ų���ͼ��
struct BookNode* findbooknodebyid(char id[]);
//�������߲���ͼ��
struct BookNode* findbooknodebyauthor(char author[]);
//����ѧ�Ų���ͼ��
struct BookNode* findbooknodebyprofessional_field(char professional_field[]);
//�޸�ͼ��
void editBook();
//ɾ��ͼ��
void deleteBook(char id[]);
//��ӡ����ͼ��
void printAllBook();
//���浽�ļ���
void saveBook();
//���ļ��ж�ȡ
void readBook();

//��ӡѧ����Ϣ
void printStudent(struct Student* student);
//��ӡ����ѧ����Ϣ
void printAllStudent();
//���ѧ��
void addStudent(char id[], char name[], char sex[], int borrown, char borrow_id[][105]);
//����ѧ���Ų���
struct StudentNode* findstudentnodebyid(char id[]);
//����ѧ����Ϣ
void saveStudent();
//��ȡѧ����Ϣ
void readStudent();
//ɾ��ѧ����Ϣ
void deleteStudent(char id[]);
//�޸�ѧ����Ϣ
void editStudent();

