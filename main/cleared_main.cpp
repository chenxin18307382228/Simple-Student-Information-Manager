#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
using namespace std;
//定义stu链表，head为头指针 
struct stu
{
	int id;              //id为学生学号 
	char name[100];      //name为学生姓名 
	int score;           //score为学生成绩 
	stu* next;           //next用于形成链表 
};
//交换函数
void swap(stu* Student1, stu* Student2)
{
	int t_id = 0, t_score = 0;
	char t_name[10] = "000";
	//学号对换 
	t_id = Student1->id;
	Student1->id = Student2->id;
	Student2->id = t_id;
	//名字对换
	strcpy(t_name, Student1->name);
	strcpy(Student1->name, Student2->name);
	strcpy(Student2->name, t_name);
	//成绩对换
	t_score = Student1->score;
	Student1->score = Student2->score;
	Student2->score = t_score;
}
//建立“学生”类 
class student
{
private:
	int num;       //用于统计学生数量
	stu* head;     //头指针
	stu* tail;     //尾指针
public:
	//构造函数
	student(stu* list_head) { tail = head = list_head; num = 0; }
	bool read();                 //读取文件数据以建立链表
	int set(stu);                  //建立初始学生信息
	stu* find(int);                //根据学号查找指定学生信息
	stu* find(char*);//根据名字查找
	void change(stu*, int);              //修改指定学生的学号
	void change(stu*, char*);        //修改指定学生的姓名
	void change(int, stu*);
	void del(stu*);                 //删除指定学生信息
	void all_del();             //全部删除
	void add(stu);                 //添加新学生信息
	void sort(stu*, stu*);      //对学生信息依据成绩排序
	void view();                //信息总览
	void invert();              //倒序
	void GradeTable();          //打印成绩表
	void save();                //保存学生信息
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
		delete head;
	}
};
bool student::read()
{
	bool check = 0;
	stu* StudentList1, * StudentList2;
	head = NULL;
	StudentList2 = head;
	ifstream infile("student.txt");     //student.txt为学生信息存出文件，通过读取此文件，可直接获取学生信息
	if (!infile)
	{
		cout << "请先建立 student.txt 文件!" << endl;
		system("pause");
		exit(-1);
	}
	int id, score;           //id和score的中转变量
	char name[20];           //name的中转变量
	StudentList1 = new stu;  //首次动态分配空间
	while (infile.peek() != EOF)   //遍历student.txt数据
	{
		num++;
		infile >> id >> name >> score;       //为中转变量赋值
		//为链表成员变量赋值
		StudentList1->id = id;
		strcpy(StudentList1->name, name);
		StudentList1->score = score;
		//判断头指针是否为空，若为空，则从头开始赋值，否则从末端开始赋值
		if (head == NULL)
		{
			head = StudentList1;
		}
		else
		{
			StudentList2->next = StudentList1;
		}
		StudentList2 = StudentList1;           //StudentList2向前移动
		StudentList1 = new stu;                //继续动态分配空间
	}
	delete StudentList1;
	//若从文件中读取出数据
	if (head != NULL)
	{
		StudentList2->next = NULL;     //结束建立链表进程
		check = 1;
	}
	//标注尾指针
	tail = StudentList2;
	infile.close();
	//判断之前通过文件流建立链表是否成功，若成功，结束函数，返回链表长度num，反之开始初次建立链表（手动输入）
	return check;
}
//set--建立初始学生信息
int student::set(stu new_student)
{
	stu* StudentList1, * StudentList2=tail;
	StudentList1 = new stu;
	num = 1;
	StudentList1->id = new_student.id;
	strcpy(StudentList1->name, new_student.name);
	StudentList1->score = new_student.score;
	if (head == NULL)
	{
		head = StudentList1;
	}
	else
	{
		StudentList2->next = StudentList1;
	}
	StudentList2 = StudentList1;
	tail = StudentList2;
	tail->next = NULL;
	num++;
	return num;
}
//find--根据学号查找指定学生信息
stu* student::find(int id)
{
	stu* temp = head;
	for (; temp != NULL; temp = temp->next)
	{
		if (temp->id == id)
		{
			return temp;
		}
	}
	return temp;
}
//find--根据姓名查找
stu* student::find(char* name)
{
	stu* temp = head;
	for (; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->name, name) == 0)
		{
			return temp;
		}
	}
	return temp;
}
//change--修改学生学号
void student::change(stu *temp, int id)
{
	stu* StudentList = head;
	for (; StudentList != NULL; StudentList = StudentList->next)
	{
		if (StudentList == temp)
		{
			StudentList->id = id;
		}
	}
	return;
}
//change--修改学生姓名
void student::change(stu* temp, char* name)
{
	stu* StudentList = head;
	for (; StudentList != NULL; StudentList = StudentList->next)
	{
		if (StudentList == temp)
		{
			strcpy(StudentList->name, name);
		}
	}
        return;
}
//change--修改学生成绩
void student::change(int score, stu* temp)
{
	stu* StudentList = head;
	for (; StudentList != NULL; StudentList = StudentList->next)
	{
		if (StudentList == temp)
		{
			StudentList->score = score;
		}
	}
	sort(head, tail);
	return;
}
//del--删除学生信息
void student::del(stu* temp)
{
	stu* StudentList1 = head, * StudentList2 = head->next;
	if (temp == head)
	{
		head = head->next;
		delete StudentList1;
		return;
	}
	for (; StudentList2 != NULL; StudentList1 = StudentList1->next, StudentList2 = StudentList2->next)
	{
		if (StudentList2 == temp)
		{
			StudentList1 = StudentList2->next;
			delete StudentList2;
		}
	}
	tail = StudentList1;
	return;
}
//all_del--全体删除
void student::all_del()
{
	stu* p = head;
	while (p != NULL)
	{
		num--;
		head = p->next;
		delete p;
		p = head;
	}
	delete p;
	cout << "删除成功！\n";
	tail = NULL;
	return;
}
//add--增加学生
void student::add(stu new_student)
{
	stu* StudentList = new stu;
	//赋值
	StudentList->id = new_student.id;
	strcpy(StudentList->name, new_student.name);
	StudentList->score = new_student.score;
	//标注尾指针
	if (head == NULL)
	{
		tail = head = StudentList;
		tail->next = NULL;
		return;
	}
	tail->next = StudentList;
	StudentList->next = NULL;
	tail = StudentList;
	sort(head, tail);
	return;
}
//sort--对学生成绩进行排名（快速排序）
void student::sort(stu* head, stu* tail)
{
	if (head == tail || head == NULL || head == tail->next)
	{
		return; // 递归出口
	}
	stu* StudentList1, * StudentList2, * key;
	StudentList1 = StudentList2 = key = head;
	while (StudentList2 != tail)
	{
		StudentList2 = StudentList2->next; // 对于一个链表只遍历一遍
		if (StudentList2->score > head->score)
		{
			// 如果StudentList2的值大于key则放在左边
			key = StudentList1;
			StudentList1 = StudentList1->next;
			swap(StudentList1, StudentList2);
		}
	}
	/*
	执行while完毕后的情况：
	key在head,[head->next,StudentList1]大于key,[StudentList2->next,tail]小于key
	*/
	swap(head, StudentList1);
	sort(head, key);
	sort(StudentList1->next, tail);
	return;
}
//view--总览所有学生信息
void student::view()
{
	cout << "结果：\n";
	int n;                   //用于记录名次
	stu* StudentList1 = head;
	cout.setf(ios::left);
	cout << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
	for (n = 1; StudentList1 != NULL; n++)
	{
		cout << setw(12) << n << setw(12) << StudentList1->id << setw(12) << StudentList1->name << setw(12) << StudentList1->score << '\n' << endl;
		StudentList1 = StudentList1->next;
	}
	cout << "                                                              人数：" << n - 1 << endl;
	return;
}
//invert--倒序
void student::invert()
{
	stu* StudentList1 = head, * StudentList2;
	head = StudentList1->next;
	StudentList1->next = NULL;
	StudentList2 = StudentList1;
	tail = StudentList1;
	while (head->next != NULL)
	{
		StudentList1 = head;
		head = head->next;
		StudentList1->next = StudentList2;
		StudentList2 = StudentList1;
	}
	head->next = StudentList2;
}
//GradeTable--打印成绩表
void student::GradeTable()
{
	ofstream ouf;       //用于打印成绩表
	ouf.setf(ios::left);
	sort(head, tail);
	stu* StudentList = head;
	ouf.open("GradeTable.txt", ios_base::out);
	if (!ouf)
	{
		cout << "抱歉，输出文件建立失败，您可以手动建立GradeTable.txt\n";
		system("pause");
		exit(1);
	}
	ouf << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n';
	for (int n = 0; StudentList != NULL; n++)
	{
		;
		ouf << setw(12) << n << setw(12) << StudentList->id << setw(12) << StudentList->name << setw(12) << StudentList->score << '\n';
		ouf << "--------------------------------------------------------------------------------------------------\n";
		StudentList = StudentList->next;
	}
	ouf.close();
	return;
}
//save--保存学生信息
void student::save()
{
	ofstream outfile;   //用于保存信息
	outfile.open("student.txt");//每次打开程序，都会自动清空student.txt中的旧内容，在向其中输入新内容 
	if (!outfile)
	{
		cout << "抱歉，输出文件建立失败!您可以手动建立student.txt\n";
		system("pause");
		exit(1);
	}
	stu* StudentList = head;
	if (head != NULL)
	{
		while (StudentList->next != NULL)
		{
			outfile << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score << endl;
			StudentList = StudentList->next;
		}
		outfile << StudentList->id << '\t' << StudentList->name << '\t' << StudentList->score;
	}
	outfile.close();       //关闭存储文件
	return;
}
#define choose_id 1
#define choose_name 2
#define choose_score 3
#define Error default             //输入错误
#define choose_find 1
#define choose_change 2
#define choose_del 3
#define choose_all_del 4
#define choose_add 5
#define choose_view 6
#define choose_invert 7
#define choose_exit 0
#define print 1
#define Save 1
int main()
{
	cout << "--------------------欢迎使用学生信息统计系统----------------------\n" << endl;
	int your_choice, stop; //your_choice可用于选择是否重新建立链表、选择操作、选择是否保存、选择是否打印成绩表 
	bool check = 0;
	stu new_student;
	stu* list_head = NULL;          //链表头指针
	student run(list_head);//创建student对象run
	//建立链表
	check = run.read();
	//判断手动建立链表是否出错
	if (check == 0)
	{
		int n = 1;
		your_choice = 1;
		cout << "*********************现在建立初始学生信息**********************\n";
		while (your_choice != 0)
		{
			cout << "请输入第"<<n<<"个学生信息：\n";
			cin >> new_student.id >> new_student.name >> new_student.score;
			run.set(new_student);
			n++;
			cout << "是否继续？（是--1，否--0）？\n";
			cin >> your_choice;
		}
	}
	//开始进行各项操作
	stu* result = NULL;
	int id, score;
	char name[20];
	while (true)
	{
		system("pause");
		cout << "请选择你的操作（输入操作名前的序号）:\n";
		cout << " | 1  查找   |\n";
		cout << " | 2  修改   |\n";
		cout << " | 3  删除   |\n";
		cout << " | 4  全删   |\n";
		cout << " | 5  添加   |\n";
		cout << " | 6  总览   |\n";
		cout << " | 0  离开   |\n";
		cin >> your_choice;
		cout << " _________________________________________________________________________________________________\n";
		switch (your_choice)
		{
		case choose_find:
			cout << "您想通过哪一项信息查找？\n";
			cout << "|1 学号    |\n";
			cout << "|2 姓名    |\n";
			cin >> your_choice;
			switch (your_choice)
			{
			case choose_id:
				cout << "输入该学生学号：\n";
				cin >> id;
				result = run.find(id);
				if (result != NULL)
				{
					cout << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
					cout << setw(12) << result->id << setw(12) << result->name << setw(12) << result->score << endl;
					break;
				}
				cout << "抱歉，未找到此学生信息\n";
				cout << "或许，你可以通过“添加”功能新建学生信息\n";
				break;
			case choose_name:
				cout << "输入该学生的姓名：\n";
				cin >> name;
				result = run.find(name);
				if (result != NULL)
				{
					cout << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
					cout << setw(12) << result->id << setw(12) << result->name << setw(12) << result->score << endl;
					break;
				}
				cout << "抱歉，未找到此学生信息\n";
				cout << "或许，你可以通过“添加”功能新建学生信息\n";
				break;
			Error:
				cout << "Error!!\n";
				break;
			}
			break;
		case choose_change:
			cout << "首先，您想通过哪一项信息查找？\n";
			cout << "|1 学号    |\n";
			cout << "|2 姓名    |\n";
			cin >> your_choice;
			switch (your_choice)
			{
			case choose_id:
				cout << "输入该学生学号：\n";
				cin >> id;
				result = run.find(id);
				break;
			case choose_name:
				cout << "输入该学生的姓名：\n";
				cin >> name;
				result = run.find(name);;
				break;
			Error:
				cout << "Error!!\n";
				break;
			}
			if (result == NULL)
			{
				cout << "抱歉，未找到此学生信息\n";
				cout << "或许，你可以通过“添加”功能新建学生信息\n";
				break;
			}
			cout << "您希望修改哪项信息？\n";
			cout << "|1  学号   |\n";
			cout << "|2  姓名   |\n";
			cout << "|3  成绩   |\n";
			cin >> your_choice;
			switch (your_choice)
			{
			case choose_id:
				cout << "请输入新学号：\n";
				cin >> id;
				run.change(result, id);
				cout << "修改成功！\n";
				break;
			case choose_name:
				cout << "请输入新姓名：\n";
				cin >> name;
				run.change(result, name);
				cout << "修改成功！\n";
				break;
			case choose_score:
				cout << "请输入新学号：\n";
				cin >> score;
				run.change(score,result);
				cout << "修改成功！\n";
				break;
			Error:
				cout << "Error!!\n";
				break;
			}
			break;
		case choose_del:
			cout << "首先，您想通过哪一项信息查找？\n";
			cout << "|1 学号    |\n";
			cout << "|2 姓名    |\n";
			cin >> your_choice;
			switch (your_choice)
			{
			case choose_id:
				cout << "输入该学生学号：\n";
				cin >> id;
				result = run.find(id);
				break;
			case choose_name:
				cout << "输入该学生的姓名：\n";
				cin >> name;
				result = run.find(name);;
				break;
			Error:
				cout << "Error!!\n";
				break;
			}
			if (result == NULL)
			{
				cout << "抱歉，未找到此学生信息\n";
				cout << "或许，你可以通过“添加”功能新建学生信息\n";
				break;
			}
			run.del(result);
			cout << "删除成功！\n";
			break;
		case choose_all_del:
			run.all_del();
			break;
		case choose_add:
			cout << "请输入新学生的信息：\n";
			cin >> new_student.id >> new_student.name >> new_student.score;
			run.add(new_student);
			cout << "添加成功！\n";
			break;
		case choose_view:
			run.view();
			break;
		case choose_invert:
			run.invert();
			break;
		Error:
			if (your_choice == choose_exit)
			{
				break;
			}
			else
			{
				cout << "错误操作!!\n";
				continue;
			}
		}
		if (your_choice == choose_exit)
		{
			cout << "确定???\n";
			cout << " 再次输入0继续:";
			cin >> stop;
			if (stop == choose_exit)
			{
				break;
			}
		}
	}
	cout << "是否保存信息？（1为是，0为否）:\n";
	cin >> your_choice;
	if (your_choice == 1)
	{
		run.save();
	}
	cout << "是否需要打印成绩排名表？（表格格式为txt，打印请输入1	）\n";
	cin >> your_choice;
	if (your_choice == print)
	{
		run.GradeTable();
	}
	return 0;
}
