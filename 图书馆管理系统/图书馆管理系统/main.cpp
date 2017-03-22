#include"head.h"
//��ȡϵͳ��ʱ��
int getSystemYear()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ��  

	return 1900 + p->tm_year; 
	//int tm_year; /* ��ݣ���ֵ����ʵ����ݼ�ȥ1900 */
}
int getSystemMonth()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ��  
	return 1 + p->tm_mon;
	//����һ�¿�ʼ��0����һ�£� - ȡֵ����Ϊ[0,11] */
}
int getSystemDay()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //�˺�����õ�tm�ṹ���ʱ�䣬���Ѿ����й�ʱ��ת��Ϊ����ʱ��  
	return p->tm_mday; 
	//һ�����е����� - ȡֵ����Ϊ[1,31] */
}


//����ʱ����
int day_diff(int year_start, int month_start, int day_start
	, int year_end, int month_end, int day_end)
{
	int y2, m2, d2;
	int y1, m1, d1;

	m1 = (month_start + 9) % 12; //�����ж������Ƿ����3�£�2�����ж�����ı�ʶ���������ڼ�¼��3�µļ������
	y1 = year_start - m1 / 10;   //�����1�º�2�£��򲻰�����ǰ�꣨��Ϊ�Ǽ��㵽0��3��1�յ���������
	d1 = 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 + (m1 * 306 + 5) / 10 + (day_start - 1);
	/*365*y�ǲ�����������һ��������� y1/4 - y1/100 + y1/400�Ǽ���������������һ�죬
	(m2 * 306 + 5) / 10 ���ڼ��㵽��ǰ�µ�3��1�ռ��������306 = 365 - 31 - 28��1�º�2�£���5��ȫ���в���31���·ݵĸ���
	(day_start - 1) ���ڼ��㵱ǰ�յ�1�յļ��������*/
	m2 = (month_end + 9) % 12;  
	y2 = year_end - m2 / 10;
	d2 = 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 + (m2 * 306 + 5) / 10 + (day_end - 1);
	return (d2 - d1);
}

//���Ƿ��ڷ���
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
	printf("\t        =====================ͼ����Ϣ����ϵͳ=====================\n");
	printf("\t         **************************Menu**************************\n");
	printf("\t         *1:¼��ͼ����Ϣ");
	printf("\t         2:�޸�ͼ����Ϣ         *\n");
	printf("\t         *3:ɾ��ͼ��");
	printf("\t                 4:��ʾ����ͼ��         *\n");
	printf("\t         *5:ע��ѧ����Ϣ");
	printf("\t         6:��ʾ����ѧ����Ϣ     *\n");
	printf("\t         *7:ɾ��ѧ��");
	printf("\t                 8:�޸�ѧ����Ϣ         *\n");
	printf("\t         *9:����");
	printf("\t                 10:����                *\n");
	printf("\t         *11:�����߲�ѯͼ��");
	printf("\t         12:��רҵ�������      *\n");
	printf("\t         *13:ѧ���Ų���ѧ��");
	printf("\t         0:�˳�                 *\n");
	printf("\t         ********************************************************\n");
	printf("����������ѡ��:");
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
			printf("\t������ͼ����:");
			scanf("%s", id);
			printf("\t����������:");
			scanf("%s", name);
			printf("\t������ͼ��רҵ���������:");
			scanf("%s", professional_field);
			printf("\t������ͼ�鵥��:");
			scanf("%d", &price);
			printf("\t������ͼ������:");
			scanf("%s", author);
			printf("\t������ͼ�������:");
			scanf("%s", publication);
			addBook(id, name, professional_field, price, author, publication, 0, "", "", "", 0, 0, 0);
			printf("\t--------------------------------------------------\n");
			printf("\t¼��ɹ�\n");
			char c;
			printf("\t�����Ƿ�Ҫ�������� Y/N\n");
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
		printf("\t\t==============ͼ��ɾ��===============\n");
		printf("\t\t������Ҫɾ����ͼ����:");
		scanf("%s", id);
		deleteBook(id);
		printf("\t\t");
		system("pause");
	}
	else if (choice == 4)
	{
		system("cls");
		printf("\t\t��ʾ�������:\n");
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
		printf("\t\t==============��Աע��===============\n");
		printf("\t\t������ѧ��ѧ��:");
		scanf("%s", id);
		printf("\t\t������ѧ������;");
		scanf("%s", name);
		printf("\t\t������ѧ���Ա�:");
		scanf("%s", sex);
		addStudent(id, name, sex, borrown, borrow_id);
		printf("\t\tע��ɹ�\n");
		printf("\t\t");
		system("pause");
	}
	else if (choice == 6)
	{
		system("cls");
		printf("��ʾ�������:\n");
		printAllStudent();
		system("pause");
	}
	else if (choice == 7)
	{
		system("cls");
		char id[105];
		printf("\t\t==============ѧ��ɾ��===============\n");
		printf("\t\t������Ҫɾ����ѧ�����:");
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
		printf("\t\t==============����ϵͳ================\n");
		printf("\t\t������Ҫ�����ѧ��ѧ��:");
		scanf("%s", studentid);
		studentNode = findstudentnodebyid(studentid);
		if (studentNode == NULL)
		{
			printf("\t\t��ѧ��ѧ�Ų�����\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (studentNode->student.borrown >= 10)
		{
			printf("\t\t�Ѵﵽ��������10�����޷���������\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (is_penalty(&studentNode->student))
		{
			printf("\t\t��ѧ���鱾���ڷ��δ�黹�����ɽ���\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		printf("\t\t�������鱾�ı��:");
		scanf("%s", bookid);
		bookNode = findbooknodebyid(bookid);
		if (bookNode == NULL)
		{
			printf("\t\t����δ�ҵ�\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (bookNode->book.isborrowed)
		{
			printf("\t\t�����ѱ����\n");
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
		printf("\t\t����ɹ�\n");
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
		printf("\t\t===============����ϵͳ=================\n");
		printf("\t\t�����뻹���ѧ��ѧ��:");
		scanf("%s", studentid);
		studentNode = findstudentnodebyid(studentid);
		if (studentNode == NULL)
		{
			printf("\t\t��ѧ��ѧ�Ų�����\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		printf("\t\t�������鱾�ı��:");
		scanf("\t\t%s", bookid);
		bookNode = findbooknodebyid(bookid);
		if (bookNode == NULL)
		{
			printf("\t\t����δ�ҵ�\n");
			printf("\t\t");
			system("pause");
			return 1;
		}
		if (day_diff(bookNode->book.year, bookNode->book.month, bookNode->book.day,
			getSystemYear(), getSystemMonth(), getSystemDay())>60)
		{
			printf("\t\t�鱾�Ѿ����ڣ���Ҫ���ɴ�����\n");
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
				printf("\t\t����ɹ�\n");
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
		printf("\t\t�������ѯ�鱾����������:");
		scanf("%s", author);
        bookNode = findbooknodebyauthor(author);
		if (bookNode == NULL)
			printf("\t\t�޷���ѯ����ͼ��\n");
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
		printf("\t\t�������ѯ�鱾��רҵ����:");
		scanf("%s", professional_field);

		bookNode = findbooknodebyprofessional_field(professional_field);
		if (bookNode == NULL)
			printf("\t\t�޷���ѯ����ͼ��\n");
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
		printf("\t\t�������ѯѧ����ѧ��:");
		scanf("%s", id);

		studentNode = findstudentnodebyid(id);
		if (studentNode == NULL)
			printf("\t\t�޷���ѯ����ѧ��\n");
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
