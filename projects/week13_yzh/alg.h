#ifndef alg_h
#define alg_h

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
#include <algorithm>
#include <vector>

const int MOD = 10007; //const MOD for KarpRabin

using namespace std;

//Using strategy pattern...
class alg{
public:
	~alg();
	virtual void read() = 0;
	virtual void alg_interface(string str1) = 0;
protected:
	alg();
private:
};

class KarpRabin : public alg{
public:
	vector <string> data; //storage of the read data
	KarpRabin();
	~KarpRabin();
	virtual void read();
	virtual void alg_interface(string str1);
protected:
private:		
};

class KMP : public alg{
public:
	int next[21];
	vector <string> data; //storage of the read data
	KMP();
	~KMP();
	virtual void read();
	virtual void alg_interface(string str1);	
protected:
private:		
};

class Test{
public:
	Test(alg*);
    ~Test();
    void tenPattern();
private:
    alg* _alg;
};

#endif