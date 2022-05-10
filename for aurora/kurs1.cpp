#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

using namespace std;

class Base;

typedef void(Base::*TYPE_SIGNAL)(string&);
typedef void(Base::*TYPE_HANDLER)(string);
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)

class Base
{
private:
	string name;
	Base* head;
	int state;
	vector <Base*> subordinates;

	vector<Base*> receivers;
	vector<TYPE_SIGNAL> signals; //signal which can be sent to the receiver
	vector<Base*> senders;
	vector<TYPE_HANDLER> handlers; //handler which will be used for a signal from a certain sender
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
	Base* findByName(string name);
	void showTree(int depth = 0);
	void showTreeState(int depth = 0);
	Base* findByPath(string path);
	string getPath();
	void set_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler);
};

Base::Base(Base* head, string name)
{
	Base* tmp = head;
	if(head) while(tmp->head) tmp = tmp->head; // finding root
	//if(head && tmp->findInSubTree(name)) delete(this); //not creating object if name is occupied
	
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
	else cout << "Object tree" << endl;
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

Base* Base::findByName(string name)
{
	Base* tmp = this;
	while(tmp->head) tmp = tmp->head; // finding root
	return(tmp->findInSubTree(name));
}

Base* Base::findByPath(string path)
{
	if(!this || path.empty()) return(nullptr);
	if(path.substr(0, 2) == "//"){
		return findByName(path.substr(2));
	}
	if(path.substr(0, 1) == "/"){ // / or /sth or /sth/sth
		//cout << path << endl;
		int nextSlash = path.find("/", 1); 
		Base* tmpRoot = this;
		while(tmpRoot->head) tmpRoot = tmpRoot->head; // finding root
		//cout << nextSlash << endl;

		if(nextSlash == -1 && path.size() == 1) return tmpRoot; //root

		if(nextSlash == -1) return(tmpRoot->getSubordinateByName(path.substr(1))); // one after root
		Base* tmp = tmpRoot->getSubordinateByName(path.substr(1, nextSlash - 1)); //more than one after root
		return(tmp->findByPath(path.substr(nextSlash + 1))); //if tmp = nullptr then findByPath returns nullptr
	}
	else if(path.substr(0, 1) == "."){
		if(path.size() == 1) return(this); // just .
		return(this->findByPath(path.substr(2))); // ./sth
	}
	else{
		//cout << path << endl;
		int nextSlash = path.find("/"); 
		if(nextSlash == -1) return(this->getSubordinateByName(path)); // one after our element
		Base* tmp = this->getSubordinateByName(path.substr(0, nextSlash)); //more than one after our element
		return(tmp->findByPath(path.substr(nextSlash + 1)));
	}

}

string Base::getPath()
{
	string path = "";
	Base* tmp = this;
	while(tmp->head){ // there is a head
		path += "/" + tmp->name;
	}
	path += "/";
	return path;
}


void Base::set_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler)
{
	if(!this || !destination) return;
	this->receivers.push_back(destination);
	this->signals.push_back(signal);
	destination->senders.push_back(this);
	destination->handlers.push_back(handler);
}



class Child2 : public Base
{
public:
	Child2(Base* head, string name = "Base_object") : Base(head, name) {}
	void signal(string& mes){
		mes += " (class: 2)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};
class Child3 : public Base
{
public:
	Child3(Base* head, string name = "Base_object") : Base(head, name) {}
	void signal(string& mes){
		mes += " (class: 3)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};
class Child4 : public Base
{
public:
	Child4(Base* head, string name = "Base_object") : Base(head, name) {}
	void signal(string& mes){
		mes += " (class: 4)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};
class Child5 : public Base
{
public:
	Child5(Base* head, string name = "Base_object") : Base(head, name) {}
	void signal(string& mes){
		mes += " (class: 5)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};
class Child6 : public Base
{
public:
	Child6(Base* head, string name = "Base_object") : Base(head, name) {}
	void signal(string& mes){
		mes += " (class: 6)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};


class Application : public Base
{
private:
	//vector<shared_ptr<Base>> allSubObj;
public:
	Application(Base* head, string name = "Base_object") : Base(head, name) {}
	bool buildTree();
	void startApp();
	void errorOut(string headPath);
	void signal(string& mes){
		mes += " (class: 1)";
		cout << "Signal from " << this->getPath() << endl;
	}
	void handler(string mes){cout << "Signal to " << this->getPath() << " Text: " << mes << endl;}
};

void Application::errorOut(string headPath)
{
	showTree();
	cout << endl << "The head object " << headPath << " is not found";
}

bool Application::buildTree()
{
	string headName;
	cin >> headName;
	this->setName(headName);
	cin >> headName;
	while(headName != "endtree")
	{
		string subName;
		cin >> subName;
		int classNum;
		cin >> classNum;
		//need to remove check for unique as names are no longer unique
		Base* tmpHead = this->findByPath(headName); //tmpHead nullptr when not found
		if(tmpHead)
		{
			switch(classNum) //choosing class
			{
				case 2:
					new Child2(tmpHead, subName);
					break;
				case 3:
					new Child3(tmpHead, subName);
					break;
				case 4:
					new Child4(tmpHead, subName);
					break;
				case 5:
					new Child5(tmpHead, subName);
					break;
				case 6:
					new Child6(tmpHead, subName);
					break;
			}
		}
		else
		{
			errorOut(headName);
			return false;
		}
		
		cin >> headName;
	}
	return true;
}

void Application::startApp()
{
	showTree();
	Base* current = this->findByPath("/"); //hey what if start app was called not from root, then just this would be bad
	string command;
	string path;
	cin >> command;
	while(command != "END"){
		cin >> path;
		if(command == "FIND"){
			Base* tmp = current->findByPath(path);
			if(!tmp) cout << endl << path << "     Object is not found";
			else cout << endl << path << "     Object name: " << tmp->getName();
		}
		else{ //command is SET (yes this is cheating)
			Base* tmp = current->findByPath(path);
			if(!tmp) cout << endl << "Object is not found: " << current->getName() << " " << path;
			else{
				current = tmp;
				cout << endl << "Object is set: " << current->getName();
			}
		}
		cin >> command;
	}
}


int main()
{
	Application app(nullptr);
	if(app.buildTree()) app.startApp();
	return(0);
}