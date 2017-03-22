#include"head.h"
void printStudent(struct Student* student)
{
	int i;
	printf("\t\t===============ѧ���б�=================\n");
	printf("\t\tѧ����ţ�%s   <--------\n", student->id);
	printf("\t\t������%s\n", student->name);
	printf("\t\t�Ա�%s\n", student->sex);
	printf("\t\t����������%d\n", student->borrown);
	printf("\t\t�鱾���Ϊ��");
	for (i = 0; i<student->borrown; i++)
	{
		printf("        %s\n", student->borrow_id[i]);
	}
	printf("\n");
}
void printStudentNode(struct StudentNode* studentNode)
{
	printStudent(&studentNode->student);
}
//��ӡ����ѧ����Ϣ
void printAllStudent()
{
	struct StudentNode* cur = studentroot;
	while (1)
	{
		if (cur == NULL)
			break;
		printStudentNode(cur);
		cur = cur->next;
	}
}
//���ѧ��
void addStudent(char id[], char name[], char sex[], int borrown, char borrow_id[][105])
{
	int i;
	struct StudentNode* studentNode;
	struct Student* student = (struct Student*) malloc(sizeof(struct Student) * 1);
	strcpy(student->id, id);
	strcpy(student->name, name);
	strcpy(student->sex, sex);
	student->borrown = borrown;
	for (i = 0; i<borrown; i++)
	{
		strcpy(student->borrow_id[i], borrow_id[i]);
	}

	studentNode = (struct StudentNode*) malloc(sizeof(struct StudentNode) * 1);
	studentNode->student = (*student);
	studentNode->next = NULL;

	if (studentroot == NULL)
	{
		studentroot = studentNode;
	}
	else
	{
		struct StudentNode* cur = studentroot;
		while (1)
		{
			if (cur->next == NULL)
			{
				cur->next = studentNode;
				break;
			}
			cur = cur->next;
		}
	}
}
//����ѧ���Ų���
struct StudentNode* findstudentnodebyid(char id[])
{
	struct StudentNode* cur = studentroot;
	while (1)
	{
		if (cur == NULL)
			break;
		if (strcmp(cur->student.id, id) == 0)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//����ѧ����Ϣ
void saveStudent()
{
	FILE* fp = fopen("student.txt", "w");
	if (fp == NULL)
	{
		printf("���ܴ򿪴��ļ�\n");
		exit(EXIT_FAILURE);
	}
	struct StudentNode* cur = studentroot;
	while (1)
	{
		if (cur == NULL)
			break;
		else
		{
			int i;
			fprintf(fp, "%s\n", cur->student.id);
			fprintf(fp, "%s\n", cur->student.name);
			fprintf(fp, "%s\n", cur->student.sex);
			fprintf(fp, "%d\n", cur->student.borrown);
			for (i = 0; i<cur->student.borrown; i++)
			{
				fprintf(fp, "%s\n", cur->student.borrow_id[i]);
			}
			cur = cur->next;
		}
	}
	fclose(fp);
}
//��ȡѧ����Ϣ
void readStudent()
{
	char id[105];
	char name[105];
	char sex[105];
	int borrown;
	char borrow_id[15][105];
	char tem[105];
	FILE* fp = fopen("student.txt", "r");
	studentroot = NULL;
	if (fp == NULL)
	{
		printf("���ܴ򿪴��ļ�\n");
		exit(EXIT_FAILURE);
	}
	while (fgets(id, 105, fp) != NULL)
	{
		int i;
		id[strlen(id) - 1] = '\0';
		fgets(name, 105, fp);
		name[strlen(name) - 1] = '\0';
		fgets(sex, 105, fp);
		sex[strlen(sex) - 1] = '\0';
		fgets(tem, 105, fp);
		borrown = atoi(tem);
		for (i = 0; i<borrown; i++)
		{
			fgets(borrow_id[i], 105, fp);
			borrow_id[i][strlen(borrow_id[i]) - 1] = '\0';
		}
		addStudent(id, name, sex, borrown, borrow_id);
	}
}
//ɾ��ѧ����Ϣ
void deleteStudent(char id[])
{
	struct StudentNode* find = findstudentnodebyid(id);
	if (find == NULL)
	{
		printf("\t\t��ѧ��������\n");
		return;
	}

	if (find == studentroot)
	{
		studentroot = studentroot->next;
		printf("\t\tɾ���ɹ�\n");
	}
	else
	{
		struct StudentNode* cur = studentroot;
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
//�޸�ѧ����Ϣ
void editStudent()
{
	char id[105];
	char name[105];
	char sex[105];
	printf("\t--------------------------------------------------\n");
	printf("\t������Ҫ�޸ĵ�ѧ����:");
	scanf("%s", id);
	struct StudentNode* find = findstudentnodebyid(id);
	if (find == NULL)
	{
		printf("\t��ѧ��������\n");
		return;
	}
	printf("\t����������:");
	scanf("%s", name);
	printf("\t�������Ա�:");
	scanf("%s", sex);
	strcpy(find->student.id, id);
	strcpy(find->student.name, name);
	strcpy(find->student.sex, sex);
	printf("\t�޸ĳɹ�\n");
}
 