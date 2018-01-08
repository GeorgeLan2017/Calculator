#include<iostream>
#include <stdio.h>
#include<string>
#include<fstream>
#include<queue>
#include<map>
using namespace std;

map<char, string> HuffCode;//���ڴ���Huffman���� 
int ptrOfString,NumOfChar[1000];

struct node
{	node *Left = NULL;
	node *Right = NULL;
	int Times;//���ִ��� 
	char Letter;//��ǰ�ַ� 
};

struct cmp//����10�вο�CSDN�������� 
{
	bool operator()(node *node1, node *node2)
	{
		return node1->Times > node2->Times;
	}
};

node *root;

priority_queue <node*, vector<node*>, cmp> Heap;//���ȶ���  ��СƵ�ʵ��ȳ����� 

void Traversal(node *root, string weight)//���ַ��ͱ����Ӧ 
{
	if (root->Left == NULL)
	{
		HuffCode[root->Letter] = weight;
		return;//return ������ 
	}
	Traversal(root->Left, weight + "0");
	Traversal(root->Right, weight + "1");
}


void Compress()//ѹ�� 
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
		NumOfChar[temp]++;//���ִ�����1 
		InputFile += temp;//���ַ�д�� 
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
	while (Heap.size() != 1)//���� 
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
	root = Heap.top();//���ֻʣ1����㣬�Ǻϲ������� 
	Traversal(root, "");//ת���ɱ��� 
	SourceFile.close();
	ofstream CodeFile;
	CodeFile.open(CodeFileName.data(), ios::out);//ʵ�ִ�ӡ 
	for (int i = 0; i < InputFile.length(); i++)
		CodeFile << HuffCode[InputFile[i]];
	CodeFile.close();
	cout << "Process end." << endl;
}


string visitHuffman(node *root,string Input)//���ʹ������� ���ѱ���ת����ĸ 
{
	string result;
	node *NowNode = new node;
	NowNode = root;
	while (NowNode->Left != NULL)
	{
		if (Input[ptrOfString] == '0')//Ϊ0�������� ��ptrOfString ��ǰλ�ã� 
			NowNode = NowNode->Left;
		else
			NowNode = NowNode->Right;//Ϊ1�������� 
		ptrOfString++;
		if (ptrOfString == Input.length())
			break;
	}
	result += NowNode->Letter;
	return result;
}

string DecodeHuffman(string Input)//���� 
{
	string result;
	ptrOfString = 0;
	while (ptrOfString < Input.length())
		result += visitHuffman(root,Input);
	return result;
}


void Decompress()//��ѹ�� 
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
	ofstream TargetFile;//Ŀ���ļ� 
	TargetFile.open(TargetFileName.data(), ios::out);
	string ans=DecodeHuffman(InputFile);
	TargetFile << ans << endl;//��� 
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
