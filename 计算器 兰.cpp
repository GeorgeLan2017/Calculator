#include <iostream>
using namespace std; 
enum StatusCode{SUCCESS, FAIL, UNDER_FLOW, OVER_FLOW,RANGE_ERROR,DUPLICATE_ERROR,NOT_PRESENT,ENTRY_INSERTED,ENTRY_FOUND,VISITED,UNVISITED};
template<class ElemType>
struct node
{
	ElemType data;
	node<ElemType> *next;
	node();
	node(ElemType item, node<ElemType> *link = NULL);
};
template<class ElemType>
node<ElemType>::node()
{
	next=NULL;
}
template<class ElemType>
node<ElemType>::node(ElemType item, node<ElemType> *link)
{
	data = item;
	next = link;
}

template<class ElemType>
class LinkStack
{
public:
	node<ElemType> *top;
	void Init();
public:
	LinkStack();
	virtual ~LinkStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit)(const ElemType &)) const;
	StatusCode Push(const ElemType &e);
	ElemType Top() const;
	ElemType Pop();
	LinkStack(const LinkStack<ElemType>&copy);
	LinkStack<ElemType>&operator=(const LinkStack<ElemType>&copy);
};

template<class ElemType>
void LinkStack<ElemType>::Init()
{
	top=NULL;
}

template<class ElemType>
LinkStack<ElemType>::LinkStack()
{
	Init();
}
 
 template<class ElemType>
 LinkStack<ElemType>::~LinkStack()
 {
	 Clear();
 }

template <class ElemType>
int LinkStack<ElemType>::Length() const
{
	int count=0;
	for(node<ElemType> *tmpPtr=top;tmpPtr!= NULL;tmpPtr=tmpPtr->next)
	{
		count++;
	}
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
{
	ElemType tmpElem;
	while (!Empty())
	{
		Pop();
	}
}

template<class ElemType>
void LinkStack<ElemType>::Traverse(void (*visit)(const ElemType &)) const
{
	node<ElemType> *tmpPtr;
	LinkStack<ElemType> tmpS;
	for (tmpPtr = top;tmpPtr != NULL;tmpPtr->next)
	{
		tmpS.Push(tmpPtr->data);
	}
	for (tmpPtr = tmpS.top;tmpPtr != NULL;tmpPtr->next)
	{
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
StatusCode LinkStack<ElemType>::Push(const ElemType &e)
{
	node<ElemType> *new_top = new node<ElemType>(e, top);
	if (new_top == NULL)
	{
		return OVER_FLOW;
	}
	else
	{
		top = new_top;
		return SUCCESS;
	}
}

template<class ElemType>
ElemType LinkStack<ElemType>::Top() const
{
	if (Empty())
	{
		return UNDER_FLOW;
	}
	else
	{
		
		return top->data;
	}
}

template<class ElemType>
ElemType LinkStack<ElemType>::Pop()
{
	if (Empty())
	{
		return UNDER_FLOW;
	}
	else
	{
		node<ElemType> *old_top = top;
		top = old_top->next;
		ElemType e= old_top->data;
		delete old_top;
		return e;
	}
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType> &copy)
{
	if (copy.Empty())
	{
		Init();
	}
	else
	{
		top = new node<ElemType>(copy.top->data);
		node<ElemType> *buttomPtr = top;
		for (node<ElemType> *tmpPtr = copy.top->next;tmpPtr != NULL;tmpPtr = tmpPtr->next)
		{
			buttomPtr->next = new node<ElemType>(tmpPtr->data);
			buttomPtr = buttomPtr->next;
		}
	}
}

template<class ElemType>
LinkStack<ElemType>&LinkStack<ElemType>::operator=(const LinkStack<ElemType>&copy)
{
	if (&copy != this)
	{
		if (copy.Empty())
		{
			Init();
		}
		else
		{
			Clear();
			top = new node<ElemType>(copy.top->data);
			node<ElemType> *buttomPtr = top;
			for (node<ElemType> *tmpPtr = copy.top->next;tmpPtr != NULL;tmpPtr = tmpPtr->next)
			{
				buttomPtr->next = new node<ElemType>(tmpPtr->data);
				buttomPtr = buttomPtr->next;
			}
		}
	}
	return *this;
}


double get(char*s, int &k)//此函数，根据输入形式（有无小数点），返回输入的操作数 
{
	int flag = 0;
	double x = 0.0, y = 0.1;
	while (s[k] >= '0'&&s[k] <= '9' || s[k] == '.')
	{
		if (s[k] >= '0'&&s[k] <= '9')
		{
			if (flag == 0)
				x = x * 10 + s[k] - '0';
			else
			{
				x = x + y*(s[k] - '0');
				y = y*0.1;
			}
		}
		else
		{
			flag = 1;
		}
		k = k + 1;
	}
	return x;//x代表当前操作数 
}

int priority(char c)
{
	int k;
	switch (c)
	{
	case '*':k = 2; break;
	case '/':k = 2; break;
	case '+':k = 1; break;
	case '-':k = 1; break;
	case '(':k = 0; break;
	case ')':k = 0; break;
	default:k = -1; break;
	}
	return k;
}

int main ()
{	
	LinkStack<double> sv;
	LinkStack<char> sp;
	char c;
	int k = 0, flag = 1;
	double x, y;
	sp.Push('=');
	char *s = new char[100];
	cout << "请输入算式：" << endl;
	cin >> s;
	c = s[0];
	while (flag)
	{
		if (c >= '0'&&c <= '9' || c == '.')
		{
			sv.Push(get(s, k));//操作数压栈 
		}
		else if (c == '='&& sp.Top() == '=')
		{
			flag = 0;//退出循环 
		}
		else if (c == '(' || (priority(c) > priority(sp.Top())))
		{
			sp.Push(c);
			k++;
		}
		else if (c == ')'&& sp.Top() == '(')
		{
			sp.Pop();
			k++;
		}
		else if (priority(c) <= priority(sp.Top()))
		{
			x = sv.Top();
			sv.Pop();
			y = sv.Top();
			sv.Pop();
			c = sp.Top();
			sp.Pop();
			switch (c)
			{
			case '+':y = x + y; break;
			case '-':y = y - x; break;
			case '*':y = x*y; break;
			case '/':y = y / x; break;
			}
			sv.Push(y);
		}
		c = s[k];
	}
	cout << sv.Top() << endl;//输出最终计算结果 
	return 0;
}

