#include <iostream>

using namespace std;



template <typename T>
class Tree {
private:

	struct node
	{
		T key;
		unsigned char height;
		node* left;
		node* right;
		node(T k) { key = k; left = right = 0; height = 1; }
	};

	node* root;

	unsigned char differenceHeight(node* tempNode) {
		return calculateHeight(tempNode->right) - calculateHeight(tempNode->left);
	}

	node* turnRight(node* tempNode) 
	{
		node* tempNodeQ = tempNode->left;
		tempNode->left = tempNode->right;
		tempNodeQ->right = tempNode;
		countingHeight(tempNode);
		countingHeight(tempNodeQ);
		return tempNodeQ;
	}

	node* turnLeft(node* tempNode) 
	{
		node* tempNodeQ = tempNode->right;
		tempNode->right = tempNodeQ->left;
		tempNodeQ->left = tempNode;
		countingHeight(tempNode);
		countingHeight(tempNodeQ);
		return tempNodeQ;
	}

	unsigned char calculateHeight(node* tempNode) {
		if (tempNode) {
			return tempNode->height;
		}
		return 0;
	}

	void countingHeight(node* tempNode) {
		T rightHeight = calculateHeight(tempNode->right), leftHeight = calculateHeight(tempNode->left);

		if (rightHeight > leftHeight) {
			tempNode->height = rightHeight+1;
		}
		else{
			tempNode->height = leftHeight+1;
		}
	}

	node* balance(node* tempNode) 
	{
		
		countingHeight(tempNode);
		
		if (differenceHeight(tempNode) == 2)
		{
			if (differenceHeight(tempNode->right) < 0)
				tempNode->right = turnRight(tempNode->right);
			return turnLeft(tempNode);
		}
		if (differenceHeight(tempNode) == -2)
		{
			if (differenceHeight(tempNode->left) > 0)
				tempNode->left = turnLeft(tempNode->left);
			return turnRight(tempNode);
		}
		return tempNode; 
	}

	node* pushNode(T key, node* tempNode) {
		if (!tempNode) {
			node* temp = new node(key);
			return temp;
		}
		if (key < tempNode->key)
			tempNode->left = pushNode(key, tempNode->left);
		else
			tempNode->right = pushNode(key, tempNode->right);
		return balance(tempNode);

	}

	void showVAL(node* tempNode) {
		cout << tempNode->key << " ";
		if (tempNode->left) {
			showVAL(tempNode->left);
		}
		if (tempNode->right) {
			showVAL(tempNode->right);
		}


	}

	node* findMin(node* tempNode)
	{
		if (tempNode->left) {
			return findMin(tempNode->left);
		}
		return tempNode;
	}

	node* delMin(node* tempNode) 
	{
		if (tempNode->left == 0)
			return tempNode->right;
		tempNode->left = delMin(tempNode->left);
		return balance(tempNode);
	}

	node* del(node* tempNode, T key) 
	{
		if (!tempNode) return 0;
		if (key < tempNode->key)
			tempNode->left = del(tempNode->left, key);
		else if (key > tempNode->key)
			tempNode->right = del(tempNode->right, key);
		else 
		{
			node* tempNodeQ = tempNode->left;
			node* tempNodeR = tempNode->right;
			delete tempNode;
			if (!tempNodeR) return tempNodeQ;
			node* min = findMin(tempNodeR);
			min->right = delMin(tempNodeR);
			min->left = tempNodeQ;
			return balance(min);
		}
		return balance(tempNode);
	}

	bool chekElem(node* tempNode, T key) {
		if (tempNode->key == key) {
			return true;
		}
		if (tempNode->left) {
			chekElem(tempNode->left, key);
		}
		if (tempNode->right) {
			chekElem(tempNode->right, key);
		}
		
	}

	void printTree(node* tempNode, int level)
	{
		if (tempNode)
		{
			printTree(tempNode->right, level + 1);

			for (int i = 0; i < level; i++){ 
				cout << "   ";
			}
			cout << tempNode->key << endl;

			printTree(tempNode->left, level + 1);
		}
	}
	

public:

	Tree() {
		root = 0;
	}
	~Tree() {}

	void push(T key) {
		root = pushNode(key, root);	
	}

	void show() {
		showVAL(root);
	}

	void pop(T key) {
		if (key = root->key) {
			root = del(root, key);
		}
		else {
			del(root, key);
		}
	}

	bool empty(T key) {
		if (chekElem(root, key) == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	
	void showAVL() {
		printTree(root, 0);
	}

	



	
};





















int main()
{
	Tree<int> tree;
	tree.push(15);
	tree.push(16);
	tree.push(17);
	tree.push(14);
	tree.push(18);
	tree.push(19);
	tree.push(20);
	tree.push(21);
	tree.push(22);
	tree.push(23);
	tree.push(24);
	/*tree.push(25);
	tree.push(26);
	tree.push(27);
	tree.push(28);
	tree.push(29);
	tree.push(30);*/
	tree.show();
	cout << endl;
	//tree.pop(16);
	tree.show();
	cout << endl;
	cout << tree.empty(16);
	cout << endl;
	cout << tree.empty(21);
	cout << endl;
	tree.showAVL();


		




	return 0;
}
