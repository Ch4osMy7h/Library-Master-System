#include"head.h"
//打印书本内容
void printBook(struct Book* book)
{
	printf("\t\t===================图书列表===================\n");
	printf("\t\t图书编号：%s   <--------\n", book->id);
	printf("\t\t图书名称：%s\n", book->name);
	printf("\t\t专业领域：%s\n", book->professional_field);
	printf("\t\t单价：%d\n", book->price);
	printf("\t\t作者：%s\n", book->author);
	printf("\t\t出版社：%s\n", book->publication);
	if (book->isborrowed)
		printf("\t\t书本已借出，借给：%s，其学号%s：借书时间：%d年%d月%d日\n", book->borrowed_name, book->borrowed_id, book->year, book->month, book->day);
	else
		printf("\t\t该书未借出\n");
}
void printBookNode(struct BookNode* bookNode)
{
	printBook(&bookNode->book);
}
//打印所有图书
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

//添加图书
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

//按照编号查找图书
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
//按照作者查找图书
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
//按照专业领域查找
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

//修改图书
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
	printf("\t\t请输入要修改的图书编号:");
	scanf("%s", id);
	struct BookNode* find = findbooknodebyid(id);
	if (find == NULL)
	{
		printf("\t\t该书本不存在\n");
		return;
	}
	printf("\t\t请输入书名:");
	scanf("%s", name);
	printf("\t\t请输入图书专业领域检索号:");
	scanf("%s", professional_field);
	printf("\t\t请输入图书单价:");
	scanf("%d", &price);
	printf("\t\t请输入图书作者:");
	scanf("%s", author);
	printf("\t\t请输入图书出版社:");
	scanf("%s", publication);
	strcpy(find->book.id, id);
	strcpy(find->book.name, name);
	strcpy(find->book.professional_field, professional_field);
	find->book.price = price;
	strcpy(find->book.author, author);
	strcpy(find->book.publication, publication);
	printf("\t\t修改成功\n");
}
//删除图书
void deleteBook(char id[])
{
	struct BookNode* find = findbooknodebyid(id);
	if (find == NULL)
	{
		printf("\t\t该书本不存在\n");
		return;
	}
	if (find == bookroot)
	{
		struct BookNode* temp = bookroot;
		bookroot = bookroot->next;
		free(temp);
		printf("\t\t删除成功\n");
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
				printf("\t\t删除成功\n");
				break;
			}
			cur = cur->next;
		}
	}
}
//保存到文件中
void saveBook()
{
	FILE* fp = fopen("book.txt", "w");
	if (fp == NULL)
	{
		printf("不能打开此文件\n");
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
//从文件中读取
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
		printf("不能打开此文件\n");
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





