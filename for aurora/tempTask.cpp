#include <iostream>
#include <vector>

using namespace std;

class Field
{
	private:
		int data;
		int mask;
	public:
		Field(int data, int mask) { this->data = data; this->mask = mask;}
		Field(const Field& other) : data(other.data), mask(other.mask){}
		int getData() const { return data; }
		void setData(int data) { this->data = data; }
		int getMask() const { return mask; }
		void setMask(int mask) { this->mask = mask; }
		Field& operator|(const Field& other);
		Field& operator&(const Field& other);

};

Field& Field::operator&(const Field& other)
{
	int activeMask = this->mask & other.mask;
	int changes = activeMask & (this->data & other.data);
	this->data = (this->data & ~activeMask) | changes;
	return (*this);
}

Field& Field::operator|(const Field& other)
{
	int activeMask = this->mask & other.mask;
	int changes = activeMask & (this->data | other.data);
	this->data = (this->data & ~activeMask) | changes;
	return (*this);
}

int main() 
{
	int n;
	cin >> n;
	vector<Field> fields;
	for(int i = 0; i < n; ++i)
	{
		int tmpData, tmpMask;
		cin >> hex >> tmpData >> tmpMask;
		fields.push_back(Field(tmpData, tmpMask));
	}

	int lastOp = 0;
	while(!(cin.eof()))
	{
		int n1, n2;
		char act;
		cin >> n1 >> act >> n2;
		switch(act){
			case '|':
				fields[n1-1] = fields[n1-1] | fields[n2-1];
				lastOp = n1-1;
				break;
			case '&':
				fields[n1-1] = fields[n1-1] & fields[n2-1];
				lastOp = n1-1;
				break;
		}
	}

	cout << hex << fields[lastOp].getData();
	return 0;
}