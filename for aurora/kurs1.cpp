#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

using namespace std;

class Base
{
private:
	string name;
	Base* head;
	int state;
	vector <Base*> subordinates;
public:
	Base(Base* head, string name = "Base_object");
	~Base();
	bool setName(string name);
	string getName();
	void setState(int state);
	int getState();
	void setHead(Base* head);
	Base* getHead();
	Base* getSubordinateByName(string subName);
	Base* findInSubTree(string name);
	void showTree();
};

Base::Base(Base* head, string name)
{
	Base* tmp = head;
	if(head) while(tmp->head) tmp = tmp->head; // finding root
	if(head && tmp->findInSubTree(name)) delete(this); //not creating object if name is occupied
	
	this->name = name;
	state = -1;
	this->head = head;
	if(head != nullptr)
	{
		head->subordinates.push_back(this);
	}
}

Base::~Base() //if commented then we're using shared ptr and this will be done automaticly
{
	//cout << name << " " << subordinates.size() << endl;
	//if(0 < subordinates.size()) cout << "a" << endl;
	//if(0 < subordinates.size()) delete subordinates[0];
	for(int i = 0; i < subordinates.size(); i++)
	{
		delete(subordinates[i]);	
	}
}

bool Base::setName(string name)
{
	Base* tmp = this;
	while(tmp->head) tmp = tmp->head; // finding root
	if(!(tmp->findInSubTree(name))) //no object with such name found (we can use it)
	{
		this->name = name;
		return true;
	}
	return false;
	//this->name = name;
}

string Base::getName()
{
	return name;
}

void Base::setState(int state)
{
	this->state = state;
}

int Base::getState()
{
	return state;
}

void Base::setHead(Base* head)
{
	this->head->subordinates.erase(find(subordinates.begin(), subordinates.end(), this)); //deleting "this" from previous head
	this->head = head;
	head->subordinates.push_back(this);
}

Base* Base::getHead()
{
	return this->head;
}

Base* Base::getSubordinateByName(string subName)
{
	for(int i = 0; i < this->subordinates.size(); i++)
	{
		if(subordinates[i]->name == subName) return subordinates[i];
	}
	return nullptr;
}

void Base::showTree()
{
	if(subordinates.size() > 0)
	{
		cout << endl << name;
		for(int i = 0; i < subordinates.size(); i++)
		{
			cout << "  " << subordinates[i]->name;
		}
		for(int i = 0; i < subordinates.size(); i++)
		{
			subordinates[i]->showTree();
		}
	}
}

Base* Base::findInSubTree(string name)
{
	if(this->name == name) return(this);
	Base* searched;
	for(int i = 0; i < this->subordinates.size(); i++)
	{
		searched = subordinates[i]->findInSubTree(name);
		if(searched) return(searched);
	}
	return(nullptr);
}


class Child2 : public Base
{
public:
	Child2(Base* head, string name = "Base_object") : Base(head, name) {}
};


class Application : public Base
{
private:
	//vector<shared_ptr<Base>> allSubObj;
public:
	Application(Base* head, string name = "Base_object") : Base(head, name) {}
	void buildTree();
	void startApp();
};


void Application::buildTree()
{
	//ask what to do here, cause we have nothing to work with before the input
}

void Application::buildTree()
{
	string headName;
	cin >> headName;

	this->setName(headName);
	string subName;
	cin >> headName >> subName;
	//vector<shared_ptr<Child2>> allSubObj; //storing pointers to all the subordinate objects
	//Base* parent = this;
	Child2* x = nullptr;
	while(headName != subName)
	{
		Base* tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
		//if(tmpHead) allSubObj.push_back(make_shared<Child2>(tmpHead, subName));
		//if(tmpHead) shared_ptr<Child2> = make_shared<Child2>(tmpHead, subName);
		//Base* tmpHead = parent;
		//if(x && headName == x->getName()) parent = (Base*)x;
		//x = new Child2(parent, subName);
		if(tmpHead) x = new Child2(tmpHead, subName);
		cin >> headName >> subName;
	}
}

void Application::startApp()
{
	cout << getName();
	showTree();
}


int main()
{
	Application app(nullptr);
	app.buildTree();
	app.startApp();
	return(0);
}