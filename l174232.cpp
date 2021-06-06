#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<fstream>
#include<string>
using namespace std;


class ProductData
{
public:
	friend ostream& operator<<(ProductData p, ostream &out);
	ProductData(string _Name = "", int _Quantity = 0)
	{
		Name = _Name;
		Quantity = _Quantity;
	}
	ProductData(const ProductData& obj)
	{
		Name = obj.Name;
		Quantity = obj.Quantity;
	}
	const  ProductData& operator=(const ProductData &rhs)
	{
		if (this != &rhs)
		{
			Name = rhs.Name;
			Quantity = rhs.Quantity;
		}
		return *this;
	}
	void Print()
	{
		cout << Name << '\t' << Quantity << '\t' << endl;
	}
private:
	string Name; //Value
	int Quantity; //Value
};

ostream& operator<<(ostream &out, ProductData p)
{
	p.Print();
	return out;
}

void PlaceCursor(int x, int y)
{
	COORD c;
	c.X = x; c.Y = y;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

template<class K, class T>
class AVLNode
{
public:
	K key;
	T data;
	int height;
	AVLNode<K, T> *left;
	AVLNode<K, T> *right;
	AVLNode<K, T>(K _key = 0, T _data = 0, int _height = 0, AVLNode<K, T> *_left = 0, AVLNode<K, T>*_right = 0)
	{
		key = _key;
		data = _data;
		height = _height;
		left = _left;
		right = _right;
	}
};

template<class K, class T>
class AVLMAP
{
public:
	AVLMAP<K, T>(AVLNode<K, T>* _root = 0)
	{
		root = _root;
	}
	bool Insert(K _key, T value)									//wrapper function
	{
		return	Insert(root, _key, value);
	}
	bool Insert(AVLNode<K, T> *&ptr, K _key, T &value)
	{
		if (ptr == nullptr)											 //if nullptr then insert new element
		{
			ptr = new AVLNode<K, T>(_key, value, 0, 0, 0);
		}
		else if (_key == ptr->key)
			return false;
		else if (_key > ptr->key)
		{
			Insert(ptr->right, _key, value);
			ptr->right->height = Height(ptr->right);
			ptr->height = Height(ptr);
		}
		else if (_key < ptr->key)
		{

			Insert(ptr->left, _key, value);
			ptr->left->height = Height(ptr->left);
			ptr->height = Height(ptr);
		}
		Balance(ptr);
		ptr->height = Height(ptr);
		return true;
	}
	bool LookUP(K value)							  //wrapper function
	{
		return LookUP(root, value);
	}
	bool LookUP(AVLNode <K, T> *&ptr, K value)
	{
		if (ptr == nullptr)
			return false;
		else if (value == ptr->key)
			return true;
		else if (value < ptr->key)
			return LookUP(ptr->left, value);
		else if (value > ptr->key)
			return LookUP(ptr->right, value);
	}
	void rightRotate(AVLNode<K, T> * &ptr)
	{
		AVLNode<K, T> * Orphan = ptr->left->right;
		AVLNode<K, T> * Y = ptr->left;
		Y->right = ptr;
		ptr->left = Orphan;
		ptr = Y;
		ptr->height = Height(ptr);
		Y->height = Height(Y);
	}
	void leftRotate(AVLNode<K, T> *& X)
	{
		AVLNode<K, T> *orphan = X->right->left;
		AVLNode<K, T> *Y = X->right;
		Y->left = X;
		X->right = orphan;
		X = Y;
		X->height = Height(X);
		Y->height = Height(Y);
	}
	void doubleLeftRightRotation(AVLNode <K, T> *&X)
	{
		leftRotate(X->left);
		rightRotate(X);
	}
	void doubleRightLeftRotation(AVLNode< K, T>*&X)
	{
		rightRotate(X->right);
		leftRotate(X);
	}
	void Balance(AVLNode<K, T>*& ptr)
	{
		if (ptr == nullptr)
			return;

		int bf = BF(ptr);
		if (bf != 0 && bf != -1 && bf != 1)
		{
			if (bf < -1)
			{
				if (Height(ptr->left->left) >= Height(ptr->left->right))
					rightRotate(ptr);
				else
					doubleLeftRightRotation(ptr);						//zigzag rotation
			}
			else if (bf > 1)
			{
				if (Height(ptr->right->right) >= Height(ptr->right->left))
					leftRotate(ptr);
				else
					doubleRightLeftRotation(ptr);						//zigzag rotation
			}
		}
		ptr->height = Height(ptr);
	}
	int BF(AVLNode<K, T>* &ptr)										   //Balance Factor
	{
		return Height(ptr->right) - Height(ptr->left);
	}
	int Height(AVLNode<K, T> *&ptr)
	{
		if (ptr == nullptr)							//if not exist then height=-1
			return -1;
		else
		{
			if (ptr->left == 0 && ptr->right == 0)	//if no child then height=0
				return 0;
			int	LH = Height(ptr->left);
			int	RH = Height(ptr->right);
			if (LH > RH)						  //Greater height of children
				return 1 + Height(ptr->left);
			else
				return 1 + Height(ptr->right);
		}
	}
	int Height()
	{
		return Height(root);
	}
	AVLNode<K, T>*& FindMax(AVLNode<K, T>*ptr)	//find maximum->key from children
	{
		while (ptr->right != nullptr)
			ptr = ptr->right;
		return *&ptr;
	}
	bool DeleteNode(AVLNode<K, T>*& ptr)
	{
		AVLNode<K, T>*temp = ptr;
		if (ptr->left == nullptr)		//parent have right child only
		{
			ptr = ptr->right;
			delete temp;
			return true;
		}
		else if (ptr->right == nullptr)  //parent have left child only
		{
			ptr = ptr->left;
			delete temp;
			return true;
		}
		else							//parent have both children
		{
			AVLNode<K, T> *newDataPtr = FindMax(ptr->left);
			ptr->data = newDataPtr->data;
			ptr->key = newDataPtr->key;
			Delete(ptr->left, ptr->key);
		}
	}
	bool Delete(K value) //wrapper function for delete
	{
		return	Delete(root, value);
	}
	bool Delete(AVLNode<K, T>*& ptr, K value)
	{
		if (ptr == nullptr)
			return false;
		if (ptr != nullptr)
		{
			if (ptr->key > value)
				Delete(ptr->left, value); //delete left child
			else if (ptr->key < value)
				Delete(ptr->right, value);	//delete right child
			else
				DeleteNode(ptr);			//delete itself
			Balance(ptr);
			return true;
		}
	}
	void Destroy(AVLNode<K, T>* &ptr)			 
	{
		if (ptr != nullptr)
		{
			Destroy(ptr->left);
			Destroy(ptr->right);
			delete ptr;
		}
	}
	~AVLMAP()
	{
		Destroy(root);
	}
	void PrintAVLTree()		   //wrapper function for print
	{
		int x = 50, y = 2;
		PrintAVLTree(root, x, y);												   \
	}
	void Visit(AVLNode<K, T>* ptr)
	{
		if (ptr)
			cout << ptr->key << " ";			//print key
	}
	void PrintAVLTree(AVLNode<K, T> *ptr, int x, int y)
	{

		if (ptr != nullptr)
		{
			if (ptr == root->right)
				x = x + 20;

			PrintAVLTree(ptr->left, x - 2 - (Height(ptr->left)) * 6, y + 2);		  //left
			PlaceCursor(x, y);

			if (ptr == root)				   //handeling root
			{
				int rootx = x - 2 + (Height(root->right) * 4 + Height(root->left) * 4) / 2;
				PlaceCursor(rootx, y);
				Visit(ptr);
				if (ptr->right != 0)
				{
					PlaceCursor(rootx + 1, y + 1);
					if (root == ptr)
						PlaceCursor(rootx + 1, y + 1);
					cout << "\\";
				}
				if (ptr->left != 0)
				{
					PlaceCursor(rootx - 1, y + 1);
					cout << "/";
				}
			}
			if (ptr != root){
				Visit(ptr);
				if (ptr->right != 0)
				{

					PlaceCursor(x + 1, y + 1);
					if (root == ptr)
						PlaceCursor(x + 1, y + 1);
					cout << "\\";
				}
				if (ptr->left != 0)
				{

					PlaceCursor(x - 1, y + 1);
					cout << "/";
				}
			}

			PrintAVLTree(ptr->right, x + 2 + (Height(ptr->right)) * 6, y + 2);  //right
		}
	}
	void PrintInOrder()			   //wrapper function for print 
	{
		PrintInOrder(root);
	}
	void PrintInOrder(AVLNode<K,T> *ptr)		//Inorder print 
	{
		if (ptr != nullptr)
		{
			PrintInOrder(ptr->left);
			Visit(ptr);
			PrintInOrder(ptr->right);
		}
	}
private:
	AVLNode< K, T >* root;

};

void LoadAVL(AVLMAP <int, ProductData> &A)
{
	ifstream fin;
	fin.open("file.txt");
	if (fin.is_open())
	{
		char buffer[100];
		int a, b;
		fin.getline(buffer, 100, '\n');
		while (!fin.eof())
		{
			fin >> a;											   //read key
			fin.getline(buffer, 100, '\t');
			fin.getline(buffer, 100, '\t');						   //read name
			fin >> b;											   //read quantity
			ProductData P(buffer, b);
			A.Insert(a, P);
		}
	}
	else
		cout << "Error: File not found." << endl;
}
int main()
{
		AVLMAP<int, ProductData > ProductMap;
		LoadAVL(ProductMap);
		ProductData P("CD", 3);


		cout << "Printing AVL Tree of ProductMap." << endl;
		ProductMap.PrintAVLTree();

		cout << endl<< endl << "Printing Inorder ProductMap" << endl;
		ProductMap.PrintInOrder();
		bool s;
		s=ProductMap.Insert(911, P);
		if (s == 1)
			cout <<  endl <<"911 inserted." << endl;
		else
			cout << endl<<"911 not inserted." << endl;
		cout << endl << "Printing AVL Tree of ProductMap after inserting 911." << endl;
		ProductMap.PrintInOrder();

		s = ProductMap.LookUP(911);
		if (s == 1)
			cout <<endl<< "911 found." << endl;
		else
			cout <<endl<< "911 not found." << endl;

		s = ProductMap.LookUP(4);
		if (s == 1)
			cout <<endl<< "4 found." << endl;
		else
			cout <<endl<< "4 not found." << endl;
		
		s=ProductMap.Delete(911);

		if (s == 1)
			cout <<endl<< "911 deleted." << endl;
		else
			cout <<endl<< "911 not deleted." << endl;
		cout << endl << "Printing p after deleting 911" << endl;
		ProductMap.PrintInOrder();
		
	_getch();
}