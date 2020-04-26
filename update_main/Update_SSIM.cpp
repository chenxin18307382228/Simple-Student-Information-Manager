#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<conio.h>
#define choose_id '1'
#define choose_name '2'
#define choose_score '3'
#define Error default             //输入错误
using namespace std;
//定义stu链表，head为头指针 
typedef struct element
{
	int id;              //id为学生学号 
	char name[100];      //name为学生姓名 
	int score;           //score为学生成绩 
	element* next;           //next用于形成链表 
}stu;
//用户
struct Users
{
	char username[20];        //用户名
	char password[7];         //密码
	char filename[20];        //存档名
};
//交换函数
void swap(element* ElementType1, element* ElementType2)
{
	int t_id = 0, t_score = 0;
	char t_name[10] = "000";
	//学号对换 
	t_id = ElementType1->id;
	ElementType1->id = ElementType2->id;
	ElementType2->id = t_id;
	//名字对换
	strcpy(t_name, ElementType1->name);
	strcpy(ElementType1->name, ElementType2->name);
	strcpy(ElementType2->name, t_name);
	//成绩对换
	t_score = ElementType1->score;
	ElementType1->score = ElementType2->score;
	ElementType2->score = t_score;
}

//建立“学生”类 
typedef class ElementList
{
protected:
	int num = 0;       //用于统计学生数量
	element* head = NULL;     //头指针
	element* tail = NULL;     //尾指针
public:
	element* find();                //查找指定学生信息
	void change();              //修改指定学生的指定信息
	void del();                 //删除指定学生信息
	void all_del();             //全部删除
	void add();                 //添加新学生信息
	void sort(element*, element*);      //对学生信息依据成绩排序
	void view();                //信息总览
	//析构函数--释放动态存储空间
	~ElementList()
	{
		element* p = head;
		while (p != NULL)
		{
			head = p->next;
			delete p;
			p = head;
		}
		delete head;
	}
}student;
//find--根据学号或姓名查找指定学生信息
element* ElementList::find()
{
	int ID;
	bool check = 0;
	char Name[20], choice;
	element* ElementType = head;
	int n = 0;                                  //记录学生名次
	cout << "您想通过哪一项信息查找？\n";
	cout << "|1 学号    |\n";
	cout << "|2 姓名    |\n";
	cin >> choice;
	switch (choice)
	{
	case choose_id:
		cout << "请输入学号：\n";
		cin >> ID;
		cout << "结果：\n";
		cout.setf(ios::left);
		cout << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
		while (ElementType != NULL)
		{
			n++;
			if (ElementType->id == ID)
			{
				cout << setw(12) << n << setw(12) << ElementType->id << setw(12) << ElementType->name << setw(12) << ElementType->score << '\n' << endl;
				check = 1;
				break;
			}
			ElementType = ElementType->next;
		}
		//若未找到指定学生
		if (check == 0)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	case choose_name:
		cout << "请输入姓名：\n";
		cin >> Name;
		cout << "结果：\n";
		cout.setf(ios::left);
		cout << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
		while (ElementType != NULL)
		{
			n++;
			if (strcmp(ElementType->name, Name) == 0)
			{
				cout << setw(12) << n << setw(12) << ElementType->id << setw(12) << ElementType->name << setw(12) << ElementType->score << '\n' << endl;
				check = 1;
				break;
			}
			ElementType = ElementType->next;
		}
		if (check == 0)
		{
			cout << "抱歉，未找到此学生信息\n";
			cout << "或许，你可以通过“添加”功能新建学生信息\n";
		}
		break;
	Error:
		cout << "Error!!\n";
		break;
	}
	return ElementType;
}
//change--修改学生信息
void ElementList::change()
{
	element* ElementType = head, new_student;
	char choice;                       //choice为修改信息选项
	bool check = 0;                   //判断是否找到
	ElementType = find();
	//若找到，进入信息修改进程
	if (ElementType != NULL)
	{
		cout << ElementType->id << '\t' << ElementType->name << '\t' << ElementType->score << '\n' << endl;
		cout << "你希望修改学生的哪一项信息 ? :\n";
		cout << "|1  学号   |\n";
		cout << "|2  姓名   |\n";
		cout << "|3  成绩   |\n";
		cin >> choice;
		switch (choice)
		{
		case choose_id:
			cout << "请输入新学号: ";
			cin >> new_student.id;
			cout << "结果:\n";
			ElementType->id = new_student.id;
			cout << "修改成功!\n";
			break;
		case choose_name:
			cout << "请输入新姓名: ";
			cin >> new_student.name;
			cout << "结果:\n";
			strcpy(ElementType->name, new_student.name);
			cout << "修改成功 !\n";
			break;
		case choose_score:
			cout << "请输入新成绩: ";
			cin >> new_student.score;
			cout << "结果:\n";
			ElementType->score = new_student.score;
			cout << "修改成功!\n";
			break;
		Error:
			cout << "Error!!!\n";
			return;
		}
		cout << ElementType->id << '\t' << ElementType->name << '\t' << ElementType->score << '\n' << endl;
	}
	return;
}
//del--删除学生信息
void ElementList::del()
{
	int n = 0, choice = 0;
	bool check = 0;                //判断是否找到
	element* ElementType1 = head, * ElementType2 = head;
	cout << "结果:\n";
	ElementType1 = find();
	//若找到，进入删除进程
	if (ElementType1 != NULL)
	{
		for (; ElementType2->next != ElementType1; ElementType2 = ElementType2->next);
		cout << "删除成功 !\n";
		if (ElementType1 == head)          //若要删除的学生为链表中的第一位学生，则头指针后移
		{
			head = head->next;
		}
		else
		{
			ElementType2->next = ElementType1->next;
		}
		delete ElementType1;
		num--;
	}
	//标注尾指针
	ElementType2 = head;
	if (ElementType2 != NULL)
	{
		while (ElementType2->next != NULL)
		{
			ElementType2 = ElementType2->next;
		}
		tail = ElementType2;
	}
	else
	{
		cout << "*********************\n";
		cout << "*       注意！      *\n";
		cout << "*                   *\n";
		cout << "*   学生列表已空    *\n";
		cout << "*********************\n";
		tail = NULL;
	}
	return;
}
//all_del--全体删除
void ElementList::all_del()
{
	element* p = head;
	while (p != NULL)
	{
		num--;
		head = p->next;
		delete p;
		p = head;
	}
	delete p;
	cout << "删除成功！\n";
	return;
}
//add--增加学生
void ElementList::add()
{
	element* ElementType = head, * new_student;
	new_student = new stu;
	cout << "请输入你所要添加的学生的信息:\n";
	cin >> new_student->id >> new_student->name >> new_student->score;
	//在链表尾端添加学生信息
	if (head != NULL)
	{
		tail->next = new_student;
		tail = new_student;
		new_student->next = NULL;
	}
	else
	{
		head = new_student;
		tail = new_student;
		new_student->next = NULL;
	}
	cout << "添加成功！\n";
	num++;
	sort(head, tail);
	return;
}
//sort--对学生成绩进行排名（快速排序）
void ElementList::sort(element* head, element* tail)
{
	if (head == tail || head == NULL || head == tail->next)
	{
		return; // 递归出口
	}
	element* ElementType1, * ElementType2, * key;
	ElementType1 = ElementType2 = key = head;
	while (ElementType2 != tail)
	{
		ElementType2 = ElementType2->next; // 对于一个链表只遍历一遍
		if (ElementType2->score > head->score)
		{
			// 如果ElementType2的值大于key则放在左边
			key = ElementType1;
			ElementType1 = ElementType1->next;
			swap(ElementType1, ElementType2);
		}
	}
	/*
	执行while完毕后的情况：
	key在head,[head->next,ElementType1]大于key,[ElementType2->next,tail]小于key
	*/
	swap(head, ElementType1);
	sort(head, key);
	sort(ElementType1->next, tail);
	return;
}
//view--总览所有学生信息
void ElementList::view()
{
	//先对数据进行排序
	sort(head, tail);
	cout << "结果：\n";
	int n;                   //用于记录名次
	element* ElementType1 = head;
	cout.setf(ios::left);
	cout << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n' << endl;
	for (n = 1; ElementType1 != NULL; n++)
	{
		cout << setw(12) << n << setw(12) << ElementType1->id << setw(12) << ElementType1->name << setw(12) << ElementType1->score << '\n' << endl;
		ElementType1 = ElementType1->next;
	}
	cout << "                                                              人数：" << num << endl;
	return;
}
#define choose_log_in '1'               //选择登录
#define choose_sign_in '2'              //选择注册
//用户类
class user :public ElementList
{
private:
	Users messi;             //梅西 :）
public:
	user();
	bool sign_in();             //构造函数，用户注册or登录
	bool set();                  //建立初始学生信息
	void GradeTable();          //打印成绩表
	void save();                //保存学生信息
};
user::user()
{
	cout << "--------------------欢迎使用学生信息统计系统----------------------\n" << endl;
	strcpy(messi.filename,"\0");
	strcpy(messi.username,"\0");
	strcpy(messi.password,"\0");
}
bool user::sign_in()
{
	ofstream cout_collection("collection.txt",ios_base::app);    //用于存储用户们的信息
	if (!cout_collection)
	{
		cout << "请先建立“collection.txt”文件！";
		system("pause");
		exit(1);
	}
	bool check = 0;
	char temp[7] = {'\0'};                       //用于注册时二次输入密码
	char choice;
	char test_name[20];                          //验证登录用户名
	char test_password[7] = {'\0'};              //验证登录密码
	bool test_log = 0;                           //用于判断用户是否存在
	Users exist[100] = {"\0","\0","\0"};         //读取collection.txt内的所有用户信息，用于登录时判断用户是否存在
	ifstream cin_collection;                     //读取用户的信息，用于登录操作
	ofstream user_save;                          //对学生信息存档
	int save_num = 0;                            //存档个数
	cin_collection.open("collection.txt");
	if (!cin_collection)
	{
		cout << "请先建立“user.txt”文件\n";
		system("pause");
		exit(1);
	}
	for (int i = 0; cin_collection.peek() != EOF; i++)
	{
		cin_collection >> exist[i].username >> exist[i].password >> exist[i].filename;
		save_num++;
	}
	save_num--;
	cout << "请选择：\n";
	cout << "     |   1、登录    |\n";
	cout << "     |   2、注册    |\n";
	cin >> choice;
	switch (choice)
	{
		system("cls");
	case choose_sign_in:
		for (int i = 0; i < save_num;)
		{
			cout << "新用户名：";
			cin >> messi.username;
			for (; i < save_num; i++)
			{
				if (!strcmp(messi.username, exist[i].username))
				{
					cout << "用户名已存在！\n";
					break;
				}
			}
		}
		strcpy(messi.filename, messi.username);
		strcat(messi.filename, ".txt");
		while (!check)
		{
			cout << "\n密码（限6位）：";
			for (int i = 0; i < 6; i++)
			{
				messi.password[i] = getch();
				cout << "*";
			}
			strcpy(temp, messi.password);
			cout << "\n再次输入密码：";
			for (int i = 0; i < 6; i++)
			{
				messi.password[i] = getch();
			    cout << "*";
			}
			if (strcmp(temp,messi.password))
			{
				cout << "\n前后密码有误，请重新设置！\n";
			}
			else 
				check = 1;
		}
		cout_collection << messi.username << '\t' << messi.password << '\t' << messi.filename << endl;
		user_save.open(messi.filename);
		break;
	case choose_log_in:
		cout << "用户名：";
		cin >> test_name;
		cout << endl;
		cout << "\n密码：";
		for (int j = 0; j < 6; j++)
		{
			test_password[j] = getch();
			cout << "*";
		}
		for (int i = 0; i < 100; i++)
		{
			if (!strcmp(test_name, exist[i].username))
			{
				test_log = 1;
				if (!strcmp(test_password, exist[i].password))
				{
					cout << "\n登陆成功！\n";
					strcpy(messi.filename, exist[i].filename);
					strcpy(messi.username, exist[i].username);
					strcpy(messi.password, exist[i].password);
					check = 1;
					break;
				}
			}
		}
		//判断用户是否存在
		if (!test_log)
		{
			cout << "用户不存在！\n";
			system("pause");
			system("cls");
		}
		//判断密码是否正确
		else if (!check)
		{
			cout << "\n密码错误\n";
			system("pause");
			system("cls");
		}
		break;
	Error:
		cout << "Error!!\n";
		break;
	}
	cout_collection.close();
	cin_collection.close();
	user_save.close();
	return check;
}
//set--建立初始学生信息，先读取文件，若无学生信息，则再新建
bool user::set()
{
	bool check = 0;
	stu* ElementType1, * ElementType2;
	head = NULL;
	ElementType2 = head;
	ifstream infile(messi.filename);     //student.txt为学生信息存出文件，通过读取此文件，可直接获取学生信息
	if (!infile)
	{
		cout << "请先建立 "<<messi.filename<<" 文件!" << endl;
		system("pause");
		exit(-1);
	}
	int id, score;           //id和score的中转变量
	char name[20];           //name的中转变量
	ElementType1 = new stu;  //首次动态分配空间
	while (infile.peek() != EOF)   //遍历student.txt数据
	{
		num++;
		infile >> id >> name >> score;       //为中转变量赋值
		//为链表成员变量赋值
		ElementType1->id = id;
		strcpy(ElementType1->name, name);
		ElementType1->score = score;
		//判断头指针是否为空，若为空，则从头开始赋值，否则从末端开始赋值
		if (head == NULL)
		{
			head = ElementType1;
		}
		else
		{
			ElementType2->next = ElementType1;
		}
		ElementType2 = ElementType1;           //ElementType2向前移动
		ElementType1 = new stu;                //继续动态分配空间
	}
	//若从文件中读取出数据
	if (head != NULL)
	{
		check = 1;
		ElementType2->next = NULL;     //结束建立链表进程
	}
	//标注尾指针
	tail = ElementType2;
	ElementType2 = NULL;
	infile.close();
	//判断之前通过文件流建立链表是否成功，若成功，结束函数，返回链表长度num，反之开始初次建立链表（手动输入）
	if (head != NULL)
	{
		return check;
	}
	else
	{
		cout << "*********************现在建立初始学生信息**********************\n";
		ElementType1 = new stu;
		num = 1;
		cout << "请输入第1个学生的信息（当学号为0是终止）:\n";
		cin >> ElementType1->id >> ElementType1->name >> ElementType1->score;
		if (ElementType1->id == 0)        //如果输入学生学号为0，则输入错误，跳出函数 
		{
			return 0;
		}
		while (ElementType1->id != 0)     //当输入0时结束建立 
		{
			num++;
			if (head == NULL)
			{
				head = ElementType1;
			}
			else
			{
				ElementType2->next = ElementType1;
			}
			ElementType2 = ElementType1;
			ElementType1 = new stu;
			cout << "请输入第" << num << "个学生的信息（当学号为0时终止）:\n";
			cin >> ElementType1->id >> ElementType1->name >> ElementType1->score;
		}
		ElementType2->next = NULL;     //结束手动建立链表进程
		tail = ElementType2;
		cout << "建立成功！\n";
	}
	if (head != NULL) { check = 1; }
	sort(head, tail);
	num--;
	return check;           //返回学生数量num 
}
//GradeTable--打印成绩表
void user::GradeTable()
{
	char GT[100] = "GradeTable_";
	ofstream ouf;       //用于打印成绩表
	ouf.setf(ios::left);
	sort(head, tail);
	stu* ElementType = head;
	strcat(GT, messi.filename);
	ouf.open(GT);
	if (!ouf)
	{
		cout << "抱歉，输出文件建立失败，您可以手动建立"<<GT<<"文件"<<endl;
		system("pause");
		exit(1);
	}
	ouf << setw(12) << "名次" << setw(12) << "学号" << setw(12) << "姓名" << setw(12) << "分数" << '\n';
	for (int n = 1; ElementType != NULL; n++)
	{
		;
		ouf << setw(12) << n << setw(12) << ElementType->id << setw(12) << ElementType->name << setw(12) << ElementType->score << '\n';
		ouf << "--------------------------------------------------------------------------------------------------\n";
		ElementType = ElementType->next;
	}
	ouf.close();
	return;
}
//save--保存学生信息
void user::save()
{
	ofstream outfile;   //用于保存信息
	outfile.open(messi.filename);//每次打开程序，都会自动清空student.txt中的旧内容，在向其中输入新内容 
	if (!outfile)
	{
		cout << "抱歉，输出文件建立失败!您可以手动建立"<<messi.filename<<'\n';
		system("pause");
		exit(1);
	}
	stu* ElementType = head;
	if (head != NULL)
	{
		while (ElementType->next != NULL)
		{
			outfile << ElementType->id << '\t' << ElementType->name << '\t' << ElementType->score << endl;
			ElementType = ElementType->next;
		}
		outfile << ElementType->id << '\t' << ElementType->name << '\t' << ElementType->score;
	}
	outfile.close();       //关闭存储文件
	return;
}
#undef choose_id
#undef choose_name
#undef choose_score
#define choose_find '1'
#define choose_change '2'
#define choose_del '3'
#define choose_all_del '4'
#define choose_add '5'
#define choose_view '6'
#define choose_exit '0'
#define print '1'
#define Save '1'
int main()
{  
	user run;//创建user对象run
	char your_choice, stop;//your_choice可用于选择是否重新建立链表、选择操作、选择是否保存、选择是否打印成绩表
	bool check = 0;
	while (!check)
	{
		check = run.sign_in();
	}
	system("pause");
	system("cls");
	//建立链表
	check = 0;
	while (true)
	{
		check = run.set();
		//判断手动建立链表是否出错
		if (check == 0)
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
				return -1;
			}
		}
		break;
	}
	//开始进行各项操作
	while (true)
	{
		system("pause");
		system("cls");
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
			run.find();
			break;
		case choose_change:
			run.change();
			break;
		case choose_del:
			run.del();
			break;
		case choose_all_del:
			run.all_del();
			break;
		case choose_add:
			run.add();
			break;
		case choose_view:
			run.view();
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
	if (your_choice == Save)
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
