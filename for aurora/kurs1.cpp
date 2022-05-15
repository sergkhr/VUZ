#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <typeinfo>
#include <type_traits>

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
	

	struct outcome{ //what goes from this object
		Base* receiver;
		TYPE_SIGNAL signal;
		TYPE_HANDLER handler;
		outcome(Base* receiver, TYPE_SIGNAL signal, TYPE_HANDLER handler):receiver(receiver), signal(signal), handler(handler){};
		bool operator==(const outcome& other) const{ 
			return(receiver==other.receiver && signal==other.signal && handler==other.handler);
		}
	};
	/*struct income{ //what comes to this object
		Base* sender;
		TYPE_HANDLER handler;
		income(Base* sender, TYPE_HANDLER handler):sender(sender), handler(handler){};
		bool operator==(const income& other) const{
			return(sender==other.sender && handler==other.handler);
		}
	};*/
	vector<outcome*> outcomes;
	//vector<income*> incomes;
protected:
	int childType;
public:
	Base(Base* head, string name = "Base_object");
	~Base();
	bool setName(string name);
	string getName();
	void setState(int state);
	void setStateForAll(int state);
	int getState();
	void setHead(Base* head);
	int getChildType(){return childType;}
	Base* getHead();
	Base* getSubordinateByName(string subName);
	Base* findInSubTree(string name);
	Base* findByName(string name);
	void showTree(int depth = 0);
	void showTreeState(int depth = 0);
	Base* findByPath(string path);
	string getPath();
	void set_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler);
	void delete_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler);
	void emit_signal(TYPE_SIGNAL signal, string mes);
	TYPE_SIGNAL getSignal();
	TYPE_HANDLER getHandler();
};



class Application : public Base
{
private:
	//vector<shared_ptr<Base>> allSubObj;
public:
	Application(Base* head, string name = "Base_object") : Base(head, name) {childType = 1;}
	bool buildTree();
	void startApp();
	void errorOut(string headPath);
	void signal(string& mes){
		mes += " (class: 1)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
};
class Child2 : public Base
{
public:
	Child2(Base* head, string name = "Base_object") : Base(head, name) {childType = 2;}
	void signal(string& mes){
		mes += " (class: 2)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
};
class Child3 : public Base
{
public:
	Child3(Base* head, string name = "Base_object") : Base(head, name) {childType = 3;}
	void signal(string& mes){
		mes += " (class: 3)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
};
class Child4 : public Base
{
public:
	Child4(Base* head, string name = "Base_object") : Base(head, name) {childType = 4;}
	void signal(string& mes){
		mes += " (class: 4)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
};
class Child5 : public Base
{
public:
	Child5(Base* head, string name = "Base_object") : Base(head, name) {childType = 5;}
	void signal(string& mes){
		mes += " (class: 5)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
};
class Child6 : public Base
{
public:
	Child6(Base* head, string name = "Base_object") : Base(head, name) {childType = 6;}
	void signal(string& mes){
		mes += " (class: 6)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}
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

void Base::setStateForAll(int state){ //setting starts from this, so if this->head has state 0, then nothing will happen
	if(this->head && this->head->state == 0){
		//cout << "vot rofl";
		return;
	}
	this->setState(state);
	for(int i = 0; i < subordinates.size(); i++){
		subordinates[i]->setStateForAll(state);
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
	if(!tmp->head) return "/";
	while(tmp->head){ // there is a head
		path = "/" + tmp->getName() + path;
		tmp = tmp->head;
	}
	return path;
}

void Base::set_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler)
{
	if(!this || !destination) return;
	outcome* out = new outcome(destination, signal, handler);
	//income* in = new income(this, handler);
	for(int i = 0; i < outcomes.size(); i++){
		if(*(outcomes[i]) == *out){
			//cout << "test_equal"; //this works, I checked
			delete out; //we don't push back here, so we need to destroy
			//delete in;
			return; //no equal connections
		}
	}
	this->outcomes.push_back(out); //new outcome and income will bedestroyed by class destructor
	//this->incomes.push_back(in);
}

void Base::delete_connection(TYPE_SIGNAL signal, Base* destination, TYPE_HANDLER handler)
{
	//cout << "delete";
	if(!this || !destination) return;
	outcome* out = new outcome(destination, signal, handler);
	//income* in = new income(this, handler);
	{//blocked them to deal with error of "it" not changing type properly
		int ind = -1;
		for(int i = 0; i < outcomes.size(); i++){
			if(*(outcomes[i]) == *out) ind = i;
		}
		//auto it = find(outcomes.begin(), outcomes.end(), out); //does not work, dunno why
		if(ind != -1){
			//cout <<"d";
			delete outcomes[ind]; //don't know wheter only one or both delete and erase
			this->outcomes.erase(outcomes.begin() + ind); //potential memory leak if left alone
			//cout << "test_delete_out";
		}
		//check whether the overloaded operator == is working
	}
	/*{
		int ind = -1;
		for(int i = 0; i < incomes.size(); i++){
			if(*(incomes[i]) == *in) ind = i;
		}
		//auto it = find(incomes.begin(), incomes.end(), in);
		if(ind != -1){
			delete incomes[ind];
			destination->incomes.erase(incomes.begin() + ind); //potential memory leak if left alone
			cout << "test_delete_in";
		}
	}*/
	//delete out;
	//delete in;
}

void Base::emit_signal(TYPE_SIGNAL signal, string mes){
	if(!this || state == 0){
		//cout << "not emitting ";
		return; //if this is nullptr or obj is not active we do nothing
	}
	(this->*signal)(mes);
	for(int i = 0; i < outcomes.size(); i++){
		if(outcomes[i]->signal == signal){
			Base* destination = outcomes[i]->receiver;
			if(destination->getState() != 0){
				(destination->*(outcomes[i]->handler))(mes);
			}
			// for(int j = 0; destination->state != 0 && j < (destination->incomes).size(); j++){ //we also act only if destination object is active
			// 	cout << "test " << (this->outcomes).size();
			// 	if((destination->incomes[j])->sender == this){ //found the connection
			// 		(destination->*((destination->incomes[j])->handler))(mes);
			// 	}
			// }
		}
	}
}

TYPE_SIGNAL Base::getSignal(){
	switch(this->getChildType()){
		case 1: 
			return SIGNAL_D(Application::signal);
			break;
		case 2: 
			return SIGNAL_D(Child2::signal);
			break;
		case 3: 
			return SIGNAL_D(Child3::signal);
			break;
		case 4: 
			return SIGNAL_D(Child4::signal);
			break;
		case 5: 
			return SIGNAL_D(Child5::signal);
			break;
		case 6: 
			return SIGNAL_D(Child6::signal);
			break;
		default: 
			return nullptr;
			break;
	}
}

TYPE_HANDLER Base::getHandler(){
	switch(this->getChildType()){
		case 1: 
			return HANDLER_D(Application::handler);
			break;
		case 2: 
			return HANDLER_D(Child2::handler);
			break;
		case 3: 
			return HANDLER_D(Child3::handler);
			break;
		case 4: 
			return HANDLER_D(Child4::handler);
			break;
		case 5: 
			return HANDLER_D(Child5::handler);
			break;
		case 6: 
			return HANDLER_D(Child6::handler);
			break;
		default: 
			return nullptr;
			break;
	}
}





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
	//now connections (headName -> sender; subName -> receiver)
	//tmpHead->emit_signal(SIGNAL_D(remove_pointer<decltype(tmpHead)>::type::signal), message); //this is the closest I got to getting rid of switch casing. We use the type of tmpHead (the problem is that tmpHead is a pointer to a Base class, even if it's pointing to a Child, because we store Base*)
	cin >> headName;
	while(headName != "end_of_connections"){
		string subName;
		cin >> subName;
		Base* tmpHead = this->findByPath(headName);
		Base* tmpSub = this->findByPath(subName);
		//set_connection
		if(!tmpHead) cout << endl << "Object " << headName << " not found";
		else if(!tmpSub) cout << endl << "Handler object " << subName << " not found";
		else{
			tmpHead->set_connection(tmpHead->getSignal(), tmpSub, tmpSub->getHandler());
		}
		cin >> headName;
	}
	return true;
}

void Application::startApp()
{
	showTree();
	this->setStateForAll(1); //turning all objects on
	string command;
	cin >> command;
	while(command != "END"){
		if(command == "EMIT"){
			string path, text;
			cin >> path;
			getline(cin, text);
			text = text.substr(1); //getting rid of the first space
			Base* tmpHead = this->findByPath(path);
			if(!tmpHead) cout << endl << "Object " << path << " not found";
			else tmpHead->emit_signal(tmpHead->getSignal(), text);
		}
		else if(command == "SET_CONNECT"){
			string path1, path2;
			cin >> path1 >> path2;
			Base* tmpHead = this->findByPath(path1);
			Base* tmpSub = this->findByPath(path2);
			if(!tmpHead) cout << endl << "Object " << path1 << " not found";
			else if(!tmpSub) cout << endl << "Handler object " << path2 << " not found";
			else tmpHead->set_connection(tmpHead->getSignal(), tmpSub, tmpSub->getHandler());
		}
		else if(command == "DELETE_CONNECT"){
			string path1, path2;
			cin >> path1 >> path2;
			Base* tmpHead = this->findByPath(path1);
			Base* tmpSub = this->findByPath(path2);
			if(!tmpHead) cout << endl << "Object " << path1 << " not found";
			else if(!tmpSub) cout << endl << "Handler object " << path2 << " not found";
			else tmpHead->delete_connection(tmpHead->getSignal(), tmpSub, tmpSub->getHandler());
		}
		else if(command == "SET_CONDITION"){
			string path;
			int state;
			cin >> path >> state;
			Base* tmpHead = this->findByPath(path);
			if(!tmpHead) cout << endl << "Object " << path << " not found";
			else tmpHead->setState(state);
		}
		else cout << "Unknown command: " << command << endl;
		
		cin >> command;
	}
}


int main()
{
	Application app(nullptr);
	if(app.buildTree()) app.startApp();
	return(0);
}

/*
//for online compiler tests
#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <typeindex>

using namespace std;

//template <typename childType> class Base;
class Base;

//template<class T>
//using TYPE_SIGNAL = void(T::*)(string);
typedef void(Base::*TYPE_SIGNAL)(string);
//using SIGNAL_D(signal_f) = (TYPE_SIGNAL)(&signal_f)
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)

//template <typename childType>



class Base{
    public:
    //decltype() clnullptr;
    //virtual void sig(string mes) = 0;
    
    // type_info getType(){
    //     return(typeid(*this));
    // }
    void foo(TYPE_SIGNAL signal, string mes){
        cout << "base did it" << endl;
        (this->*signal)(mes);
    }
};

class Acl : public Base{
    public:
    // Acl(){
    //     Acl *tmp = nullptr;
    //     clnullptr = tmp;
    // }
    
    void sig(string mes)
    {
        cout << "it's A" << mes << endl;
    }
};

class Bcl : public Base{
    public:
    // Bcl(){
    //     Bcl *tmp = nullptr;
    //     clnullptr = tmp;
    // }
    void sig(string mes)
    {
        cout << "it's B" << mes << endl;
    }
};


int main()
{
    
    Acl* a = new Acl();
    Bcl* b = new Bcl();
    Base* baseB = b;
    //map<type_index, 
    string message = "lol";
    //cout << (baseB->getType()).name << endl;
    b->foo(SIGNAL_D(remove_pointer<decltype(b)>::type::sig), message);
    
    delete a;
    delete b;
    return 0;
}
*/