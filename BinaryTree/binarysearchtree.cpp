#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
};

bool emptyTree(node* root)
{
	return root->data <= -1;
}

void insert(node *root, int data)
{
	node *newNode, *current, *parent;

	if(!emptyTree(root))
	{
		parent = NULL;
		current = root;

		newNode = new node;
		newNode->data = data;
		newNode->left = NULL;
		newNode->right = NULL;

		while(current != NULL)
		{
			parent = current;
			if(data < current->data) current = current->left;
			else current = current->right;
		}
		if(data < parent->data) parent->left = newNode;
		else parent->right = newNode;
	}
	else root->data = data;
}

void inOrder(node* root)
{
	if(root->left != NULL)
	{
		cout << "root left: inOrder(" << root->left->data << ")" << endl;
		inOrder(root->left);
	}
	cout << root->data << endl;
	if(root->right != NULL)
	{
		cout << "root right: inOrder(" << root->right->data << ")" << endl;
		inOrder(root->right);
	}
}

void levelOrder(node* root)
{
	queue<node*> q;
	if(root != NULL)
	{
		q.push(root);

		while(!q.empty())
		{
			node* current = q.front();

			if(current->left != NULL) q.push(current->left);
			if(current->right != NULL) q.push(current->right);

			cout << current->data << endl;
			q.pop();
		}
	}
}

int numNodes(node* root)
{
	if(root == NULL) return 0;
	else return 1 + numNodes(root->left) + numNodes(root->right);
}

int numLeaves(node* root)
{
	if(root == NULL) return 0;
	else if (root->left == NULL && root->right == NULL) return 1 + numLeaves(root->left) + numLeaves(root->right);
	else return numLeaves(root->left) + numLeaves(root->right);
}

int sumLeaves(node* root)
{
	if(root == NULL) return 0;
	else if(root->left == NULL && root->right == NULL) return root->data + sumLeaves(root->left) + sumLeaves(root->right);
	else return sumLeaves(root->left) + sumLeaves(root->right); 
}

node* max(node* root)
{
	if(root == NULL) return NULL;
	else if(root->right != NULL) return max(root->right);
	else return root;
}

node* min(node* root)
{
	if(root == NULL) return NULL;
	else if(root->left != NULL) return min(root->left);
	else return root;
}

// node* findNode(node* root, int value)
// {
// 	if(root != NULL)
// 	{
// 		if(root->data == value) return root;
// 		else if(value < root->data) return findNode(root->left, value);
// 		else return findNode(root->right, value);
// 	}
// 	else return NULL;
// }

int numLevels(node* root)
{
	if(root == NULL) return -1;

	int leftHeight = numLevels(root->left);
	int rightHeight = numLevels(root->right);

	return 1 + max(leftHeight, rightHeight);
}

int levelOfNode(node* root, int value, int level)
{
	if(root == NULL) return INT_MIN;
	else if(root->data == value) return level;
	else return levelOfNode(root->left, value, level+1) + levelOfNode(root->right, value, level+1);
}

void deleteNode(node* root, int value)
{
	node *current, *parent, *child;

	parent = NULL;
	current = root;
	while(current != NULL && value != current->data)
	{
		parent = current;

		if(value < current->data) current = current->left;
		else current = current->right;
	}

	if(current != NULL)
	{
		cout << "Deleting: " << current->data << endl;
		if(current->left == NULL && current->right == NULL)
		{
			cout << "Deleting Leaf Node" << endl;
			if(parent == NULL) current->data = -1;
			else
			{
				if(value < parent->data) parent->left = NULL;
				else parent->right = NULL;
			}
			delete current;
		}
		else if(current->left != NULL && current->right == NULL)
		{
			cout << "Left Subtree Only" << endl;
			child = current->left;
			if(parent == NULL)
			{
				current->data = child->data;
				current->left = child->left;
				current->right = child->right;
			}
			else parent->left = child;

			delete current;
			delete child;
		}
		else if(current->left == NULL && current->right != NULL)
		{
			cout << "Right Subree Only" << endl;
			child = current->right;
			if(parent == NULL)
			{
				current->data = child->data;
				current->left = child->left;
				current->right = child->right;
			}
			else parent->right = child;

			delete current;
			delete child;
		}
		else if(current->left != NULL && current->right != NULL)
		{
			cout << "Right and Left subtree" << endl;
			if(parent == NULL)
			{
				cout << "Parent NULL" << endl;
				child = current->right;
				current->data = child->data;
				if(child->left == NULL && child->right != NULL) // GOOD
				{
					cout << "Child Left NULL and Child Right NOT null" << endl;
					current->right = child->right;
				}
				else if(child->left != NULL && child->right == NULL) // GOOD
				{
					cout << "Child left not null and child right null" << endl;
					current->right = NULL;
					node* temp = child;
					while(child->left != NULL) child = child->left;
					child->left = current->left;
					current->left = temp->left;
					
					delete temp;
					delete child;
				}
				else if(child->left == NULL && child->right == NULL)
				{
					cout << "Child Left and Child Right are NULL.  Copy value and delete child" << endl;
				}
				else
				{
					cout << "Both child->left and child->right not null" << endl;
				}
			}
			else
			{
				cout << "Parent NOT NULL" << endl;
			}
			//delete current;
		}
	}
	else cout << "Item not found for deletion" << endl;
}

node* findNode(node* root, int key)
{
	if(root == NULL) return NULL;
	else if(key == root->data) return root;
	else if(key < root->data) return findNode(root->left, key);
	else return findNode(root->right, key);
}

node* newSearch(node* root, int val) // NO...
{
	if(root == NULL) return NULL;
	else if(root->data == val) return root;
	else
	{
		node* result = newSearch(root->left, val);
		if(result == NULL) 
		{
			result = newSearch(root->right, val);
			return result;
		}
	}
}

int main()
{
	node* root = new node;
	root->data = -1;
	root->left = NULL;
	root->right = NULL;

	insert(root, 50);
	insert(root, 40);
	insert(root, 60);
	insert(root, 30);
	insert(root, 70);
	insert(root, 25);
	insert(root, 35);
	insert(root, 65);
	insert(root, 75);
	insert(root, 80);
	cout << "In Order" << endl;
	inOrder(root);
	cout << endl << "Level Order" << endl;
	levelOrder(root);
	cout << endl << "Num Leaves" << endl;
	cout << numLeaves(root) << endl;
	cout << endl << "Sum Leaves" << endl;
	cout << sumLeaves(root) << endl;
	cout << endl << "Max" << endl;
	node* maxResult = max(root);
	cout << maxResult->data << endl;
	cout << endl << "Min" << endl;
	node* minResult = min(root);
	cout << minResult->data << endl;
	int value = 60;
	cout << endl << "Find Recursively: " << value << endl;

	node* findNodeValue = findNode(root, value);
	if(findNodeValue != NULL) cout << findNodeValue->data << " FOUND!" << endl;
	else cout << value << " NOT found!" << endl;

	node* findNodeValue = findNodeIteratively(root, value);
	if(findNodeValue != NULL) cout << findNodeValue->data << " FOUND!" << endl;
	else cout << value << " NOT found!" << endl;

	cout << endl << "Num Levels" << endl;
	cout << numLevels(root) << endl;

	cout << endl << "Num Nodes" << endl;
	cout << numNodes(root) << endl;

	int nodeLevelValue = 55;
	cout << endl << "Level of node: " << nodeLevelValue << endl;
	int res = levelOfNode(root, nodeLevelValue, 0);
	if(res != INT_MIN) cout << res << endl;
	else cout << "Value doesn't exist in the tree" << endl;
	//cout << levelOfNode(root, nodeLevelValue, 0) << endl;

	cout << endl << "Bitwise Question..." << endl;
	char three = 'z';
	int count = 0;
	int i = 0;
	while(three)
	{
		count += three & 2;
		three = three >> 1;
		cout << "Count: " << count << endl;
	}
	cout << "Count = " << count << endl;

	cout << endl << "New Search" << endl;
	node* newSearchResult = newSearch(root, 25);
	if(newSearchResult != NULL) cout << newSearchResult->data << " FOUND!" << endl;
	else cout << "NOT FOUND!" << endl;
	return 0;
}