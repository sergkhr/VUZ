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
typedef string(Base::*TYPE_HANDLER)(string);
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
	void emit_signal(TYPE_SIGNAL signal, string mes = "foo");
	int emit_FSSignal(TYPE_SIGNAL signal, string posI100J = "0");
	/*TYPE_SIGNAL getSignal();
	TYPE_HANDLER getHandler();*/
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
	/*void signal(string& mes){
		mes += " (class: 1)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	void tactSignal(string& placeholder){}
};

class Reader : public Base
{
public:
	Reader(Base* head, string name = "Base_object") : Base(head, name) {childType = 2;}
	/*void signal(string& mes){
		mes += " (class: 2)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	void insert(string& field);
};

class Brain : public Base
{
private:
	int entryPosi = -1;
	int entryPosj = -1;
	int entryPrintPosi = -1;
	int entryPrintPosj = -1;
	bool isOutside = true;
	bool isFirstOutput = true;
public:
	Brain(Base* head, string name = "Base_object") : Base(head, name) {childType = 3;}
	/*void signal(string& mes){
		mes += " (class: 3)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	void checkForwardSignal(string& placeholder){}
	void moveForwardSignal(string& placeholder){}
	void turnSignal(string& placeholder){}
	void printSignal(string& placeholder){}
	void getCoordsSignal(string& placeholder){}
	
	string findLabyrinthTact(string placeholder); //this is actually the main thing which performs the task 
};

class Field : public Base
{
private:
	vector<vector<int>> field;
public:
	Field(Base* head, string name = "Base_object") : Base(head, name) {childType = 4;}
	/*void signal(string& mes){
		mes += " (class: 4)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	string insertHandler(string fieldStr);
	string getFieldStateHandler(string posI100J);
};

class Bot : public Base
{
private:
	int posi = 0;
	int posj = 1;
	char facing = 'E'; //N; E; S; W;
public:
	Bot(Base* head, string name = "Base_object") : Base(head, name) {childType = 5; posi = 0; posj = 1; facing = 'E';}
	/*void signal(string& mes){
		mes += " (class: 5)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	void getFieldStateSignal(string& placeholder){} 
	void getFrontStateSignal(string& posI100J); //signal creates position by looking at facing variable
	
	string checkForwardHandler(string placeholder);
	string moveForwardHandler(string placeholder);
	string turnHandler(string direction); //diretion is "R" - for right; "L" - for left
	string getCoordsHandler(string placeholder);
	
	int getPosi(){return posi;}
	void setPosi(int posi){this->posi = posi;}
	int getPosj(){return posj;}
	void setPosj(int posj){this->posj = posj;}
	char getFacing(){return facing;}
	void setFacing(char facing){this->facing = facing;}
	
	void absoluteMove(char direction);
};

class Printer : public Base
{
public:
	Printer(Base* head, string name = "Base_object") : Base(head, name) {childType = 6;}
	/*void signal(string& mes){
		mes += " (class: 6)";
		cout << endl << "Signal from " << this->getPath();
	}
	void handler(string mes){cout << endl << "Signal to " << this->getPath() << " Text: " << mes;}*/
	string printHandler(string mes){
		cout << mes;
		return "";
	}
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
	for(int i = 0; i < outcomes.size(); i++)
	{
		delete(outcomes[i]);
	}
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
		else{//head->state = 0
			this->state = 0;
			for(int i = 0; i < subordinates.size(); i++) subordinates[i]->setState(0);
		}
	}
	else
	{
		this->state = state;
		if(state == 0) for(int i = 0; i < subordinates.size(); i++) subordinates[i]->setState(0);
	}
}

void Base::setStateForAll(int state){ //setting starts from this, so if this->head has state 0, then nothing will happen
	//if(this->head && this->head->state == 0) return;
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
			//cout << "test_equal"; //this works
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
			delete outcomes[ind]; //don't know wheter only one or both delete and erase
			this->outcomes.erase(outcomes.begin() + ind); //potential memory leak if left alone
			//cout << "test_delete_out";
		}
		//check whether the overloaded operator == is working
	}
	//delete out;
	//delete in;
}

void Base::emit_signal(TYPE_SIGNAL signal, string mes)
{
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

		}
	}
}

int Base::emit_FSSignal(TYPE_SIGNAL signal, string posI100J) //default coordinates will be erased by front signal, otherwise default is (0,0)
{
	//-2 means something is turned off or there is no such connection
	//cout << "emitting FSSignal" << endl;
	if(!this || state == 0){
		cout << "not emitting FSSignal" << state << endl;
		return -2;	
	}
	(this->*signal)(posI100J); //if it's a placeholder signal then nothing happens, otherwise we can decide the coordinate in signal method
	for(int i = 0; i < outcomes.size(); i++){
		if(outcomes[i]->signal == signal){
			Base* destination = outcomes[i]->receiver;
			if(destination->getState() != 0){
				return stoi((destination->*(outcomes[i]->handler))(posI100J));
			}
		}
	}
	return -2;
}

/*TYPE_SIGNAL Base::getSignal(){
	switch(this->getChildType()){
		case 1: return SIGNAL_D(Application::signal); //we return => we don't need a break
		case 2: return SIGNAL_D(Reader::signal);
		case 3: return SIGNAL_D(Brain::signal);
		case 4: return SIGNAL_D(Field::signal);
		case 5: return SIGNAL_D(Bot::signal);
		case 6: return SIGNAL_D(Printer::signal);
		default: return nullptr;
	}
}

TYPE_HANDLER Base::getHandler(){
	switch(this->getChildType()){
		case 1: return HANDLER_D(Application::handler);
		case 2: return HANDLER_D(Reader::handler);
		case 3: return HANDLER_D(Brain::handler);
		case 4: return HANDLER_D(Field::handler);
		case 5: return HANDLER_D(Bot::handler);
		case 6: return HANDLER_D(Printer::handler);
		default: return nullptr;
	}
}*/





void Application::errorOut(string headPath)
{
	showTree();
	cout << endl << "The head object " << headPath << " is not found";
}
	
bool Application::buildTree()
{
	this->setState(1);
	Reader* reader = new Reader(this, "reader");
	reader->setState(1);
	Brain* brain = new Brain(this, "brain");
	brain->setState(1);
	Field* field = new Field(this, "field");
	field->setState(1);
	Bot* bot = new Bot(this, "bot");
	bot->setState(1);
	Printer* printer = new Printer(this, "printer");
	printer->setState(1);
	//setStaet just in case, since we don't have actual user in our programm, we control everything
	
	reader->set_connection(SIGNAL_D(Reader::insert), (Base*)field, HANDLER_D(Field::insertHandler)); //the insertion signal
	
	bot->set_connection(SIGNAL_D(Bot::getFieldStateSignal), (Base*)field, HANDLER_D(Field::getFieldStateHandler)); //bot getting state of specific field //use emit_FSSignal
	bot->set_connection(SIGNAL_D(Bot::getFrontStateSignal), (Base*)field, HANDLER_D(Field::getFieldStateHandler)); //bot getting state of the field in front of it //use emit_FSSignal
	
	brain->set_connection(SIGNAL_D(Brain::checkForwardSignal), (Base*)bot, HANDLER_D(Bot::checkForwardHandler)); //command from brain to return what's infront
	brain->set_connection(SIGNAL_D(Brain::moveForwardSignal), (Base*)bot, HANDLER_D(Bot::moveForwardHandler)); //command from brain to move forward
	brain->set_connection(SIGNAL_D(Brain::turnSignal), (Base*)bot, HANDLER_D(Bot::turnHandler)); //command from brain to turn, the turn direction should be selected via parameter
	brain->set_connection(SIGNAL_D(Brain::getCoordsSignal), (Base*)bot, HANDLER_D(Bot::getCoordsHandler)); //command to get current bot coordinates
	
	brain->set_connection(SIGNAL_D(Brain::printSignal), (Base*)printer, HANDLER_D(Printer::printHandler)); // command from brain to print something
	
	this->set_connection(SIGNAL_D(Application::tactSignal), (Base*)brain, HANDLER_D(Brain::findLabyrinthTact));//tact signals from application
	
	return true;
}

void Application::startApp()
{
	Base* reader = this->findByPath("/reader");
	Base* field = this->findByPath("/field");
	
	//cout << reader->getName() << endl;

	int insertStatus = reader->emit_FSSignal(SIGNAL_D(Reader::insert));
	//cout << insertStatus << endl;
	if(!insertStatus) return; // we stop programm if insertStatus is 0 meaning that reader got SHOWTREE
	
	Base* brain = this->findByPath("/brain");
	int INeedMoreTime = this->emit_FSSignal(SIGNAL_D(Application::tactSignal));
	while(INeedMoreTime) INeedMoreTime = this->emit_FSSignal(SIGNAL_D(Application::tactSignal));
}


void Reader::insert(string& field)
{
	field = "";
	for(int i = 0; i < 22; i++){
		string tmp;
		cin >> tmp;
		if(tmp == "SHOWTREE"){
			Base* tmpRoot = this;
			while(tmpRoot->getHead()) tmpRoot = tmpRoot->getHead();
			tmpRoot->showTreeState();
			field =  "SHOWTREE"; //this means we have to end programm
			return;
			i--; //showtree does not count in the number of field lines
		}
		else{
			//tmp is a line of field
			field += tmp + "\n";
		}
	}
}


string Brain::findLabyrinthTact(string placeholder){ //it's a handler
	/*what we need:
		checkFront done: emit_FSSignal(SIGNAL_D(Brain::checkForwardSignal)); //1 - wall; 0 - space; -1 - out of bounds; -2 - error (there should be none)
		moveForward done: emit_signal(SIGNAL_D(Brain::moveForwardSignal));
		turnLeft done: emit_signal(SIGNAL_D(Brain::turnSignal), "L");
		turnRight done: emit_signal(SIGNAL_D(Brain::turnSignal), "R");
		print done: emit_signal(SIGNAL_D(Brain::printSignal), "whatever we need to print");
		get coords done: emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal)); //return posI100J
	*/
	
	if(isOutside && emit_FSSignal(SIGNAL_D(Brain::checkForwardSignal)) == -1){ //we are at the corner and the next turn is not a labyrinth entry
		emit_signal(SIGNAL_D(Brain::turnSignal), "R");
		emit_signal(SIGNAL_D(Brain::moveForwardSignal));
	}
	else{
		emit_signal(SIGNAL_D(Brain::turnSignal), "R"); //turn right, try to go, if can't then spin left
		bool turnedRight = true;
		while(emit_FSSignal(SIGNAL_D(Brain::checkForwardSignal)) != 0){
			emit_signal(SIGNAL_D(Brain::turnSignal), "L"); //while we can't move forward we turn left
			turnedRight = false;
		}
		if(isOutside && turnedRight){ //we have to remember the cell before the entry to print it, because the task wants us to, but only if on the outside road we turned right (no turns left during the spin)
			int entryCoords = emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal));
			entryPrintPosi = entryCoords / 100;
			entryPrintPosj = entryCoords % 100;
		}
		
		emit_signal(SIGNAL_D(Brain::moveForwardSignal));
		
		
		if(!isOutside){ //we were and are inside => have to check wheather we've found exit
			int curCoords = emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal));
			int posi = curCoords / 100;
			int posj = curCoords % 100;
			if(posi == 1 || posi == 22-2 || posj == 1 || posj == 22-2){ //it's an exit (22 is metainfo => size of field)
				if(posi == entryPosi && posj == entryPosj){ //exit = entry
					//There is no way out of the maze (1, 3)
					if(!isFirstOutput) emit_signal(SIGNAL_D(Brain::printSignal), "\n");
					emit_signal(SIGNAL_D(Brain::printSignal), "There is no way out of the maze (" + to_string(entryPrintPosi + 1) + ", " + to_string(entryPrintPosj + 1) + ")");
					isFirstOutput = false;
					emit_signal(SIGNAL_D(Brain::moveForwardSignal)); //get out of the maze to the outside road
					isOutside = true;
					emit_signal(SIGNAL_D(Brain::turnSignal), "R");
					emit_signal(SIGNAL_D(Brain::moveForwardSignal)); //move away from already checked entry
				}
				else{ //exit != entry
					//we'll have to move one step forward because the task thinks that the exit of the maze is the cell on the outside road
					emit_signal(SIGNAL_D(Brain::moveForwardSignal));
					
					curCoords = emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal));
					posi = curCoords / 100;
					posj = curCoords % 100;
					
					//Maze (14, 22) (12, 1)
					if(!isFirstOutput) emit_signal(SIGNAL_D(Brain::printSignal), "\n");
					emit_signal(SIGNAL_D(Brain::printSignal), "Maze (" + to_string(entryPrintPosi + 1) + ", " + to_string(entryPrintPosj + 1) + ") (" + to_string(posi + 1) + ", " + to_string(posj + 1) + ")");
					isFirstOutput = false;
					return("0"); //we found a maze, we finish
				}
			}
		}
		else if(turnedRight){//we are outside and we only turned right => we found entry to labyrinth => we have to remember it (if didn't turn just right => we proceed with outside road => we don't need to do anything)
			isOutside = false;
			int entryCoords = emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal));
			entryPosi = entryCoords / 100;
			entryPosj = entryCoords % 100;
			if(emit_FSSignal(SIGNAL_D(Brain::checkForwardSignal)) != 0){ //that's a one cell maze
				if(!isFirstOutput) emit_signal(SIGNAL_D(Brain::printSignal), "\n");
				emit_signal(SIGNAL_D(Brain::printSignal), "There is no way out of the maze (" + to_string(entryPrintPosi + 1) + ", " + to_string(entryPrintPosj + 1) + ")");
				isFirstOutput = false;
				emit_signal(SIGNAL_D(Brain::turnSignal), "R");
				emit_signal(SIGNAL_D(Brain::turnSignal), "R");
				emit_signal(SIGNAL_D(Brain::moveForwardSignal)); //get out of the maze to the outside road
				isOutside = true;
				emit_signal(SIGNAL_D(Brain::turnSignal), "R");
				emit_signal(SIGNAL_D(Brain::moveForwardSignal)); //move away from already checked entry
			}
		}
	}
	if(emit_FSSignal(SIGNAL_D(Brain::getCoordsSignal)) == 0) return "0"; //0 means 0*100 + 0 => (0,0)
	return "1"; //meaning we still have work, and we need more time ticks from application (0 is returned after we find a labytinth or we come to (0,0))
}


string Field::insertHandler(string fieldStr)
{
	// as we push_back, we can use this handler only once in programm, since there only one field, it's fine
	if(fieldStr == "SHOWTREE") return "0"; //means we have to stop the programm
	int lineLength = fieldStr.find("\n");
	for(int j = 0, i = 0; i*(lineLength + 1) + j < fieldStr.size(); j++){
		if(fieldStr[i*(lineLength + 1) + j] == '\n'){
			++i; // we go to the next line
			j = -1; //it'll become 0 on next iteration
		}
		else{
			if(j == 0) field.push_back(vector<int>()); //if the line is new we add a new line in field
			field[i].push_back((int)(fieldStr[i*(lineLength + 1) + j] - '0'));
		}
	}
	return "1"; //means everything's fine
	//need to uses emit_FSSignal(SIGNAL_D(Reader::insert)) and it'll return 0 or 1
}

string Field::getFieldStateHandler(string posI100J)
{
	int i = stoi(posI100J) / 100;
	int j = stoi(posI100J) % 100;
	if(i < 0 || i >= field.size() || j < 0 || j >= field[i].size()) return to_string(-1); //out of bounds
	return to_string(field[i][j]);
}


void Bot::absoluteMove(char direction)
{
	//direction can be 'u' - up; 'r' - right; 'd' - down; 'l' - left
	int newPosi;
	int newPosj;
	int posState = -2;
	switch(direction)
	{
		case 'u':
			//move up, check for walls and end of field
			newPosi = posi-1;
			newPosj = posj;
			break;
		case 'r':
			//move right, check for walls and end of field
			newPosi = posi;
			newPosj = posj+1;
			break;
		case 'd':
			//move down, check for walls and end of field
			newPosi = posi+1;
			newPosj = posj;
			break;
		case 'l':
			//move left, check for walls and end of field
			newPosi = posi;
			newPosj = posj-1;
			break;
		default:
			break;
	}
	posState = this->emit_FSSignal(SIGNAL_D(Bot::getFieldStateSignal), to_string(newPosi*100 + newPosj)); //1 - wall; 0 - space; -1 - out of bounds; -2 - error
	if(posState == 0){ //if we can we move
		posi = newPosi;
		posj = newPosj;
	}
}

void Bot::getFrontStateSignal(string& posI100J){
	int newPosi;
	int newPosj;
	switch(facing){
		case 'N':
			newPosi = posi-1;
			newPosj = posj;
			break;
		case 'E':
			newPosi = posi;
			newPosj = posj+1;
			break;
		case 'S':
			newPosi = posi+1;
			newPosj = posj;
			break;
		case 'W':
			newPosi = posi;
			newPosj = posj-1;
			break;
		default:
			cout << "facing error";
			break;
	}
	posI100J = to_string(newPosi*100 + newPosj);
}

string Bot::checkForwardHandler(string placeholder){
	string out = to_string( this->emit_FSSignal(SIGNAL_D(Bot::getFrontStateSignal)) );
	return out;
}

string Bot::moveForwardHandler(string placeholder){
	int newPosi;
	int newPosj;
	int posState = -2;
	switch(facing)
	{
		case 'N':
			//move up, check for walls and end of field
			newPosi = posi-1;
			newPosj = posj;
			break;
		case 'E':
			//move right, check for walls and end of field
			newPosi = posi;
			newPosj = posj+1;
			break;
		case 'S':
			//move down, check for walls and end of field
			newPosi = posi+1;
			newPosj = posj;
			break;
		case 'W':
			//move left, check for walls and end of field
			newPosi = posi;
			newPosj = posj-1;
			break;
		default:
			break;
	}
	posState = this->emit_FSSignal(SIGNAL_D(Bot::getFieldStateSignal), to_string(newPosi*100 + newPosj)); //1 - wall; 0 - space; -1 - out of bounds; -2 - error
	if(posState == 0){ //if we can we move
		posi = newPosi;
		posj = newPosj;
	}
	return "";
}

string Bot::turnHandler(string direction){
	//direction is "R" or "L"
	string directions = "NESWNESW";
	int faceInd = directions.find(facing);
	if(direction == "R") ++faceInd;
	if(direction == "L") faceInd += 4-1; //just -1 will throw us out of bounds on N
	facing = directions[faceInd];
	return "";
}

string Bot::getCoordsHandler(string placeholder){
	return(to_string(100*posi + posj));
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