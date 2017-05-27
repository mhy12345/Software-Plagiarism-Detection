#include "alg.h"

int main(){
	//KarpRabin
	cout << "KarpRabin working..." << endl;
    alg* myalg = new KarpRabin();
    Test* myTest = new Test(myalg);
    myTest->tenPattern();
	cout << endl;
	
	//KMP
	cout << "KMP working..." << endl;
    myalg = new KMP();
    myTest = new Test(myalg);
    myTest->tenPattern();

    return 0;
}