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
	void showTree(int depth = 0);
	void showTreeState(int depth = 0);
};

Base::Base(Base* head, string name)
{
	Base* tmp = head;
	if(head) while(tmp->head) tmp = tmp->head; // finding root
	if(head && tmp->findInSubTree(name)) delete(this); //not creating object if name is occupied
	
	this->name = name;
	state = 0;
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
	if(this->head)
	{
		if(this->head->state)
		{
			this->state = state;
			if(state == 0) for(int i = 0; i < subordinates.size(); i++) subordinates[i]->setState(0);
		}
	}
	else
	{
		this->state = state;
		if(state == 0) for(int i = 0; i < subordinates.size(); i++) subordinates[i]->setState(0);
	}
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

void Base::showTree(int depth)
{
	if(this->head) cout << endl;
	for(int i = 0; i < depth; i++) cout << "    ";
	cout << name;
	for(int i = 0; i < subordinates.size(); i++) subordinates[i]->showTree(depth + 1);	
}

void Base::showTreeState(int depth)
{
	if(this->head) cout << endl;
	for(int i = 0; i < depth; i++) cout << "    ";
	if(state) cout << name << " is ready";
	else cout << name << " is not ready";
	for(int i = 0; i < subordinates.size(); i++) subordinates[i]->showTreeState(depth + 1);
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
class Child3 : public Base
{
public:
	Child3(Base* head, string name = "Base_object") : Base(head, name) {}
};
class Child4 : public Base
{
public:
	Child4(Base* head, string name = "Base_object") : Base(head, name) {}
};
class Child5 : public Base
{
public:
	Child5(Base* head, string name = "Base_object") : Base(head, name) {}
};
class Child6 : public Base
{
public:
	Child6(Base* head, string name = "Base_object") : Base(head, name) {}
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
	string headName;
	cin >> headName;

	this->setName(headName);

	bool flag = true; // true - building tree; false - changing status
	while(!cin.eof())
	{
		cin >> headName;
		if(flag) // building tree
		{
			if(headName == "endtree")
			{
				flag = false;
				continue;
			}
			string subName;
			cin >> subName;
			int classNum;
			cin >> classNum;
			switch(classNum) //choosing class
			{
				Base* tmpHead;
				case 2:
					tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
					if(tmpHead) new Child2(tmpHead, subName);
					break;
				case 3:
					tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
					if(tmpHead) new Child3(tmpHead, subName);
					break;
				case 4:
					tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
					if(tmpHead) new Child4(tmpHead, subName);
					break;
				case 5:
					tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
					if(tmpHead) new Child5(tmpHead, subName);
					break;
				case 6:
					tmpHead = this->findInSubTree(headName); //if to make sure we won't create another tree with no access
					if(tmpHead) new Child6(tmpHead, subName);
					break;
			}
		}
		else //changing status
		{
			int newStatus;
			cin >> newStatus;
			Base* tmpHead = this->findInSubTree(headName);
			tmpHead->setState(newStatus);
		}
	}
}

void Application::startApp()
{
	cout << "Object tree" << endl;
	showTree();
	cout << endl << "The tree of objects and their readiness" << endl;
	showTreeState();
}


int main()
{
	Application app(nullptr);
	app.buildTree();
	app.startApp();
	return(0);
}