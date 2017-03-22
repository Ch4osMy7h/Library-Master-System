#include"head.h"
//获取系统的时间
int getSystemYear()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  

	return 1900 + p->tm_year; 
	//int tm_year; /* 年份，其值等于实际年份减去1900 */
}
int getSystemMonth()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  
	return 1 + p->tm_mon;
	//（从一月开始，0代表一月） - 取值区间为[0,11] */
}
int getSystemDay()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  
	return p->tm_mday; 
	//一个月中的日期 - 取值区间为[1,31] */
}


//计算时间差几天
int day_diff(int year_start, int month_start, int day_start
	, int year_end, int month_end, int day_end)
{
	int y2, m2, d2;
	int y1, m1, d1;

	m1 = (month_start + 9) % 12; //用于判断日期是否大于3月（2月是判断闰年的标识），还用于纪录到3月的间隔月数
	y1 = year_start - m1 / 10;   //如果是1月和2月，则不包括当前年（因为是计算到0年3月1日的天数）。
	d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_start - 1);
	/*365*y是不算闰年多出那一天的天数， y1/4 - y1/100 + y1/400是加所有闰年多出的那一天，
	(m2 * 306 + 5) / 10 用于计算到当前月到3月1日间的天数，306 = 365 - 31 - 28（1月和2月），5是全年中不是31天月份的个数
	(day_start - 1) 用于计算当前日到1日的间隔天数。*/
	m2 = (month_end + 9) % 12;  
	y2 = year_end - m2 / 10;
	d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day_end - 1);
	return (d2 - d1);
}

//看是否超期罚款
int is_penalty(struct Student* student)
{
	int i;
	char id[105];
	for (i = 0; i<student->borrown; i++)
	{
		struct BookNode* bookNode;
		strcpy(id, student->borrow_id[i]);
		bookNode = findbooknodebyid(id);
		if (day_diff(bookNode->book.year, bookNode->book.month, bookNode->book.day,
			getSystemYear(), getSystemMonth(), getSystemDay())>60)
		{
			return 1;
		}
	}
	return 0;
}



int menu()
{
	system("cls");
	system("color 03");
	int choice;
	printf("\n");
	printf("\t        =====================图书信息管理系统=====================\n");
	printf("\t         **************************Menu**************************\n");
	printf("\t         *1:录入图书信息");
	printf("\t         2:修改图书信息         *\n");
	printf("\t         *3:删除图书");
	printf("\t                 4:显示所有图书         *\n");
	printf("\t         *5:注册学生信息");
	printf("\t         6:显示所有学生信息     *\n");
	printf("\t         *7:删除学生");
	printf("\t                 8:修改学生信息         *\n");
	printf("\t         *9:借书");
	printf("\t                 10:还书                *\n");
	printf("\t         *11:按作者查询图书");
	printf("\t         12:按专业领域查找      *\n");
	printf("\t         *13:学生号查找学生");
	printf("\t         0:退出                 *\n");
	printf("\t         ********************************************************\n");
	printf("请输入您的选择:");
	scanf("%d", &choice);
	if (choice == 0)
	{
		return 0;
	}
	else if (choice == 1)
	{
		while (1) {
			system("cls");
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
			printf("\t--------------------------------------------------\n");
			printf("\t请输入图书编号:");
			scanf("%s", id);
			printf("\t请输入书名:");
			scanf("%s", name);
			printf("\t请输入图书专业领域检索号:");
			scanf("%s", professional_field);
			printf("\t请输入图书单价:");
			scanf("%d", &price);
			printf("\t请输入图书作者:");
			scanf("%s", author);
			printf("\t请输入图书出版社:");
			scanf("%s", publication);
			addBook(id, name, professional_field, price, author, publication, 0, "", "", "", 0, 0, 0);
			printf("\t--------------------------------------------------\n");
			printf("\t录入成功\n");
			char c;
			printf("\t请问是否要继续输入 Y/N\n");
			rewind(stdin);
			printf("\t");
			scanf("%c", &c);
			if (c == 'N'||c == 'n') { break; }
		}
		printf("\t");
		system("pause");
	}
	else if (choice == 2)
	{
		system("cls");
		editBook();
		printf("\t\t");
		system("pause");
	}
	else if (choice == 3)
	{
		system("cls");
		char id[105];
		printf("\t\t==============图书删除===============\n");
		printf("\t\t请输入要删除的图书编号:");
		scanf("%s", id);
		deleteBook(id);
		printf("\t\t");
		system("pause");
	}
	else if (choice == 4)
	{
		system("cls");
		printf("\t\t显示结果如下:\n");
		printAllBook();
		printf("\t\t");
		system("pause");
	}
	else if (choice == 5)
	{
		system("cls");
		char id[105];
		char name[105];
		char sex[105];
		int borrown = 0;
		char borrow_id[15][105];
		printf("\t\t==============会员注册===============\n");
		printf("\t\t请输入学生学号:");
		scanf("%s", id);
		printf("\t\t请输入学生姓名;");
		scanf("%s", name);
		printf("\t\t请输入学生性别:");
		scanf("%s", sex);
		addStudent(id, name, sex, borrown, borrow_id);
		printf("\t\t注册成功\n");
		printf("\t\t");
		system("pause");
	}
	else if (choice == 6)
	{
		system("cls");
		printf("显示结果如下:\n");
		printAllStudent();
		system("pause");
	}
	else if (choice == 7)
	{
		system("cls");
		char id[105];
		printf("\t\t==============学生删除===============\n");
		printf("\t\t请输入要删除的学生编号:");
		scanf("%s", id);
		deleteStudent(id);
		printf("\t\t");
		system("pause");
	}
	else if (choice == 8)
	{
		system("cls");
		char id[105];
		char name[105];
		char sex[105];
		editStudent();
		printf("\t");
		system("pause");
	}
	else if (choice == 9)
	{
		system("cls");
		char studentid[105];
		char bookid[105];
		struct StudentNode* studentNode;
		struct BookNode* bookNode;
		printf("\t\t==============借书系统================\n");
		printf("\t\t请输入要借书的学生学号:");
		scanf("%s", studentid);
		studentNode = findstudentnodebyid(studentid);
		if (studentNode == NULL)
		{
			printf("\t\t该学生学号不存在\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (studentNode->student.borrown >= 10)
		{
			printf("\t\t已达到借书上限10本，无法继续借书\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (is_penalty(&studentNode->student))
		{
			printf("\t\t该学生书本超期罚款，未归还，不可借书\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		printf("\t\t请输入书本的编号:");
		scanf("%s", bookid);
		bookNode = findbooknodebyid(bookid);
		if (bookNode == NULL)
		{
			printf("\t\t该书未找到\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (bookNode->book.isborrowed)
		{
			printf("\t\t该书已被借出\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		strcpy(studentNode->student.borrow_id[studentNode->student.borrown++], bookid);
		strcpy(bookNode->book.borrowed_id, studentid);
		strcpy(bookNode->book.borrowed_name, studentNode->student.name);
		strcpy(bookNode->book.borrowed_sex, studentNode->student.sex);
		bookNode->book.year = getSystemYear();
		bookNode->book.month = getSystemMonth();
		bookNode->book.day = getSystemDay();
		bookNode->book.isborrowed = 1;
		printf("\t\t借书成功\n");
		printf("\t\t");
		system("pause");
	}
	else if (choice == 10)
	{
		system("cls");
		char studentid[105];
		char bookid[105];
		struct StudentNode* studentNode;
		struct BookNode* bookNode;
		int i, j;
		printf("\t\t===============还书系统=================\n");
		printf("\t\t请输入还书的学生学号:");
		scanf("%s", studentid);
		studentNode = findstudentnodebyid(studentid);
		if (studentNode == NULL)
		{
			printf("\t\t该学生学号不存在\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		printf("\t\t请输入书本的编号:");
		scanf("\t\t%s", bookid);
		bookNode = findbooknodebyid(bookid);
		if (bookNode == NULL)
		{
			printf("\t\t该书未找到\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (day_diff(bookNode->book.year, bookNode->book.month, bookNode->book.day,
			getSystemYear(), getSystemMonth(), getSystemDay())>60)
		{
			printf("\t\t书本已经超期，需要缴纳处罚金\n");
			printf("\t\t");
			system("pause");
		}
		bookNode->book.isborrowed = 0;
		for (i = 0; i<studentNode->student.borrown; i++)
		{
			if (strcmp(bookid, studentNode->student.borrow_id[i]) == 0)
			{
				for (j = i; j<studentNode->student.borrown - 1; j++)
				{
					strcpy(studentNode->student.borrow_id[j], studentNode->student.borrow_id[j + 1]);
				}
				studentNode->student.borrown--;
				printf("\t\t还书成功\n");
				break;
			}
		}
		printf("\t\t");
		system("pause");
	}
	else if (choice == 11)
	{
		system("cls");
		char author[105];
		struct BookNode* bookNode;
		printf("\t\t================================\n");
		printf("\t\t请输入查询书本的作者名字:");
		scanf("%s", author);
        bookNode = findbooknodebyauthor(author);
		if (bookNode == NULL)
			printf("\t\t无法查询到该图书\n");
		else printBookNode(bookNode);
		printf("\t\t");
		system("pause");
	}
	else if (choice == 12)
	{
		system("cls");
		char professional_field[105];
		struct BookNode* bookNode;
		printf("\t\t================================\n");
		printf("\t\t请输入查询书本的专业领域:");
		scanf("%s", professional_field);

		bookNode = findbooknodebyprofessional_field(professional_field);
		if (bookNode == NULL)
			printf("\t\t无法查询到该图书\n");
		else printBookNode(bookNode);
		printf("\t\t");
		system("pause");
	}
	else if (choice == 13)
	{
		system("cls");
		char id[105];
		struct StudentNode* studentNode;
		printf("\t\t================================\n");
		printf("\t\t请输入查询学生的学号:");
		scanf("%s", id);

		studentNode = findstudentnodebyid(id);
		if (studentNode == NULL)
			printf("\t\t无法查询到该学生\n");
		else 
		printStudent(&studentNode->student);
		printf("\t\t");
		system("pause");
	}
	return 1;
}


int main()
{
	readBook();
	readStudent();
	while (menu())
	{
		;
	}
	saveBook();
	saveStudent();
}
