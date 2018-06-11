#pragma once
#using <System.dll>
#include<string>
#include<fstream>
using namespace std;
using namespace System;
using namespace System::Diagnostics;
#include<iostream>
#include<exception>
#define dT template<class T>


class OutOfTree : public std::exception
{
public:
	virtual char* what() throw() {
		return "out of tree!!!";
	}
};
class leftOut : public OutOfTree
{
public:
	virtual char* what() throw() {
		return  "left operand is NULL (or both)";
	}
};
class rightOut : public OutOfTree {
public:
	virtual char* what() throw() {
		return  "right operand is NULL";
	}
};
class NullIter : public  std::exception {
public:
	virtual  char* what() throw() {
		return "iterator is NULL";
	}
};

dT struct node;
dT class TreeSet;
dT class iter;


dT inline bool operator==(const iter<T>& __lhs, const iter<T>& __rhs);
dT inline bool operator!=(const iter<T>& __lhs, const iter<T>& __rhs);
dT inline bool operator<(const iter<T>& lhs, const iter<T>& rhs);
dT inline bool operator>(const iter<T>& lhs, const iter<T>& rhs);
dT inline bool operator<=(const iter<T>& lhs, const iter<T>& rhs);
dT inline bool operator>=(const iter<T>& lhs, const iter<T>& rhs);
dT inline iter<T> operator+(std::size_t n, const iter<T>& __i);


dT struct node {
	node* left; node* right;
	node* prev; node* next;
	T key;
	int height;
	node(T k) :key(k) {
		right = left = prev=next=0;
		height = 1;
	}
	node* operator[](int n)
	{
		node* tt = this;
		for (int i = 0; i < n; i++)
			tt = tt->next;
		return tt;
	}
};
dT class TreeSet {
private:
	node<T>* root;
	int size;
	T minKey;
protected:
	int getheight(node<T>*p);
	int deltah(node<T>*p);
	void fixh(node<T>* a);
	node<T>*  rotateL(node<T>* a);
	node<T>* rotateR(node<T>*a);
	node<T>* balance(node<T>* p);
	node<T>* Fmin(node<T>* p);
	node<T>* insert(node<T>* p, T k, node<T>* pr, bool isLeft);
	node<T>* remove(node<T>* p, T k);
	void makeDot();
	
public:	
	TreeSet() { node<T>* root = 0; size = 0; }
	void insert(T k);
	void remove(T k);
	iter<T> getIter();
	bool exist(T);
	void print();
	void makePic(String^);
	void clear();
	T min();
	T max();
	int getSize();
	TreeSet<T>& operator=(TreeSet<T>&);
	 TreeSet<T>& operator=(T&);
	 TreeSet<T> operator+(TreeSet<T>);
	 TreeSet<T> operator+(T&);
	 TreeSet<T> operator-(TreeSet<T>&);
	 TreeSet<T> operator-(T&);
	 void operator+=(TreeSet<T>&);
	 void operator+=(T&);
	 void operator-=(TreeSet<T>&);
	 void operator-=(T&);
	 iter<T> begin();
	 iter<T> end();
};
dT class iter : public std::iterator<std::input_iterator_tag, TreeSet<T>> {
protected:
	node<T>* p;
public:
	explicit iter(node<T>* i) : p(i) { }
	const node<T>* operator*() const;
	node<T>* operator*();
	node<T>* operator->() const;
	iter& operator++();
	iter operator++(int);
	iter& operator--();
	iter operator--(int);
	const node<T>* operator[](const std::size_t& n) const;
	node<T>* operator[](const std::size_t& n);
	iter& operator+=(const std::size_t& n);
	iter operator+(const std::size_t& n) const;
	iter& operator-=(const std::size_t& n);
	iter operator-(const std::size_t& n) const;
	node<T>* base() const;
};

dT int TreeSet<T>::getheight(node<T>*p) {
	return p ? p->height : 0;
}
dT int TreeSet<T>::deltah(node<T>*p) {
	return  getheight(p->right) - getheight(p->left);
}
dT void TreeSet<T>::fixh(node<T>* a) {
	int hl = getheight(a->left);
	int hr = getheight(a->right);
	a->height =(hl > hr ? hl : hr)+1;
}
dT node<T>*  TreeSet<T>::rotateL(node<T>* a) {
	node<T>* b = a->right;
	a->right = b->left;
	b->left = a;
	fixh(a); fixh(b);
	return b;
}
dT node<T>* TreeSet<T>::rotateR(node<T>*a) {
	node<T>* b = a->left;
	a->left = b->right;
	b->right = a;
	fixh(a);
	fixh(b);
	return b;
}
dT node<T>* TreeSet<T>::balance(node<T>* p) {
	fixh(p);
	if (deltah(p) == 2) {
		if (deltah(p->right) <0)
			p->right = rotateR(p->right);
		return rotateL(p);
	}
	else if (deltah(p) == -2) {
		if (deltah(p->left)>0)
			p->left = rotateL(p->left);
		return rotateR(p);
	}	
	return p;
}
dT node<T>* TreeSet<T>::Fmin(node<T>* p) {
	if (!p->left) {
		minKey = p->key;
		return p->right;
	}
	p->left = Fmin(p->left);
	return balance(p);
}
dT node<T>* TreeSet<T>::remove(node<T>* p, T k) {
	if (!p) {
		return 0; size++;
	}
	if (p->key < k)p->right = remove(p->right, k);
	else if (p->key>k)p->left = remove(p->left, k);
	else {
		if(p->prev)p->prev->next = p->next;
		if(p->next)p->next->prev = p->prev;
		if (!p->right)return p->left;
		else {
			p->right = Fmin(p->right);
			p->key = minKey;
		}
	}
	return balance(p);
}
dT void TreeSet<T>::remove(T k) {
	root = remove(root, k); size--;
}
dT node<T>* TreeSet<T>::insert(node<T>* p, T k, node<T>* pr, bool isLeft) {
	if (!p) {
		node<T>* r = new node<T>(k);
		if (isLeft) {
			r->prev = pr->prev;
			if (r->prev)r->prev->next = r;
			r->next = pr;
			pr->prev = r;
		}
		else {
			r->prev = pr;
			r->next = pr->next;
			if (r->next)r->next->prev = r;
			pr->next = r;
		}
		return  r;
	}
	if (p->key <= k) p->right = insert(p->right, k, p, 0);
	else p->left = insert(p->left, k, p, 1);
	return balance(p);
}
dT void TreeSet<T>::insert(T k) {
	if (exist(k))return; size++;
	if (!root)root= new node<T>(k);
	else root= insert(root, k, 0, 0);
}
dT iter<T> TreeSet<T>::getIter() {
	{
		node<T>* r = root;
		while (r->left)r = r->left;
		return iter<T> (r);
	}
}
dT bool TreeSet<T>::exist(T k) {
	node<T>* n = root;
	while (n) {
		if (n->key == k)return true;
		if (n->key < k)n = n->right;
		else n = n->left;
	}
	return false;
}
dT void TreeSet<T>::print() {
	struct u {
		static void traverse(node<T>* t) {
			if (t->left) traverse(t->left);
			cout << t->key << " ";
			if (t->right)traverse(t->right);
		}
	};
	u.traverse(root);
}
dT void TreeSet<T>::makePic(String^ imgName) {
	Process p;
	String^ path = AppDomain::CurrentDomain->BaseDirectory; 
	String^ dotName = "tree.dot";
	makeDot();
	p.StartInfo->WorkingDirectory = path;
	p.StartInfo->FileName = path + "GraphViz\\release\\bin\\dot.exe";
	p.StartInfo->Arguments = "-Tpng " + dotName + " -o " + imgName;
	p.StartInfo->UseShellExecute = false;
	p.StartInfo->CreateNoWindow = true;

	p.Start();
	while (!p.HasExited);
	p.Close();
}
dT void TreeSet<T>::clear() {
	root = 0;
}
dT T TreeSet<T>::min() {
	node<T>* n = root;
	while (n->left) n = n->left;
	return n->key;
}
dT T TreeSet<T>::max() {
	node<T>* n = root;
	while (n->right) n = n->right;
	return n->key;
}
dT int TreeSet<T>::getSize() {
	return size;
}
dT void TreeSet<T>::makeDot() {
	//String^ dotName = ;
	//const int con = 0;
	struct uu {
		int con = 0;
		void traverse(node<T>* t, ofstream& ff,int c) {
			
			if (t->left) {	
				con++;
				ff << c << "[label=" << t -> key << "];";
				ff << c+1 << "[label=" << t->left->key << "];" << endl;
				ff << c << "->" << c+1 << ";\n";
				traverse(t->left, ff,c+1);
			}
			if (t->right) {
				con++;
				ff << c << "[label=" << t->key << "];";
				ff << con<< "[label=" << t->right->key << "];" << endl;
				ff <<c << "->" <<con << ";\n";
				traverse(t->right, ff,con);
			}
		}
		void MarshalString(String ^ s, string& os) {
			using namespace Runtime::InteropServices;
			const char* chars =
				(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
			os = chars;
			Marshal::FreeHGlobal(IntPtr((void*)chars));
		}
	};
	uu u;
	String^ path = AppDomain::CurrentDomain->BaseDirectory;
	string p; u.MarshalString(path, p);
	ofstream f( p+"tree.dot");
	f << "digraph g{" << endl;
	
	
	u.traverse(root, f,0);
	f << "}" << endl;
	f.close();
}
dT iter<T> TreeSet<T>::begin()
{
	return getIter();
}
dT iter<T> TreeSet<T>::end() {
	node<T>* r = root;
	while (r->right)r = r->right;
	return iter<T>(r);
}

dT TreeSet<T>& TreeSet<T>::operator=(TreeSet<T>& t)
{
	root = t.root; size = t.size;
	return this;
}
dT  TreeSet<T>& TreeSet<T>::operator=(T& t) {
	root = new node<T>(t);
	return this;
}
dT TreeSet<T> TreeSet<T>::operator+(TreeSet<T> t) {
	TreeSet<T> tree;
	iter<T> it=t.getIter();
	while (*it) {
		tree.insert(it->key);
		it++;
	}
	it = getIter();
	while (*it) {
		tree.insert(it->key);
		it++;
	}
	return tree;
}
dT  TreeSet<T> TreeSet<T>::operator+(T& t) {
	TreeSet<T> tree();
	iter<T> it = t.getIter();
	while (it) {
		tree.insert(it->key);
		it++;
	}
	tree.insert(t->key);
	return tree;
}
dT TreeSet<T> TreeSet<T>::operator-(TreeSet<T>& t) {
	TreeSet<T> tree;
	iter<T> it = getIter();
	while (*it) {
		tree.insert(it->key);
		it++;
	}
	it = t.getIter();
	while (*it) {
		tree.remove(it->key);
		//tree.makePic("" + (bb++)+".png");
		it++;
	}
	return tree;
}
dT TreeSet<T> TreeSet<T>::operator-( T& t) {
	TreeSet<T> tree();
	iter<T> it = t.getIter();
	while (*it) {
		tree.insert(it->key);
		it++;
	}
	tree.remove(t->key);
	return tree;
}
dT void TreeSet<T>::operator+=(TreeSet<T>& t) {
	iter<T> it = t.getIter();
	while (*it) {
		insert(it->key);
		it++;
	}
}
dT void TreeSet<T>::operator+=(T& t) {
	insert(t);
}
dT void TreeSet<T>::operator-=(TreeSet<T>& t) {
	iter<T> it = t.getIter();
	while (it) {
		remove(it->key);
		it++;
	}
}
dT void TreeSet<T>::operator-=(T& t) {
	remove(t);
}

         //ITERATOR
dT const node<T>* iter<T>::operator*() const
{
	return p;
}
dT node<T>* iter<T>::operator*()
{
	return p;
}
dT node<T>* iter<T>::operator->() const
{
	//try {
	//	if (p == 0)throw NullIter();
		return p;
	/*}
	catch (NullIter& e) {
		cout << e.what() << endl;
		return 0;
	}*/
}
// prefix increment (++it)
dT iter<T>& iter<T>::operator++() {
	try {
		if (p == 0)throw 1;
		p = p->next;
		return *this;
	}
	catch (int k) {
		cout << "out of tree!!!" << endl;
		return iter<T>(0);
	};
}
// postfix increment (it++)
dT iter<T> iter<T>::operator++(int)
{
	try {
		if (p == 0) throw OutOfTree();
		iter<T> h = iter<T>(p);
		p = p->next;
		return h;
	}
	catch (OutOfTree& e) {
		cout << e.what() << endl;
		return iter<T>(0);
	}
}
// prefix decrement (--it)
dT iter<T>& iter<T>::operator--() {
	try {
		if (p == 0)throw 1;
		p = p->prev;
		return *this;
	}
	catch (int k) {
		cout << "out of tree!!!" << endl;
		return iter<T>(0);
	}
}
// postfix decrement (it--)
dT iter<T> iter<T>::operator--(int)
{
	try {
		if (p == 0)throw OutOfTree();
		iter<T> h = iter<T>(p);
		p = p->prev;
		return h;
	}
	catch (OutOfTree& e) {
		cout << e.what() << endl;
		return iter<T>(0);
	}
}
dT const node<T>* iter<T>::operator[](const std::size_t& n) const
{
	try {
		node<T>* tt = p;
		for (int i = 0; i < n; i++) {
			if (tt == 0)throw 1;
			tt = tt->next;
		}
		return tt;
	}
	catch (int i) {
		cout << "out of tree!!!" << endl;
		return 0;
	}
}
dT node<T>* iter<T>::operator[](const std::size_t& n)
{
	try {
		node<T>* tt = p;
		for (int i = 0; i < n; i++) {
			if (tt == 0)throw OutOfTree();
			tt = tt->next;
		}
		return tt;
	}
	catch (OutOfTree& e) {
		cout << e.what() << endl;
		return 0;
	}
}
dT iter<T>& iter<T>::operator+=(const std::size_t& n)
{
	try {
		for (int i = 0; i < n; i++) {
			if (p == 0)throw 1;
			p = p->next;
		}
		return *this;
	}
	catch (int k) {
		cout << "out of tree!" << endl;
		return iter<T>(0);
	}
}
dT iter<T> iter<T>::operator+(const std::size_t& n) const
{
	try {
		node<T>* tt = p;
		for (int i = 0; i < n; i++) {
			if (tt == 0)throw OutOfTree();
			tt = tt->next;
		}
		return   iter<T>(tt);
	}
	catch (OutOfTree& e) {
		cout << e.what() << endl;
		return iter<T>(0);
	}
}
dT iter<T>& iter<T>::operator-=(const std::size_t& n)
{
	try {
		for (int i = 0; i < n; i++) {
			if (p == 0)throw 1;
			p = p->prev;
		}
		return *this;
	}
	catch (int k) {
		cout << "out of tree!" << endl;
		return iter<T>(0);
	}
}
dT iter<T> iter<T>::operator-(const std::size_t& n) const
{
	try {
		node<T>* tt = p;
		for (int i = 0; i < n; i++) {
			if (tt == 0)throw OutOfTree();
			tt = tt->prev;
		}			
		return   iter<T>(tt);
	}
	catch (OutOfTree& e) {
		cout << e.what() << endl;
		return iter<T>(0);
	}
}
dT node<T>* iter<T>::base() const { return p; }
dT inline bool operator==(const iter<T>& __lhs, const iter<T>& __rhs)
{
	return __lhs.base() == __rhs.base();
}
dT inline bool operator!=(const iter<T>& __lhs, const iter<T>& __rhs)
{
	return __lhs.base() != __rhs.base();
}
dT inline bool operator<(const iter<T>& lhs,const iter<T>& rhs)
{
	try {
		node<T>* l = lhs.base(); 	node<T>* r = rhs.base();
		if (l == 0) throw 1;
		if (r == 0) throw 2;
		if (l == r)return false;
		while (l != 0 && l != r) l = l->next;
		return l == r;
	}
	catch (int i) {
		if (i == 1)cout << "left operand is NULL (or both)" << endl;
		if(i==2)cout << "right operand is NULL" << endl;
		return false;
	}
}
dT inline bool operator>(const iter<T>& lhs, const iter<T>& rhs)
{
	try {
		node<T>* l = lhs.base(); node<T>* r = rhs.base();
		if (l == 0) throw leftOut();
		if (r == 0) throw rightOut();
		if (l == r)return false;
		while (r != 0 && l != r) r = r->next;
		return l == r;
	}
	catch (leftOut& e) {
		cout << e.what() << endl;
		return false;
	}
	catch (rightOut& e) {
		cout << e.what() << endl;
		return false;
	}
}
dT inline bool operator<=(const iter<T>& lhs, const iter<T>& rhs)
{
	try {
		node<T>* l = lhs.base(); 	node<T>* r = rhs.base();
		if (l == 0) throw leftOut();
		if (r == 0) throw rightOut();
		while (l != 0 && l != r) l = l->next;
		return l == r;
	}
	catch (leftOut& e) {
		cout << e.what() << endl;
		return false;
	}
	catch (rightOut& e) {
		cout << e.what() << endl;
		return false;
	}
}
dT inline bool operator>=(const iter<T>& lhs, const iter<T>& rhs)
{
	try {
		node<T>* l = lhs.base(); node<T>* r = rhs.base();
		if (l == 0) throw leftOut();
		if (r == 0) throw rightOut();		
		while (r != 0 && l != r) r = r->next;
		return l == r;
	}
	catch (leftOut& e) {
		cout << e.what() << endl;
		return false;
	}
	catch (rightOut& e) {
		cout << e.what() << endl;
		return false;
	}
}
dT inline iter<T> operator+(std::size_t n, const iter<T>& __i)
{
	try {
		node<T>* tt = __i.base();
		if (tt == 0)throw NullIter();
		for (int i = 0; i < n; i++)
			tt = tt->next;
		return   iter<T>(tt);
	}
	catch (NullIter& e) {
		cout << e.what()<< endl;
		return iter<T>(0);
	}
}