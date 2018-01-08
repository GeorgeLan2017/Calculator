#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
bool visit[100];
int numberOfvertex,tot, numberOfterm[10], head[1000] ;

struct edge// 边 
{
	int to, next;
}e[1000];

int StrToInt(string s)
{
	int ans = 0;
	for (int i = 0; i < s.size(); i++)
		ans = ans * 10 + s[i] - 48; //字符转化为整数 
	return ans;
}



class vertex//顶点 
{
public:
	int number, hours, term, degree;
	string name;
	vertex(string a,string b,string c,string d)//初始化 
	{
		string newnumber = "";
		for (int i = 1; i < a.size(); i++)
			newnumber += a[i];
		name = b;
		number = StrToInt(newnumber);
		hours = StrToInt(c);
		term = StrToInt(d);
		degree = 0;
	}
	vertex(){}
	                           
	void IncDegree()
	{
		degree++;
	}

	void output()
	{
		cout << name << " " << 'c'<<number << " " << hours << " " << endl;
	}
};

vertex Nodes[100];
int index;

void addedge(int x, int y) //向邻接表中加边 
{
	tot++;
	Nodes[y].IncDegree();
	e[tot].to = y;
	e[tot].next = head[x];
	head[x] = tot;
}


string nextString(string s)//获取下一字符串 
{
	for(int i =0;i<s.size();i++)
	{
		if(s[index] == ' ' || s[index] == '\t' && index < s.size())
		index++;
	}
 if (s[index] == '\n' || index >= s.size())
		return "";
	string ans = "";
	for(int i =0;i<s.size();i++)
	{
		if (s[index] != ' ' && s[index] != '\t' && index < s.size())
		{
			ans += s[index];
			index++;
		}
	}
	return ans;
}


void Init()//初始化，读取文件 
{
	string Line="",FileName="C:\course_inf.txt";
	ifstream infoFile;
	infoFile.open(FileName.data(), ios::in);
	vector <string> info;
	char temp = ' ';
	while (temp != EOF)
	{
		temp = infoFile.get();
		if (temp == '\n')
		{
			if (Line == "")
				continue;
			if (Line[0] == Line[1] && Line[0] == '/')
			{
				Line = "";
				continue;
			}
			info.push_back(Line);
			Line = "";
			continue;
		}
		Line += temp;
	}
	int k = 0;
	for (int i = 0; i < info[0].size(); i++)
	{
		if (info[0][i] < '0' || info[0][i] > '9')
			continue;
		int sum = 0;
		while (info[0][i] >= '0'&&info[0][i] <= '9'&&i < info[0].size())
		{
			sum = sum * 10 + info[0][i] - 48;
			i++;
		}
		numberOfterm[++k] = sum;
		numberOfvertex += sum;
 }

	for (int i = 1; i <= numberOfvertex; i++)
	{
		index = 0;
		vector <string> Lineinfo;
		for (int j = 1; j <= 4; j++)
			Lineinfo.push_back(nextString(info[i]));
		vertex node(Lineinfo[0], Lineinfo[1],Lineinfo[2], Lineinfo[3] );
		Nodes[i] = node;
		while (index < info[i].size())
		{
			string From = nextString(info[i]), newFrom = "";
			if (From == "")
				break;
			for (int it = 1; it < From.size(); it++)
				newFrom += From[it];
			int from = StrToInt(newFrom);
			addedge(from, i);
		}
	}
	infoFile.close();
}

vector<int> ans[10];

int Remain()
{
	for (int i = 1; i <= numberOfvertex; i++) 
	{
		if (visit[i])
			continue;
		if (Nodes[i].degree != 0)
			continue;
		return i; 
	}
	return 0;
}

void Sort()//找入度为0的点，加到序列中，然后把该点连接的点的入度减一 
{	
	int nowNode, nowTerm;
	for (int i = 1; i <= numberOfvertex; i++)
		if (Nodes[i].term != 0)
		{
			ans[Nodes[i].term].push_back(i);
			visit[i] = 1;
			numberOfterm[Nodes[i].term]--;
			continue;
		}

	for (int i = 1; i <= 8; i++)
		if (numberOfterm[i] > 0)
		{
			nowTerm = i;
			break;
		}
	while (Remain())
	{
		nowNode = Remain();
		visit[nowNode] = 1;
		ans[nowTerm].push_back(nowNode);
		for (int i = head[nowNode]; i; i = e[i].next)
			Nodes[e[i].to].degree--;
		numberOfterm[nowTerm]--;
		if (numberOfterm[nowTerm] == 0)
			nowTerm++;
	}
	for (int i = 8; i >= 1; i--)
	{
		cout << "第" << i << "学期：" << endl;
		for (int j = 0; j < ans[i].size(); j++)
		{
			Nodes[ans[i][ans[i].size()-1-j]].output();
		}
	}
}

int main(void)
{
	bool flag=true; 
	Init(); 
	Sort();
	while (flag);
    return 0;

}
