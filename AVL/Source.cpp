#include<iostream>
#include"AVLtree.h"
#include<vector>
#include<string>

using namespace std;
int main() {
	TreeSet<double> tr;
	TreeSet<double> tr0;
	for (int i = 0; i < 10; i++) {
		//tr.insert(50);
		tr.insert(rand() % 200+3.14);
		tr0.insert(rand() % 200 / 10.0 + 3.1);
		/*string s = "cheb" ;
		s += (char)(rand() % 200);
		tr.insert(s);*/
	}
	for (node<double>* x : tr)
		cout << x->key << " ";
	tr.makePic("tr.png");
	tr0.makePic("tr0.png");
	(tr+tr0).makePic("trPLUStr0.png");
	(tr - tr0).makePic("trMINUStr0.png");
	tr0 += tr;
	tr0.makePic("tr0PLUStr.png");
	(tr0-tr).makePic("tr00.png");
	TreeSet<string> tr2;
	for (int i = 0; i < 20; i++) {
		//tr.insert(rand() % 200 + 3.14);
		string s = "cheb" ;
		s += (char)(rand() % 20+65);
		tr2.insert(s);
	}
	TreeSet<int> tr3;
	for (int i = 0; i < 50; i++) {
		tr3.insert(rand() % 500);
	
	}
	iter<double> it = tr.getIter();

	int num = 0;
	while (*it) {
		num++;
		cout << it->key << " ";
		it++;
	}
	cout << endl << num << endl;
	1 + it;
	it = tr.getIter() + 4; 
	it--;


	iter<double> it2 = tr.getIter();
	cout << it2++->key << " ";
	it2 += 2;
	//it2=tr.getIter();
	int k=it2->key;
	cout << ((--it2)+3)->key << " ";
	cout << it[5]->key << " ";
	if (it <= it2) {}
	else if (it > it2) cout << (3 + it2)->key << " ";
	tr.makePic("kek.png");
	tr2.makePic("kek2.png");
	tr3.makePic("kek3.png");
	
	return 0;
}
