// PANGFENGZHENGA1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

void wrongInput();
void anyKey();

void runMenu();
void endTesting();
void displayText();
void creatList(string filename);
string generateTable(int dice_num, int times);
void save();
void load();
void printTallyData(string data);

//vector<vector<int>> tallyData;
vector<string> tallyData;

vector<string> tallyResults;


int main()
{
	//n = 0;
	tallyResults.clear();
	tallyData.clear();
	//diceNum.clear();

	while (1) {
		runMenu();
	}

    return 0;
}

void runMenu() {
	system("cls");
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "The Tally Ho Probability Generator\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "[0]\t End Testing the Program" << endl;
	cout << "[1]\t Display 'About' Information" << endl;
	cout << "[2]\t Read and store data from files" << endl;
	cout << "[3]\t Generate a Dice Tally Table" << endl;
	cout << "[4]\t Save Tally Statistics to a file" << endl;
	cout << "[5]\t Load Tally Statistics from a file" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "Which option would you like (0-5):";
	int input_number;
	cin >> input_number;
	cout << endl << endl;
	string data;
	int dice_num, times;
	switch (input_number) {
	case 0:
		endTesting();
		break;
	case 1:
		displayText();
		anyKey();
		break;
	case 2:
		cout << "Data loading from" << "savedTallyData.txt" << endl;
		creatList("savedTallyData.txt");
		anyKey();
		break;
	case 3:
		cout << "How many dice to roll (1-2): ";
		cin >> dice_num;
		cout << "How many rolls required (1-10): ";
		cin >> times;
		times *= 10;
		data = generateTable(dice_num, times);
		tallyResults.push_back(data);
		//cout << data << endl;
		printTallyData(data);
		anyKey();
		break;
	case 4:
		save();
		anyKey();
		break;
	case 5:
		load();
		anyKey();
		break;
	default:
		wrongInput();
		break;
	}
}

//输入错误选项
void wrongInput()
{
	cout << "\tInvalid input, please check! " << endl;
	cout << endl;
	anyKey();
}

void anyKey()
{
	cout << "\tPress any key to continue . . ." << endl;
	_getch();  //按任意键继续
}

//结束程序
void endTesting()
{
	cout << "Thank you for testing this application" << endl;
	anyKey();
	exit(0);
}

void displayText()
{
	ifstream in("TallyAbout.txt", ios::in);
	if (!in.is_open()) {
		cout << "This file cannot be opened" << endl;
		cout << endl;
	}
	else {
		system("cls");
		string line;
		while (!in.eof()) {
			getline(in, line);
			cout << line << endl;
		}
	}
}

void creatList(string filename)
{
	ifstream in(filename, ios::in);
	if (!in.is_open()) {
		cout << "File Not Found" << endl;
		cout << endl;
	}
	else {
		string line;
		while (!in.eof()) {
			getline(in, line);
			tallyData.push_back(line);
		}
	}
}

//void creatList(string filename)
//{
//	ifstream in(filename, ios::in);
//	if (!in.is_open()) {
//		cout << "File Not Found" << endl;
//		cout << endl;
//	}
//	else {
//		//读取结果数量
//		in >> n;
//		int k; //点数
//		int q; //骰子数
//		//这里设置一个临时的vector用于保存每次的记录
//		vector<int> tally;
//		for (int i = 0; i < n; i++) {
//			cin >> q;
//			for (int j = 0; j < q; j++) {
//				in >> k;
//				tally.push_back(k); //记录当前点数的数量
//			}
//			tallyData.push_back(tally); //记录每次的结果
//			diceNum.push_back(q); //记录骰子数量
//		}
//	}
//}

void printTallyData(string data)
{
	stringstream str;
	str.str(data);
	int dice_num;
	int k, sum;
	vector<int> tally;
	str >> dice_num;
	sum = 0;
	for (int i = 0; i < 5 * dice_num + 1; i++) {
		str >> k;
		sum += k;
		tally.push_back(k);
	}
	cout << "You rolled " << dice_num << " dice " << sum << " times." << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	for (int i = 0; i < 5 * dice_num + 1; i++) {
		cout << setw(3) << right << i + dice_num;
		cout << ": ";
		for (int j = 0; j < tally[i]; j++) {
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;
}

string generateTable(int dice_num, int times)
{
	stringstream str;
	default_random_engine e; //随机数生成工具
	uniform_int_distribution<unsigned> u(dice_num, 6 * dice_num);
	vector<int> tally(5 * dice_num + 1, 0);
	int k;
	for (int i = 0; i < times; i++) {
		k = u(e); //随机数
		tally[k- dice_num] += 1; //记录
	}
	str << dice_num << " "; //这里用字符串流的方法处理数据
	for (int i = 0; i < 5 * dice_num + 1; i++) {
		str << tally[i] << " "; //数据写入字符串
	}
	return str.str();
}

void save()
{
	if (tallyResults.size() == 0) {
		//保存前判断表格是否为空
		cout << "There is no result to save." << endl;
		return;
	}
	printTallyData(tallyResults.at(tallyResults.size() - 1));
	cout << "Do you want to save this data? (y/n)";
	char c;
	cin >> c;
	if (c == 'y') {
		ofstream of;
		of.open("savedTallyData.txt", ios::out);
		of << tallyResults.size()<<endl;
		for (int i = 0; i < tallyResults.size(); i++) {
			of << tallyResults[i];
		}
		of.close();
		cout << "\t These statistics are now saved.";
		anyKey();
		for (int i = 0; i < tallyResults.size(); i++) {
			printTallyData(tallyResults[i]);
		}

	}
	tallyResults.clear();
	anyKey();
}

void load()
{
	if (!tallyResults.empty()) {
		cout << "Data are not saved!";
	}
	else{
		ifstream in("savedTallyData.txt", ios::in);
		if (!in.is_open()) {
			cout << "File Not Found" << endl;
			cout << endl;
		}
		else {
			int n;
			in >> n;
			string line;
			for (int i = 0; i < n; i++) {
				getline(in, line);
				tallyResults.push_back(line);
			}
		}
		cout << "Load data from savedTallyData.txt!" << endl;
	}
}
