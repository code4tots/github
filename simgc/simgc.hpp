// Simple garbage collector in C++
#ifndef SIMGC_HPP
#define SIMGC_HPP

#include<map>
#include<string>
namespace Simgc{
using std::map;
using std::string;

class Object{
public:
	// constructor methods.
	static void newInteger(string name){}
	

private:
	// Constructor is made private.
	// Object instances should only be created under careful supervision.
	Object(string name){}
	
	
	
	
	// Keep track of 
	
	
	// Fields.
	// Object type is either "Object", "int", "char", or "None"
	string type;
	
	map<string,Object*> m;
	int i;
	char c;
};

};



#endif//SIMGC_HPP
