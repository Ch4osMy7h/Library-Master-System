#include"head.h"
//��ӡ�鱾����
void printBook(struct Book* book)
{
	printf("\t\t===================ͼ���б�===================\n");
	printf("\t\tͼ���ţ�%s   <--------\n", book->id);
	printf("\t\tͼ�����ƣ�%s\n", book->name);
	printf("\t\tרҵ����%s\n", book->professional_field);
	printf("\t\t���ۣ�%d\n", book->price);
	printf("\t\t���ߣ�%s\n", book->author);
	printf("\t\t�����磺%s\n", book->publication);
	if (book->isborrowed)
		printf("\t\t�鱾�ѽ���������%s����ѧ��%s������ʱ�䣺%d��%d��%d��\n", book->borrowed_name, book->borrowed_id, book->year, book->month, book->day);
	else
		printf("\t\t����δ���\n");
}
void printBookNode(struct BookNode* bookNode)
{
	printBook(&bookNode->book);
}
//��ӡ����ͼ��
void printAllBook()
{
	struct BookNode* cur = bookroot;
	for(;cur->next!=NULL;cur=cur->next)
	{
		if (cur == NULL)
			break;
		printBookNode(cur);
		cur = cur->next;
	}
}

//���ͼ��
void addBook(char id[], char name[], char professional_field[], int price, char author[], char publication[], int isborrowed, char borrowed_name[], char borrowed_sex[], char borrowed_id[], int year, int month, int day)
{
	struct BookNode* booknode;
	struct Book* book = (struct Book*) malloc(sizeof(struct Book) * 1);
	strcpy(book->id, id);
	strcpy(book->name, name);
	strcpy(book->professional_field, professional_field);
	book->price = price;
	strcpy(book->author, author);
	strcpy(book->publication, publication);
	book->isborrowed = isborrowed;
	strcpy(book->borrowed_name, borrowed_name);
	strcpy(book->borrowed_sex, borrowed_sex);
	strcpy(book->borrowed_id, borrowed_id);
	book->year = year;
	book->month = month;
	book->day = day;

	booknode = (struct BookNode*) malloc(sizeof(struct BookNode) * 1);
	booknode->book = (*book);
	booknode->next = NULL;

	if (bookroot == NULL)
	{
		bookroot = booknode;
	}
	else
	{
		struct BookNode* cur = bookroot;
		while (1)
		{
			if (cur->next == NULL)
			{
				cur->next = booknode;
				break;
			}
			cur = cur->next;
		}
	}
}

//���ձ�Ų���ͼ��
struct BookNode* findbooknodebyid(char id[])
{
	struct BookNode* cur = bookroot;
	while (1)
	{
		if (cur == NULL)
			break;
		if (strcmp(cur->book.id, id) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//�������߲���ͼ��
struct BookNode* findbooknodebyauthor(char author[])
{
	struct BookNode* cur = bookroot;
	while (1)
	{
		if (cur == NULL)
			break;
		if (strcmp(cur->book.author, author) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//����רҵ�������
struct BookNode* findbooknodebyprofessional_field(char professional_field[])
{
	struct BookNode* cur = bookroot;
	while (1)
	{
		if (cur == NULL)
			break;
		if (strcmp(cur->book.professional_field, professional_field) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

//�޸�ͼ��
void editBook()
{
	char id[105];
	char name[105];
	char professional_field[105];
	int price;
	char author[105];
	char publication[105];
	int isborrowed;
	char borrowed_name[105];
	char borrowed_sex[105];
	char borrowed_id[105];
	char tem[105];
	printf("\t\t==============================\n");
	printf("\t\t������Ҫ�޸ĵ�ͼ����:");
	scanf("%s", id);
	struct BookNode* find = findbooknodebyid(id);
	if (find == NULL)
	{
		printf("\t\t���鱾������\n");
		return;
	}
	printf("\t\t����������:");
	scanf("%s", name);
	printf("\t\t������ͼ��רҵ���������:");
	scanf("%s", professional_field);
	printf("\t\t������ͼ�鵥��:");
	scanf("%d", &price);
	printf("\t\t������ͼ������:");
	scanf("%s", author);
	printf("\t\t������ͼ�������:");
	scanf("%s", publication);
	strcpy(find->book.id, id);
	strcpy(find->book.name, name);
	strcpy(find->book.professional_field, professional_field);
	find->book.price = price;
	strcpy(find->book.author, author);
	strcpy(find->book.publication, publication);
	printf("\t\t�޸ĳɹ�\n");
}
//ɾ��ͼ��
void deleteBook(char id[])
{
	struct BookNode* find = findbooknodebyid(id);
	if (find == NULL)
	{
		printf("\t\t���鱾������\n");
		return;
	}
	if (find == bookroot)
	{
		struct BookNode* temp = bookroot;
		bookroot = bookroot->next;
		free(temp);
		printf("\t\tɾ���ɹ�\n");
	}
	else
	{
		struct BookNode* cur = bookroot;
		while (1)
		{
			if (cur == NULL)
				break;
			if (cur->next == find)
			{
				cur->next = cur->next->next;
				printf("\t\tɾ���ɹ�\n");
				break;
			}
			cur = cur->next;
		}
	}
}
//���浽�ļ���
void saveBook()
{
	FILE* fp = fopen("book.txt", "w");
	if (fp == NULL)
	{
		printf("���ܴ򿪴��ļ�\n");
		exit(EXIT_FAILURE);
	}
	struct BookNode* cur = bookroot;
	while (1)
	{
		if (cur == NULL)
			break;
		else
		{
			fprintf(fp, "%s\n", cur->book.id);
			fprintf(fp, "%s\n", cur->book.name);
			fprintf(fp, "%s\n", cur->book.professional_field);
			fprintf(fp, "%d\n", cur->book.price);
			fprintf(fp, "%s\n", cur->book.author);
			fprintf(fp, "%s\n", cur->book.publication);
			fprintf(fp, "%d\n", cur->book.isborrowed);
			fprintf(fp, "%s\n", cur->book.borrowed_name);
			fprintf(fp, "%s\n", cur->book.borrowed_sex);
			fprintf(fp, "%s\n", cur->book.borrowed_id);
			fprintf(fp, "%d\n", cur->book.year);
			fprintf(fp, "%d\n", cur->book.month);
			fprintf(fp, "%d\n", cur->book.day);
			cur = cur->next;
		}
	}
	fclose(fp);
}
//���ļ��ж�ȡ
void readBook()
{
	char id[105];
	char name[105];
	char professional_field[105];
	int price;
	char author[105];
	char publication[105];
	int isborrowed;
	char borrowed_name[105];
	char borrowed_sex[105];
	char borrowed_id[105];
	char tem[105];
	int year, month, day;
	FILE* fp = fopen("book.txt", "r");
	if (fp == NULL)
	{
		printf("���ܴ򿪴��ļ�\n");
		exit(EXIT_FAILURE);
	}
	bookroot = NULL;
	while (fgets(id, 105, fp) != NULL)
	{
		id[strlen(id) - 1] = '\0';
		fgets(name, 105, fp);
		name[strlen(name) - 1] = '\0';
		fgets(professional_field, 105, fp);
		professional_field[strlen(professional_field) - 1] = '\0';
		fgets(tem, 105, fp);
		price = atoi(tem);
		fgets(author, 105, fp);
		author[strlen(author) - 1] = '\0';
		fgets(publication, 105, fp);
		publication[strlen(publication) - 1] = '\0';
		fgets(tem, 105, fp);
		isborrowed = atoi(tem);
		fgets(borrowed_name, 105, fp);
		borrowed_name[strlen(borrowed_name) - 1] = '\0';
		fgets(borrowed_sex, 105, fp);
		borrowed_sex[strlen(borrowed_sex) - 1] = '\0';
		fgets(borrowed_id, 105, fp);
		borrowed_id[strlen(borrowed_id) - 1] = '\0';
		fgets(tem, 105, fp);
		year = atoi(tem);
		fgets(tem, 105, fp);
		month = atoi(tem);
		fgets(tem, 105, fp);
		day = atoi(tem);
		addBook(id, name, professional_field, price, author, publication, isborrowed, borrowed_name, borrowed_sex, borrowed_id, year, month, day);
	}
}





