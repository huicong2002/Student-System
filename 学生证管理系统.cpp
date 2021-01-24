//学生证管理系统
//作者：冯玉章
//管理员默认密码：123456
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


struct Student {
	int Password;
	char Name[10];
	int Num;
	char Class[20];
};
struct Node {
	struct Student data;
	struct Node* next;
};

struct Node* head=NULL;
struct Node* tail=NULL;

struct Node* Denglu();//登录
struct Node* ZhuCe();//注册
struct Node* AddNode1(struct Node* head);//添加学生信息
struct Node* SearchPassword(struct Node* head,int Password);

void readFile(const char* FileName,struct Node* head);
void CunFile(const char* FileName, struct Node* head);
void AddNode(struct Node* Tempdata, struct Node* head);
void Mune(struct Node* KeyNode);//菜单
void Choose1(struct Node* KeyNode,int Key);//初步选择
void Change(struct Node* KeyNode);//修改学生信息
void ChangeName(struct Node* KeyNode);//修改学生姓名
void ChangeClass(struct Node* KeyNode);//修改学生班级
void ChangeNum(struct Node* KeyNode);//修改学生学号
void ChangePassword(struct Node* KeyNode);//修改学生登陆密码
void Delete(struct Node* KeyNode);//删除学生信息
void SumNode(struct Node* head);//管理员模式
void Print(struct Node* head);//遍历学生信息
void SearchChange(struct Node* head);//修改指定学生成绩
void SearchDelete(struct Node* head);//删除指定学生信息
void SearchAdd(struct Node* head);
void Explain();//帮助
void Exit();//退出
/*************主函数**************/
int main(void)
{
	struct Node* head = NULL;
	readFile("Stuinfro.txt", head);

	struct Node* KeyNode = (struct Node*)malloc(sizeof(struct Node));
	KeyNode = Denglu();
	CunFile("Stuinfro.txt", head);

	while (1)
	{
		Mune(KeyNode);
		CunFile("Stuinfro.txt", head);
		system("cls");
	}
	
	
	Exit();

	return 0;
}
/********************************/
void CunFile(const char* FileName, struct Node* head)//文件存操作
{
	FILE* fp = fopen(FileName, "w");
	struct Node* pMove = head;
	while (pMove)
	{
		fprintf(fp, "%d\t%s\t%s\t", pMove->data.Num, pMove->data.Name, pMove->data.Class);
	}

	fclose(fp);
}
void readFile(const char* FileName,struct Node* head)////文件读操作
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		fp = fopen(FileName, "w+");
	}

	//printf("\t\t\t********************************\t\t\t\n");
	//printf("\t\t\t未检测到当前有学生信息,请在下方添加\t\t\t\n");
	//printf("\t\t\t********************************\t\t\t\n");
	//printf("\t\t\t请输入学生的学号，姓名，班级：\n");

	struct Node* Tempdata = (struct Node*)malloc(sizeof(struct Node));
	while (fscanf(fp, "%d\t%s\t%s\t", &Tempdata->data.Num, Tempdata->data.Name, Tempdata->data.Class) != EOF)
	{
		AddNode(Tempdata, head);
	}

	fclose(fp);
}
void AddNode(struct Node* Tempdata, struct Node* head)//添加新的学生信息
{
	Tempdata->next = NULL;
	if (head == NULL)
	{
		head = Tempdata;
		tail = Tempdata;
	}
	else
	{
		tail = Tempdata;
		tail = Tempdata->next;
	}
}
struct Node* Denglu()//登录
{
	int Password;
	struct Node* KeyNode = (struct Node*)malloc(sizeof(struct Node));

	printf("\t\t\t*****************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*     欢迎来到登录系统      *\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************************\t\t\t\n");
	printf("\n\n");
	printf("\t\t\t请在下方输入你的登录密码：\t\t\t\n");
	scanf("%d", &Password);
	if (SearchPassword(head,Password) == NULL)
	{
		KeyNode = ZhuCe();
		return KeyNode;
	}
	else
	{
		KeyNode = SearchPassword(head, Password);
		printf("\n");
		printf("\t\t\t您已成功登录，请稍等！\t\t\t\n");
		return KeyNode;
	}

	
}
struct Node* ZhuCe()//注册
{
	system("cls");

	int Key;
	struct Node* KeyNode = (struct Node*)malloc(sizeof(struct Node));

	printf("\t\t\t*****************************\t\t\t\n");
	printf("\t\t\t未查到密码信息，请问需要注册吗？\t\t\t\n");
	printf("\t\t\t*****************************\t\t\t\n");
	printf("\n");
	printf("\t\t\t*****************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t          1.需要注册          \t\t\t\n");
	printf("\t\t\t          2.不需要注册        \t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************************\t\t\t\n");
	printf("\t\t\t请输入您的指令：\t\t\t\n");
	scanf("%d", &Key);
	if (Key == 1)
	{
		KeyNode = AddNode1(head);
		return KeyNode;
	}
	else
	{
		Exit();
	}
}
void Mune(struct Node* KeyNode)//菜单
{
	system("cls");

	int Key1;

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*            菜单            *\t\t\t\n");
	printf("\t\t\t*        1.修改学生信息      *\t\t\t\n");
	printf("\t\t\t*        2.删除学生信息      *\t\t\t\n");
	printf("\t\t\t*        3.进入管理员模式    *\t\t\t\n");
	printf("\t\t\t*        4.退出系统          *\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t*****************************\t\t\t\n");
	printf("\t\t\t请在下方输入您的指令（1/2/3/4/5/6）：\t\t\t\n");
	scanf("%d", &Key1);
	Choose1(KeyNode, Key1);
}
struct Node* AddNode1(struct Node* head)//注册学生信息并返回该学生信息
{
	system("cls");

	int Key;
	struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
	NewNode->next = NULL;

	printf("\t\t\t***********************************************\t\t\t\n");

	printf("\t\t\t请在下方依次输入学生的姓名，班级，学号:\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	scanf("%s", NewNode->data.Name);
	scanf("%s", NewNode->data.Class);
	scanf("%d", &NewNode->data.Num);
	printf("\t\t\t请输入您的密码:\t\t\t\n");
	scanf("%d", &NewNode->data.Password);
	
	while (1)
	{
		
		printf("\t\t\t请问您是否确认?(1/2)\t\t\t\n");
		printf("\t\t\t1.是\t\t\t\n");
		printf("\t\t\t2.否\t\t\t\n");
		scanf("%d", &Key);
		if (Key == 2)
		{
			printf("\t\t\t请重新输入\t\t\t\n");
		}
		else if (Key == 1)
		{
			break;
		}
		else
		{
			Exit();
		}
	}
	if ( head == NULL)
	{
		head = NewNode;
		tail = NewNode;
	}
	else
	{
		tail->next = NewNode;
		tail = NewNode;
	}
 
	return NewNode;
}
void Choose1(struct Node* KeyNode,int Key)//主选择
{
	switch (Key)
	{
		case 1:
			Change(KeyNode);
			break;
		case 2:
			Delete(KeyNode);
			break;
		case 3:
			SumNode(head);
			break;
		default:
			Exit();
	}
}
struct Node* SearchPassword(struct Node* head, int Password)//查找密码，信息是否注册
{
	struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));
	pMove = head;
	while (pMove)
	{
		if (pMove->data.Password == Password)
		{
			return pMove;
		}
		pMove = pMove->next;
	}
	return NULL;
}
void Change(struct Node* KeyNode)
{
	system("cls");

	int Key;

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请问您需要修改您的那些信息：\t\t\t\n");
	printf("\t\t\t1.学生姓名\t\t\t\n");
	printf("\t\t\t2.学生班级\t\t\t\n");
	printf("\t\t\t3.学生学号\t\t\t\n");
	printf("\t\t\t4.登陆密码\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");
	printf("\t\t\t请在下方输入您的选择(1/2/3/4)：\t\t\t\n");
	scanf("%d", &Key);
	switch (Key)
	{
		case 1:
			ChangeName(KeyNode);
			break;
		case 2:
			ChangeClass(KeyNode);
			break;
		case 3:
			ChangeNum(KeyNode);
			break;
		case 4:
			ChangePassword(KeyNode);
			break;
		default:
			Exit();
	}
}
void ChangeName(struct Node* KeyNode)
{
	system("cls");

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请在下方输入修改后的数据\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");
	

	scanf("%s", KeyNode->data.Name);

}
void ChangeClass(struct Node* KeyNode)
{
	system("cls");

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请在下方输入修改后的数据\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");

	scanf("%s", KeyNode->data.Class);

}
void ChangeNum(struct Node* KeyNode)
{
	system("cls");

	int Num;

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请在下方输入修改后的数据\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");

	scanf("%d", &Num);
	KeyNode->data.Num = Num;

}
void ChangePassword(struct Node* KeyNode)
{
	system("cls");

	int Password;

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请在下方输入修改后的数据\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");

	scanf("%d", &Password);
	KeyNode->data.Password = Password;

}
void Delete(struct Node* KeyNode)
{
	system("cls");

	int Key;

	printf("\t\t\t******************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t您是否想好删除信息？(1/2)\t\t\t\n");
	printf("\t\t\t1.是\t\t\t\n");
	printf("\t\t\t2.否\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");
	scanf("%d", &Key);
	if (Key == 2)
	{
		return;
	}
	else if (Key == 1)
	{
		if (KeyNode == head)
		{
			head = head->next;
			free(KeyNode);
		}
		else if (KeyNode == tail)
		{
			free(KeyNode);
		}
		else
		{
			struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));
			pMove->next = KeyNode->next;
			free(KeyNode);
			KeyNode = pMove->next;
		}
	}
	else
	{
		Exit();
	}

}
void Exit()
{
	system("cls");

	printf("\n\n\t\t\t******************************\t\t\t\n\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t     系统退出,欢迎下次使用！\t\t\t\n\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t******************************\t\t\t\n");

	system("pause");
	exit(-1);
}
void SumNode(struct Node* head)
{
	system("cls");

	int Password,Key;

	printf("\n\n\t\t\t**************************************\t\t\t\n");
	printf("\t\t\t欢迎来到管理员系统，请在下方输入管理员密码\t\t\t\n");
	printf("\t\t\t**************************************\t\t\t\n");
	scanf("%d", &Password);
	if (Password == 123456)
	{
		printf("\t\t\t密码正确！请在下方输入你的指令。\t\t\t\n");
		printf("\n\n\t\t\t**************************************\t\t\t\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t\t1.查看全部学生信息\t\t\t\n");
		printf("\t\t\t2.修改指定学生信息\t\t\t\n");
		printf("\t\t\t3.删除指定学生信息\t\t\t\n");
		printf("\t\t\t4.指定位置插入学生信息\t\t\t\n");
		printf("\t\t\t5.系统使用说明\t\t\t\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t\t\t**************************************\t\t\t\n");
		
		scanf("%d", &Key);
		switch (Key)
		{
			case 1:
				Print(head);//查看全部学生信息
				break;
			case 2:
				SearchChange(head);//修改指定学生信息
				break;
			case 3:
				SearchDelete(head);//删除指定学生信息
				break;
			case 4:
				SearchAdd(head);//指定位置插入学生信息
			case 5:
				Explain();//系统使用说明
				break;
			default:
				Exit();//退出
				break;
		}
	}
	else
	{
		Exit();
	}
}
void Print(struct Node* head)
{
	system("cls");

	struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));
	pMove = head;
	
	printf("\n\n");
	printf("\t\t\t|_________________________________|\n");
	printf("\t\t\t|        正在查看学员             |\n");
	printf("\t\t\t|_________________________________|\n\n\n");
	printf("\n\n\t\t\t**************************************\t\t\t\n");
	printf("\t\t\t           全体学生信息汇总表           \t\t\t\n");
	printf("\t\t\t**************************************\t\t\t\n");
	printf("\t\t\t学生学号\t学生姓名\t学生班级\t\n");
	while (pMove)
	{
		printf("\t\t\t%d\t%s\t%s\t\n",pMove->data.Num,pMove->data.Name,pMove->data.Class);
		pMove = pMove->next;
	}
	system("pause");
}
void SearchChange(struct Node* head)
{
	system("cls");

	int Num,k=0;
	
	printf("\t\t\t**************************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t     请在下方输入你想修改的学生的学号    \t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t**************************************\t\t\t\n");
	scanf("%d", &Num);

	printf("\n\n");
	printf("\t\t\t|_________________________________|\n");
	printf("\t\t\t|        正在查看学员             |\n");
	printf("\t\t\t|_________________________________|\n");

	struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));

	pMove = head;
	while (pMove)
	{
		if (pMove->data.Num == Num)
		{
			k = 1;
			Change(pMove);
			break;
		}
	}
	if (k == 0)
	{
		printf("未查到此学号的学生！");
	}
}
void SearchDelete(struct Node* head)
{
	system("cls");

	int Num, k = 0;

	printf("\t\t\t**************************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t     请在下方输入你想修改的学生的学号    \t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t**************************************\t\t\t\n");
	scanf("%d", &Num);

	printf("\n\n");
	printf("\t\t\t|_________________________________|\n");
	printf("\t\t\t|        正在查看学员             |\n");
	printf("\t\t\t|_________________________________|\n");

	struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));

	pMove = head;
	while (pMove)
	{
		if (pMove->data.Num == Num)
		{
			k = 1;
			Delete(pMove);
			break;
		}
	}
	if (k == 0)
	{
		printf("未查到此学号的学生！");
	}
}
void SearchAdd(struct Node* head)
{
	system("cls");

	int Num,k;

	printf("\t\t\t**************************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t   请在下方输入你想插入位置的学生的学号    \t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t**************************************\t\t\t\n");
	scanf("%d", &Num);

	printf("\n\n");
	printf("\t\t\t|_________________________________|\n");
	printf("\t\t\t|        正在查看学员             |\n");
	printf("\t\t\t|_________________________________|\n");

	struct Node* pMove = (struct Node*)malloc(sizeof(struct Node));

	pMove = head;
	while (pMove)
	{
		if (pMove->data.Num == Num)
		{
			k = 1;
			printf("已找到该学生！");
			break;
		}
	}
	if (k == 0)
	{
		printf("未查到此学号的学生！");
		Exit();
	}

	system("cls");

	struct Node* Tempdata = (struct Node*)malloc(sizeof(struct Node));
	struct Node* tempdata = (struct Node*)malloc(sizeof(struct Node));
	printf("\n\n");
	printf("\t\t\t**************************************\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t请在下方输入你想插入学生的姓名，班级，学号\t\t\t\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t**************************************\t\t\t\n");

	scanf("\t\t\t%s%s%d\t\t\t\n", Tempdata->data.Name, Tempdata->data.Class, &Tempdata->data.Num);

	tempdata = pMove->next;
	pMove->next = Tempdata;
	Tempdata->next = tempdata;

	printf("已插入成功！");

}
void Explain()
{
	system("cls");

	printf("\n\n");
	printf("\t\t\t\t**********************\t\t\t\n");
	printf("\t\t\t\t欢迎来到本系统使用说明         \t\t\t\n");
	printf("\t\t\t\t**********************\t\t\t\n");
	printf("\n");
	printf("\t\t\t本系统旨在为师生提供学生证信息及其信息的管理\t\t\t\n\n");
	printf("\t\t\t使用者需登录方可使用（全体师生都需要登录）\t\t\t\n\n");
	printf("\t\t\t如果未提前注册，则需注册后，方可登陆成功\t\t\t\n\n");
	printf("\t\t\t登陆后，学生可以修改或者注销自己的个人信息\t\t\t\n\n");
	printf("\t\t\t如果为系统的管理员，则可输入密码进入管理员系统\t\t\t\n\n");
	printf("\t\t\t管理员系统的默认密码为123456，如需更改，需要到学校教务处进行更改\t\t\t\n\n");
	printf("\t\t\t登陆后，管理员可以选择查看全体学生信息或者删除，修改\t\t\t\n\n");
	printf("\t\t\t所有信息一旦注册，均会保存在数据库中\t\t\t\n\n");
	printf("\t\t\t如有更好的建议及意见，欢迎来教务处\t\t\t\n\n");
	printf("\t\t\t最后，如有bug，请立刻联络相关人员\t\t\t\n\n");
	
	system("pause");
}
