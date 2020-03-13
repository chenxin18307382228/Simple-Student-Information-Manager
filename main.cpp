#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#define StudentList element
#define new_student new_element
using namespace std;
ofstream outfile;
ofstream ouf;
//定义stu链表，head为首地址 
struct stu
{
	int id;              //id为学生学号 
	char name[100];      //name为学生姓名 
	int score;           //score为学生成绩 
	stu* next;           //next用于形成链表 
};
//建立“学生”类 
class student
{
private:
	stu* head;
public:
	//num统计学生数量
	int num=0;
	//构造函数
	student(stu* list_head) { head = list_head; }
	int set();
	void find();
	void change();
	int del();
	int add();
	void sort(int);
	void view(int);
	void GradeTable();
	//析构函数--释放动态存储空间
	~student() 
	{
		stu* p = head;
		while (p != NULL)
		{
			head = p->next;
			delete p;
			p = head;
		}
		p = head = NULL;
	}
};
//set--建立初始学生数据
int student::set()
{
	int num = 0;           //num用于计学生个数 
	stu* StudentList1, * StudentList2;
	head = NULL;
	StudentList1 = new stu;
	StudentList2 = head;
	cout << "请输入第1个学生的信息（当学号为0是终止）:\n";
	cin >> StudentList1->id >> StudentList1->name >> StudentList1->score;
	if (StudentList1->id == 0)        //如果输入学生学号为0，则输入错误，跳出函数 
	{
		return 0;
	}
	num++;
	while (StudentList1->id != 0)     //当输入0时结束建立 
	{
		num++;
		if (head == NULL)
		{
			head = StudentList1;
		}
		else
		{
			StudentList2->next = StudentList1;
		}
		StudentList2 = StudentList1;
		StudentList1 = new stu;
		cout << "请输入第" << num << "个学生的信息（当学号为0时终止）:\n";
		cin >> StudentList1->id >> StudentList1->name >> StudentList1->score;
	}
	StudentList2->next = NULL;
	StudentList1 = head;
	cout << "建立成功！\n";
	while (StudentList1 != NULL)
	{
		outfile << StudentList1->id << '\t' << StudentList1->name << '\t' << StudentList1->score << endl << endl;
		StudentList1 = StudentList1->next;
	}
	outfile << "------------------------------------------------------\n";
	return num;           //返回学生数量num 
}
//find--根据学号查找学生信息
void student::find()
{
	int ID, choice;
	char Name[20];
	stu* StudentList = head;
	int n=0;
	cout << "您想通过哪一项信息查找？\n";
	cout << "|1 学号    |\n";
	cout << "|2 姓名    |\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "请输入学号：\n";
		cin >> ID;
		while (StudentList != NULL)
		{
			n++;
			if (StudentList->id == ID)
			{
				cout << "学生信息如下：\n";
				cout << n << '\t' << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << '\n' << endl;
				break;
			}
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	case 2:
		cout << "请输入姓名：\n";
		cin >> Name;
		while (StudentList != NULL)
		{
			n++;
			if(strcmp(StudentList->name,Name)==0)
			{
				cout << "学生信息如下：\n";
				cout << n << '\t' << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << '\n' << endl;
				break;
			}
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	default:
		cout << "Error!!\n";
		break;
	}
	return;
}
//change--修改学生信息
void student::change()
{
	stu* StudentList =head, new_student;
	int choice,change_choice,ID, check=0;
	char Name[20];
	cout << "首先，您想通过哪一项信息查找？\n";
	cout << "|1 学号    |\n";
	cout << "|2 姓名    |\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		check = 1;
		cout << "请输入学号：\n";
		cin >> ID;
		while (StudentList != NULL && StudentList->id != ID)
		{
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	case 2:
		check = 1;
		cout << "请输入姓名：\n";
		cin >> Name;
		while (StudentList != NULL && strcmp(StudentList->name, Name) != 0)
		{
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	default:
		cout << "Error!!\n";
		break;
	}
	if(StudentList != NULL && check == 1)
	{
		cout << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << '\n' << endl;
		cout << "你希望修改学生的哪一项信息 ? :\n";
		cout << "|1  学号   |\n";
		cout << "|2  姓名   |\n";
		cout << "|3  成绩   |\n";
		cin >> change_choice;
		switch (change_choice)
		{
		case 1:
			cout << "请输入新学号: ";
			cin >> new_student.id;
			cout << "结果:\n";
			StudentList->id = new_student.id;
			cout << "修改成功!\n";
			break;
		case 2:
			cout << "请输入新姓名: ";
			cin >> new_student.name;
			cout << "结果:\n";
			strcpy(StudentList->name, new_student.name);
			cout << "修改成功 !\n";
			break;
		case 3:
			cout << "请输入新成绩: ";
			cin >> new_student.score;
			cout << "结果:\n";
			StudentList->score = new_student.score;
			cout << "修改成功!\n";
			break;
		}
		cout << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << '\n' << endl;
	}
	return;
}
//del--删除学生信息
int student::del()
{
	int n = 0,choice,ID,check=0;
	char Name[20];
	stu* StudentList = head, * StudentList2 = head;
	cout << "结果:\n";
	cout << "首先，您想通过哪一项信息查找？\n";
	cout << "|1 学号    |\n";
	cout << "|2 姓名    |\n";
	cin >> choice;
	switch (choice)
	{
	case 1:
		check = 1;
		cout << "请输入学号：\n";
		cin >> ID;
		while (StudentList != NULL && StudentList->id != ID)
		{
			StudentList2 = StudentList;
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	case 2:
		check = 1;
		cout << "请输入姓名：\n";
		cin >> Name;
		while (StudentList != NULL && strcmp(StudentList->name, Name) != 0)
		{
			StudentList2 = StudentList;
			StudentList = StudentList->next;
		}
		if (StudentList == NULL)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	default:
		cout << "Error!!\n";
		break;
	}
	if(StudentList!=NULL&&check==1)
	{
		cout << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << '\n' << endl;
		cout << "删除成功 !\n";
		if (StudentList == head)
		{
			head = head->next;
		}
		else
		{
			StudentList2->next = StudentList->next;
		}
		delete StudentList;
	}
	return n;
}
//add--增加学生
int student::add()
{
	int n = 0;
	stu* StudentList = head, * new_student;
	new_student = new stu;
	cout << "请输入你所要添加的学生的信息:\n";
	cin >> new_student->id >> new_student->name >> new_student->score;
	while (StudentList->next != NULL)
	{
		StudentList = StudentList->next;
	}
	StudentList->next = new_student;
	new_student->next = NULL;
	cout << "添加成功！\n";
	return n;
}
//sort--对学生成绩排名
void student::sort(int num)
{
	stu* StudentList1 = head, * StudentList2 = head->next;
	int t_id = 0, t_score = 0, n = 1;
	char t_name[10]="000";
	cout << "结果:\n";
	for (int i=0;i<num-1;i++)
	{
		StudentList1 = head, StudentList2 = StudentList1->next;
		for (int j = 0; j < num - i - 1&&StudentList2!=NULL;j++)
		{
			if (StudentList1->score < StudentList2->score&&StudentList2!=NULL)
			{
				//学号对换 
				t_id = StudentList1->id;
				StudentList1->id = StudentList2->id;
				StudentList2->id = t_id;
				//名字对换
				strcpy(t_name, StudentList1->name);
				strcpy(StudentList1->name, StudentList2->name);
				strcpy(StudentList2->name, t_name);
				//成绩对换
				t_score = StudentList1->score;
				StudentList1->score = StudentList2->score;
				StudentList2->score = t_score;
			}
			StudentList1 = StudentList1->next;
			StudentList2 = StudentList1->next;
		}
	}
	StudentList1 = head;
	while (StudentList1 != NULL)
	{
		cout.setf(ios::left);
		outfile.setf(ios::left);
		cout <<setw(12)<<n << setw(12) << StudentList1->id << setw(12) << StudentList1->name << setw(12) << StudentList1->score << '\n' << endl << endl;
		outfile << setw(12) <<n << setw(12) << StudentList1->id << setw(12) << StudentList1->name << setw(12) << StudentList1->score << '\n' << endl << endl;
		n++;
		StudentList1 = StudentList1->next;
	}
	outfile << "---------------------------------------------------------" << endl;
	return;
}
//view--总览所有学生信息
void student::view(int num)
{
	stu* StudentList = head;
	int n = 0;
	while (StudentList != NULL)
	{
		n++;
		cout.setf(ios::left);
		outfile.setf(ios::left);
		cout <<setw(12)<<n << setw(12) << StudentList->id << setw(12) << StudentList->name << setw(12) << StudentList->score << '\n' << endl << endl;
		outfile << setw(12) <<n << setw(12) << StudentList->id << setw(12) << StudentList->name << setw(12) << StudentList->score << '\n' << endl << endl;
		StudentList = StudentList->next;
	}
	cout << "                                                             人数：" << num << endl;
	outfile << "                                                             人数：" << num << endl;
	outfile << "---------------------------------------------------------" << endl;
	return;
}
//GradeTable--打印成绩表
void student::GradeTable()
{
	ouf.setf(ios::left);
	sort(num);
	num = 0;
	stu* StudentList = head;
	ouf.open("GradeTable.txt", ios_base::out);
	ouf << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n';
	while (StudentList != NULL)
	{
		num++;
		ouf << setw(12) << num << setw(12) << StudentList->id << setw(12) << StudentList->name << setw(12) << StudentList->score << '\n';
		ouf << "--------------------------------------------------------------------------------------------------\n";
		StudentList = StudentList->next;
	}
	ouf.close();
}
int main()
{
	cout << "--------------------欢迎使用学生信息统计系统----------------------\n" << endl;
	system("pause");
	int your_choice, stop, num=0;
	stu* list_head=NULL;
	stu* StudentList = list_head;
	student run(list_head);//用run调用student类的成员函数 
	outfile.open("student.txt", ios_base::out);//每次打开程序，都会自动清空student.txt中的旧内容，在向其中输入新内容 
	if (!outfile)
	{
		cout << "抱歉，输出文件建立失败!\n";
		exit(1);
	}
	cout << "*********************现在建立初始学生信息**********************\n";
	while (StudentList == NULL)
	{
		cout << endl;
		num = run.set();
		if (num == 0)
		{
			cout << "学生信息建立失败！是否重新建立？(输入“1”建立)\n";
			cin >> your_choice;
			if (your_choice == 1)
			{
				cout << "现在开始重新建立：\n";
				continue;
			}
			else
			{
				exit(0);
			}
		}
		else
		{
			break;
		}
	}
	run.sort(num);
	while (true)
	{
		system("pause");
		cout << "请选择你的操作（输入操作名前的序号）:\n";
		cout << " | 1  查找   |\n";
		cout << " | 2  修改   |\n";
		cout << " | 3  删除   |\n";
		cout << " | 4  添加   |\n";
		cout << " | 5  总览   |\n";
		cout << " | 0  离开   |\n";
		cin >> your_choice;
		cout << " _________________________________________________________________________________________________\n";
		switch (your_choice)
		{
		case 1:
			run.find();
			break;
		case 2:
			run.change();
			break;
		case 3:
			num = run.del();
			break;
		case 4:
			num = run.add();
			break;
		case 5:
			run.view(num);
			break;
		default:
			if (your_choice == 0)
			{
				break;
			}
			else
			{
				cout << "错误操作!!\n";
				continue;
			}
		}
		if (your_choice == 0)
		{
			cout << "确定???\n";
			cout << " 再次输入0继续:";
			cin >> stop;
			if (stop == 0)
			{
				break;
			}
		}
	}
	outfile.close();
	cout << "是否需要打印成绩排名表？（表格格式为txt，打印请输入1	）\n";
	cin >> your_choice;
	if (your_choice == 1)
	{
		run.GradeTable();
	}
	return 0;
}
