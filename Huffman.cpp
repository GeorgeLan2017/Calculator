#include<iostream>
#include <stdio.h>
#include<string>
#include<fstream>
#include<queue>
#include<map>
using namespace std;

map<char, string> HuffCode;//用于储存Huffman编码 
int ptrOfString,NumOfChar[1000];

struct node
{	node *Left = NULL;
	node *Right = NULL;
	int Times;//出现次数 
	char Letter;//当前字符 
};

struct cmp//以下10行参考CSDN，建立堆 
{
	bool operator()(node *node1, node *node2)
	{
		return node1->Times > node2->Times;
	}
};

node *root;

priority_queue <node*, vector<node*>, cmp> Heap;//优先队列  最小频率的先出队列 

void Traversal(node *root, string weight)//将字符和编码对应 
{
	if (root->Left == NULL)
	{
		HuffCode[root->Letter] = weight;
		return;//return 不可少 
	}
	Traversal(root->Left, weight + "0");
	Traversal(root->Right, weight + "1");
}


void Compress()//压缩 
{
	string SourceFileName, CodeFileName, InputFile = "";
	cout << "Please input source file name(size less than 4GB):";
	cin >> SourceFileName;
	cout << "Please input code file name:";
	cin >> CodeFileName;
	cout << "Processing..." << endl;
	ifstream SourceFile;
	SourceFile.open(SourceFileName.data(), ios::in);
	char temp = 1;
	while (temp != EOF)
	{
		temp = SourceFile.get();
		NumOfChar[temp]++;//出现次数加1 
		InputFile += temp;//将字符写入 
	}
	for (int i = 0; i < 500; i++)
	{
		if (!NumOfChar[i])
			continue;
		node *point = new node;
		point->Letter = (char)i;
		point->Times = NumOfChar[i];
		point->Left = point->Right = NULL;
		Heap.push(point);
	}
	node *left, *right, *parent;
	while (Heap.size() != 1)//建树 
	{
		parent = new node;
		left = new node;
		right = new node;
		left = Heap.top();
		Heap.pop();
		right = Heap.top();
		Heap.pop();
		parent->Left = left;
		parent->Right = right;
		parent->Letter = 0;
		parent->Times = left->Times + right->Times;
		Heap.push(parent);
	}
	root = Heap.top();//最后只剩1个结点，是合并出来的 
	Traversal(root, "");//转换成编码 
	SourceFile.close();
	ofstream CodeFile;
	CodeFile.open(CodeFileName.data(), ios::out);//实现打印 
	for (int i = 0; i < InputFile.length(); i++)
		CodeFile << HuffCode[InputFile[i]];
	CodeFile.close();
	cout << "Process end." << endl;
}


string visitHuffman(node *root,string Input)//访问哈夫曼树 ，把编码转成字母 
{
	string result;
	node *NowNode = new node;
	NowNode = root;
	while (NowNode->Left != NULL)
	{
		if (Input[ptrOfString] == '0')//为0，往左走 （ptrOfString 当前位置） 
			NowNode = NowNode->Left;
		else
			NowNode = NowNode->Right;//为1，往右走 
		ptrOfString++;
		if (ptrOfString == Input.length())
			break;
	}
	result += NowNode->Letter;
	return result;
}

string DecodeHuffman(string Input)//译码 
{
	string result;
	ptrOfString = 0;
	while (ptrOfString < Input.length())
		result += visitHuffman(root,Input);
	return result;
}


void Decompress()//解压缩 
{
	string TargetFileName, CodeFileName, InputFile = "";
	cout << "Please input code file name(size less than 4GB):";
	cin >> CodeFileName;
	cout << "Please input target file name:";
	cin >> TargetFileName;
	cout << "Processing..." << endl;
	ifstream CodeFile;
	CodeFile.open(CodeFileName.data(), ios::in);
	char temp = 1;
	while (temp != EOF)
	{
		temp = CodeFile.get();
		NumOfChar[temp]++;
		InputFile += temp;
	}
	CodeFile.close();
	ofstream TargetFile;//目标文件 
	TargetFile.open(TargetFileName.data(), ios::out);
	string ans=DecodeHuffman(InputFile);
	TargetFile << ans << endl;//输出 
	cout << "Process end." << endl;
	TargetFile.close();
}

int UI()
{
	int temp;
	cout << endl;
	cout << "1.Huffman compress." << endl;
	cout << "2.Huffman decompress." << endl;
	cout << "3.Exit." << endl;
	cout << "Please select:";
	cin >> temp;
	if (temp < 1 || temp > 3)
	{
		return 1;
	}
	if (temp == 3)
		return 0;
	if (temp == 1)
		Compress();
	if (temp == 2)
		Decompress();
	return 1;
}

int main()
{
	while (UI());
	return 0;
}
