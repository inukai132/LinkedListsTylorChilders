#include <iostream>
#include <exception>
#include <string>
using namespace std;

class Link
{
	int value;
	Link* next;
public:
	Link* getNext() { return next; }
	void setNext(Link* _next) { this->next = _next; }
	int getValue() { return value; }
	void setValue(int _value) { this->value = _value; }
	Link(int _value) { this->value = _value; }
	Link() {}
	~Link() 
	{
		this->value = NULL;
		this->next = NULL;
	}

	static Link* GetNode(Link* firstLink, int pos)
	{
		Link* cur = firstLink;
		while (pos > 0)
		{
			if (cur->getNext() == NULL)
				return NULL;
			cur = cur->getNext();
			pos--;
		}
		return cur;
	}

	static int GetValue(Link* firstLink, int pos)
	{
		return GetNode(firstLink, pos)->getValue();
	}

	static void Push(Link* firstLink, int value)
	{
		Link* node = new Link;
		node->setValue(value);
		Link* cur = firstLink;
		while (cur->getNext())
			cur = cur->getNext();
		cur->setNext(node);
	}

	static void Add(Link** firstLink, int value, int pos)
	{
		Link* node = new Link(value);
		Link* headRoom = new Link(-1);
		headRoom->setNext(*firstLink);
		Link* cur = headRoom;
		while (cur->getNext() && pos > 0)
		{
			cur = cur->getNext();
			pos--;
		}
		node->setNext(cur->getNext());
		cur->setNext(node);
		*firstLink = headRoom->getNext();
	}

	static void Remove(Link** firstLink, int pos)
	{
		Link* headRoom = new Link(-1);
		headRoom->setNext(*firstLink);
		Link* cur = headRoom;
		while (cur->getNext() && pos > 0)
		{
			cur = cur->getNext();
			pos--;
		}
		cur->setNext(cur->getNext()->getNext());
		*firstLink = headRoom->getNext();
	}

	static string OutputList(Link* list)
	{
		Link* cur = list;
		string output = "";
		while (cur != NULL)
		{
			output += to_string(cur->getValue()) + " ";
			cur = cur->getNext();
		}
		return output.substr(0, output.size() - 1);
	}

	static Link* interweave(Link* L1, Link* L2, int step)
	{
		Link* L3 = new Link();
		int stepper = 0;
		while (L1)
		{
			if (stepper == step && L2)
			{
				Push(L3, L2->getValue());
				stepper = 0;
				L2 = L2->getNext();
			}
			else
			{
				Push(L3, L1->getValue());
				stepper++;
				L1 = L1->getNext();
			}
		}
		return L3->getNext();
	}
};


int main()
{
	int numEl;
	cin >> numEl;
	Link* initList = new Link();
	while (numEl > 0)
	{
		int el;
		cin >> el;
		Link::Push(initList, el);
		numEl--;
	}
	initList = initList->getNext();
	int numAdd;
	cin >> numAdd;
	while (numAdd > 0)
	{
		Link* addList = new Link();
		int step, numAddEl;
		cin >> step;
		cin >> numAddEl;
		while (numAddEl > 0)
		{
			int addEl;
			cin >> addEl;
			Link::Push(addList, addEl);
			numAddEl--;
		}
		addList = addList->getNext();
		initList = Link::interweave(initList, addList, step);
		numAdd--;
	}

	cout << Link::OutputList(initList);
	return 0;
}