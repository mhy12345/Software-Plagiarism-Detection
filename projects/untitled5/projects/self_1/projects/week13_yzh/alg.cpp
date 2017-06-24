#include "alg.h"

alg::alg() {}
alg::~alg() {}

KarpRabin::KarpRabin(){}
KarpRabin::~KarpRabin(){data.clear(); vector <string>(data).swap(data);} //release the vector

/*
  Two procedures for reading were both designed for Windows.
  For Mac OS or Linux, please replace the '\' with '/' in the directory, and
  rewrite the makefile-clean with "rm -f *.exe"... 
*/
void KarpRabin::read(){
	string tmp;
	
	ifstream fin1("data/src1.txt");
	while (getline(fin1, tmp)) data.push_back(tmp);
	fin1.close();
	
	ifstream fin2("data/src2.txt");
	while (getline(fin2, tmp)) data.push_back(tmp);
	fin2.close();
	
	ifstream fin3("data/src3.txt");
	while (getline(fin3, tmp)) data.push_back(tmp);
	fin3.close();

	ifstream fin4("data/src4.txt");
	while (getline(fin4, tmp)) data.push_back(tmp);
	fin4.close();

	ifstream fin5("data/src5.txt");
	while (getline(fin5, tmp)) data.push_back(tmp);
	fin5.close();	
	
	//a special case, which can show that KarpRabin is worse than KMP...
/*	
	ifstream fin6("data/src6.txt");
	while (getline(fin6, tmp)) data.push_back(tmp);
	fin6.close();		
*/
}
void KarpRabin::alg_interface(string str1){
	int len1 = str1.size();
	int hash1 = 0;
	for (int i=0; i!=len1; ++i) hash1 = (hash1*2 % MOD + str1[i]) % MOD;
	cout<<hash1<<endl;
	
	int base = (1 << (len1-1)) % MOD;

	int ans = 0;
	for (int i = 0; i != data.size(); ++i){
		string str0 = data[i];
		int len0 = str0.size();
		if (len0 < len1) continue;
		int hash0 = 0;
		for (int j=0; j!=len1-1; ++j) hash0 = (hash0*2 % MOD + str0[j]) % MOD;
		
		for (int j = len1-1; j != len0; ++j){
			hash0 = ((hash0 - (j>=len1 ? base * str0[j-len1] % MOD : 0) + MOD) * 2 + str0[j]) % MOD;		
			//compare if the hash value equals
			if (hash0 == hash1){
				bool flag = true;
				for (int k=j-len1+1; k!=j+1; ++k)
					if (str0[k]!=str1[k-j+len1-1]) {flag = false; break;}
				if (flag) ans++;
			}
		}
	}
	
	cout<<"Total times of "<<str1<<" : "<<ans<<endl;
}

KMP::KMP(){}
KMP::~KMP(){data.clear(); vector <string>(data).swap(data);}
void KMP::read(){
	string tmp;
	
	ifstream fin1("data/src1.txt");
	while (getline(fin1, tmp)) data.push_back(tmp);
	fin1.close();
	
	ifstream fin2("data/src2.txt");
	while (getline(fin2, tmp)) data.push_back(tmp);
	fin2.close();
	
	ifstream fin3("data/src3.txt");
	while (getline(fin3, tmp)) data.push_back(tmp);
	fin3.close();

	ifstream fin4("data/src4.txt");
	while (getline(fin4, tmp)) data.push_back(tmp);
	fin4.close();

	ifstream fin5("data/src5.txt");
	while (getline(fin5, tmp)) data.push_back(tmp);
	fin5.close();	
/*
	ifstream fin6("data/src6.txt");
	while (getline(fin6, tmp)) data.push_back(tmp);
	fin6.close();	
*/
}
void KMP::alg_interface(string str1){	
	int len1 = str1.size();
	next[0] = -1; int j;
	
	//array of next[] indicates where to go when failing to match
	for (int i = 1; i!=len1; ++i){
		j = next[i-1]; 
		while (j>=-1 && str1[j+1] != str1[i]) j= (j!=-1 ? next[j] : -2);
		next[i] = j+1;
	}

	int ans = 0;
	for (int i = 0; i != data.size(); ++i){
		string str0 = data[i];
		int len0 = str0.size(); int k = -1;
		if (len0 < len1) continue;
		for (int j = 0; j!=len0; ++j){
			while (k>=-1 && str1[k+1]!=str0[j]) k = (k!=-1 ? next[k] : -2); 
			k++;
			if (k == len1-1) ans++, k = next[k];
		}
	}
	
	cout<<"Total times of "<<str1<<" : "<<ans<<endl;
}

Test::Test(alg* alg){
    this->_alg = alg;
}
Test::~Test(){
    delete this->_alg;
}
void Test::tenPattern(){
	clock_t tnow = clock();
	this->_alg->read();
	
	//ten randomly-selected patterns
	this->_alg->alg_interface(string("friendvoidprotobuf"));
	this->_alg->alg_interface(string("Thisfilewasgenerate"));
	this->_alg->alg_interface(string("google/protobuf"));
	this->_alg->alg_interface(string("_repeated_packed_"));	
	this->_alg->alg_interface(string("staticconst"));
	this->_alg->alg_interface(string("DONOTEDIT!"));
	this->_alg->alg_interface(string("constEnumDescriptor"));
	this->_alg->alg_interface(string("Bufferheaders"));
	this->_alg->alg_interface(string("ImportNoArenaNested"));
	this->_alg->alg_interface(string("_google_2fprotobuf_"));	
	this->_alg->alg_interface(string("d0F"));	
	this->_alg->alg_interface(string("F0d"));	

	//one artificially-constructed pattern
//	this->_alg->alg_interface(string("aaaaaaaaaa"));
	cout << "Total Time : "<<(clock() - tnow)*1.0/1000<<endl;
}
