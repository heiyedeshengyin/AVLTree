/*	Copyright 2019 heiyedeshengyin All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef AVLTREE
#define AVLTREE
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;

//===========AVL树的结点===========
template <typename T>
struct TreeNode
{
	T key;	//结点中存储的数据
	int height;	//结点的高度
	TreeNode<T> *left;	//结点的左孩子
	TreeNode<T> *right;	//结点的右孩子
	//结点的构造函数
	TreeNode(T x, int _height)
	{
		key = x;
		height = _height;
		left = nullptr;
		right = nullptr;
	}
};

//===========AVL树===========
template <typename T>
class AVLTree
{
private:
	TreeNode<T> *root;	//根结点
	int _size;	//结点个数
public:
	AVLTree();	//无参构造函数
	AVLTree(T x);	//创建一个根结点
	AVLTree(TreeNode<T>* _root);	//用一个已有的根结点赋值给根结点
	AVLTree(AVLTree<T> &_root);	//拷贝构造函数
	AVLTree(vector<T> v);	//用一个数组来创建AVL树
	~AVLTree();	//析构函数
	vector<T> PerOrderTraverse();	//先序遍历
	vector<T> InOrderTraverse();	//中序遍历
	vector<T> PostOrderTraverse();	//后序遍历
	vector<T> LevelOrderTraverse();	//层序遍历
	void clear();	//清空二叉树
	bool isEmpty();	//判断二叉树是否为空
	bool isBalanced();	//判断是否为平衡二叉树,在AVL树中始终返回true
	int height();	//获取树的高度
	int size();	//获取结点个数
	T maximum();	//获取最大值
	T minimum();	//获取最小值
	TreeNode<T>* search(T e);	//搜索结点
	bool insert(T e);	//插入节点
	bool remove(T e);	//删除结点
	T operator[] (int r);	//重载[]操作符
};

//===========函数的具体实现===========
/*
	无参构造函数
*/
template <typename T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
	_size = 0;
}

//------------------------------------------------------
/*
	有参构造函数
	T x:二叉树根结点的值
*/
template <typename T>
AVLTree<T>::AVLTree(T x)
{
	root = new TreeNode<T>(x, 1);
	_size = 1;
}

//------------------------------------------------------
/*
	复制一个二叉树到新的内存中
	TreeNode<T>* &_root:被复制的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* copyBiTree(TreeNode<T>* &root)
{
	if (root)
	{
		TreeNode<T>* another;
		another = new TreeNode<T>(root->key, getHeight(root));
		if (root->left)
			another->left = copyBiTree(root->left);
		if (root->right)
			another->right = copyBiTree(root->right);

		return another;
	}
	else
		return nullptr;
}

//------------------------------------------------------
/*
	用一个已有的根结点赋值给根结点
	TreeNode<T>* _root:已有的根结点
*/
template <typename T>
AVLTree<T>::AVLTree(TreeNode<T>* _root)
{
	root = copyBiTree(_root);
	_size = getSize(_root);
}

//------------------------------------------------------
/*
	拷贝构造函数
	BinarySearchTree<T> &_root:被拷贝的AVL树
*/
template <typename T>
AVLTree<T>::AVLTree(AVLTree<T> &_root)
{
	root = copyBiTree(_root.root);
	_size = _root._size;
}

//------------------------------------------------------
/*
	用一个数组来创建AVL树
	vector<T> v:用来创建AVL树的数组
*/
template <typename T>
AVLTree<T>::AVLTree(vector<T> v)
{
	root = new TreeNode<T>(v.front(), 1);
	for (unsigned int i = 1; i < v.size(); i++)
		insert(v[i]);
}

//------------------------------------------------------
/*
	销毁一个二叉树
	TreeNode<T>* &root:二叉树的根结点

	@Return void
*/
template <typename T>
void destroyBiTree(TreeNode<T>* &root)
{
	if (root)
	{
		TreeNode<T> *left;
		TreeNode<T> *right;
		left = root->left;
		right = root->right;
		delete root;
		root = nullptr;
		if (left)
			destroyBiTree(left);
		if (right)
			destroyBiTree(right);
	}
}

//------------------------------------------------------
/*
	析构函数
*/
template <typename T>
AVLTree<T>::~AVLTree()
{
	destroyBiTree(root);
	_size = 0;
}

//------------------------------------------------------
/*
	先序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void Per(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		v.push_back(root->key);
		Per(root->left, v);
		Per(root->right, v);
	}
}

//------------------------------------------------------
/*
	先序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> AVLTree<T>::PerOrderTraverse()
{
	vector<T> v;
	Per(root, v);
	return v;
}

//------------------------------------------------------
/*
	中序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void In(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		In(root->left, v);
		v.push_back(root->key);
		In(root->right, v);
	}
}

//------------------------------------------------------
/*
	中序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> AVLTree<T>::InOrderTraverse()
{
	vector<T> v;
	In(root, v);
	return v;
}

//------------------------------------------------------
/*
	后序遍历
	TreeNode<T>* &root:二叉树的根结点
	vector<T> &v:存储遍历结果的数组

	@Return void
*/
template <typename T>
void Post(TreeNode<T>* &root, vector<T> &v)
{
	if (root)
	{
		Post(root->left, v);
		Post(root->right, v);
		v.push_back(root->key);
	}
}

//------------------------------------------------------
/*
	后序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> AVLTree<T>::PostOrderTraverse()
{
	vector<T> v;
	Post(root, v);
	return v;
}

//------------------------------------------------------
/*
	层序遍历,并把遍历结果返回到一个数组上

	@Return vector<T>
*/
template <typename T>
vector<T> AVLTree<T>::LevelOrderTraverse()
{
	vector<T> v;
	if (!root)
		return v;

	queue<TreeNode<T>*> q;
	q.push(root);
	while (!q.empty())
	{
		TreeNode<T>* Node;
		Node = q.front();
		v.push_back(Node->key);
		q.pop();
		if (Node->left)
			q.push(Node->left);
		if (Node->right)
			q.push(Node->right);
	}
	return v;
}

//------------------------------------------------------
/*
	清空二叉树

	@Return void
*/
template <typename T>
void AVLTree<T>::clear()
{
	destroyBiTree(root);
	_size = 0;
}

//------------------------------------------------------
/*
	判断二叉树是否为空

	@Return bool
*/
template <typename T>
bool AVLTree<T>::isEmpty()
{
	return _size == 0;
}

//------------------------------------------------------
/*
	判断是否为平衡二叉树
	TreeNode<T>* &root:二叉树的根结点

	@Return bool
*/
template <typename T>
bool isBalancedBiTree(TreeNode<T>* &root)
{
	if (!root)
		return true;

	if (!root->left && !root->right)
		return true;
	else if (abs(getHeight(root->left) - getHeight(root->right)) > 1)
		return false;
	else
		return isBalancedBiTree(root->left) && isBalancedBiTree(root->right);
}

//------------------------------------------------------
/*
	判断是否为平衡二叉树
	在AVL树中该函数始终返回true

	@Return bool
*/
template <typename T>
bool AVLTree<T>::isBalanced()
{
	return isBalancedBiTree(root);
}

//------------------------------------------------------
/*
	返回二叉树的高度
	TreeNode<T>* &root:二叉树的根结点

	@Return int
*/
template <typename T>
int getHeight(TreeNode<T>* &root)
{
	if (!root)
		return 0;

	return root->height;
}

//------------------------------------------------------
/*
	返回二叉树的高度

	@Return int
*/
template <typename T>
int AVLTree<T>::height()
{
	if (!root)
		return 0;

	return root->height;
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数
	TreeNode<T>* &root:二叉树的根结点

	@Return int
*/
template <typename T>
int getSize(TreeNode<T>* &root)
{
	if (root)
		return 1 + getSize(root->left) + getSize(root->right);
	else
		return 0;
}

//------------------------------------------------------
/*
	返回二叉树中结点的个数

	@Return int
*/
template <typename T>
int AVLTree<T>::size()
{
	return _size;
}

//------------------------------------------------------
/*
	返回AVL树中存储最大值的结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* getMax(TreeNode<T>* &root)
{
	if (!root)
		return nullptr;

	TreeNode<T>* temp;
	temp = root;
	while (temp->right)
		temp = temp->right;
	return temp;
}

//------------------------------------------------------
/*
	返回AVL树中存储的最大值

	@Return T
*/
template<typename T>
T AVLTree<T>::maximum()
{
	if (!root)
		return NULL;

	TreeNode<T> *Maximum;
	Maximum = getMax(root);
	return Maximum->key;
}

//------------------------------------------------------
/*
	返回AVL树中存储最小值的结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* getMin(TreeNode<T>* &root)
{
	if (!root)
		return nullptr;

	TreeNode<T>* temp;
	temp = root;
	while (temp->left)
		temp = temp->left;
	return temp;
}

//------------------------------------------------------
/*
	返回AVL树中存储的最小值

	@Return T
*/
template <typename T>
T AVLTree<T>::minimum()
{
	if (!root)
		return NULL;

	TreeNode<T> *Minimum;
	Minimum = getMin(root);
	return Minimum->key;
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	TreeNode<T>* &root:AVL树的根结点
	T val:要搜索的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* searchIn(TreeNode<T>* &root, T val)
{
	if (root == nullptr)
		return nullptr;

	if (root->key == val)
		return root;
	else
		if (root->key > val)
			return searchIn(root->left, val);
		else
			return searchIn(root->right, val);
}

//------------------------------------------------------
/*
	搜索结点,若找到就返回该结点,若没找到就返回nullptr
	T e:要搜索的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* AVLTree<T>::search(T e)
{
	return searchIn(root, e);
}

//------------------------------------------------------
/*
	LL旋转,返回旋转后的根结点
	TreeNode<T>* &k2:被旋转的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* leftLeftRotation(TreeNode<T>* &k2)
{
	TreeNode<T> *k1;

	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
	k1->height = max(getHeight(k1->left), getHeight(k2)) + 1;

	return k1;
}

//------------------------------------------------------
/*
	RR旋转,返回旋转后的根结点
	TreeNode<T>* &k1:被旋转的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* rightRightRotation(TreeNode<T>* &k1)
{
	TreeNode<T> *k2;

	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
	k2->height = max(getHeight(k2->right), getHeight(k1)) + 1;

	return k2;
}

//------------------------------------------------------
/*
	LR旋转,返回旋转后的根结点
	TreeNode<T>* &k3:被旋转的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* leftRightRotation(TreeNode<T>* &k3)
{
	k3->left = rightRightRotation(k3->left);
	return leftLeftRotation(k3);
}

//------------------------------------------------------
/*
	RL旋转,返回旋转后的根结点
	TreeNode<T>* &k1:被旋转的根结点

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* rightLeftRotation(TreeNode<T>* &k1)
{
	k1->right = leftLeftRotation(k1->right);
	return rightRightRotation(k1);
}

//------------------------------------------------------
/*
	插入结点,并返回插入后的根结点
	若插入后AVL树失去平衡,会自动回复平衡
	TreeNode<T>* &root:AVL树的根结点
	T val:要插入的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* insertIn(TreeNode<T>* &root, T _key)
{
	if (!root)
		//AVL树为空的情况
		root = new TreeNode<T>(_key, 1);

	if (root->key > _key)
	{
		//要插入的结点在左子树的情况
		root->left = insertIn(root->left, _key);
		if (getHeight(root->left) - getHeight(root->right) == 2)
		{
			//若AVL树失去平衡,将自动恢复平衡,先LL,再LR
			if (root->left->key > _key)
				root = leftLeftRotation(root);
			else
				root = leftRightRotation(root);
		}
	}
	else if (root->key < _key)
	{
		//要插入的结点在右子树的情况
		root->right = insertIn(root->right, _key);
		if (getHeight(root->right) - getHeight(root->left) == 2)
		{
			//若AVL树失去平衡,将自动恢复平衡,先RR,再RL
			if (root->right->key < _key)
				root = rightRightRotation(root);
			else
				root = rightLeftRotation(root);
		}
	}

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	return root;
}

//------------------------------------------------------
/*
	插入结点,若插入成功则返回true,失败则返回false
	若插入后AVL树失去平衡,会自动回复平衡
	T e:要插入的值

	@Return bool
*/
template <typename T>
bool AVLTree<T>::insert(T e)
{
	if (search(e))
		return false;

	root = insertIn(root, e);
	_size++;
	return true;
}

//------------------------------------------------------
/*
	删除结点,并返回删除后的根结点
	若删除后AVL树失去平衡,会自动回复平衡
	TreeNode<T>* &root:AVL树的根结点
	T val:要删除的值

	@Return TreeNode<T>*
*/
template <typename T>
TreeNode<T>* removeAt(TreeNode<T>* &root, T _key)
{
	if (!root)
		//没有要删除的结点的情况
		return nullptr;

	if (root->key > _key)
	{
		//要删除的结点在左子树的情况
		root->left = removeAt(root->left, _key);
		if (getHeight(root->right) - getHeight(root->left) == 2)
		{
			//若AVL树失去平衡,将自动恢复平衡,先RL,再RR
			TreeNode<T> *r = root->right;
			if (getHeight(r->left) > getHeight(r->right))
				root = rightLeftRotation(root);
			else
				root = rightRightRotation(root);
		}
	}
	else if (root->key < _key)
	{
		//要删除的结点在右子树的情况
		root->right = removeAt(root->right, _key);
		if (getHeight(root->left) - getHeight(root->right) == 2)
		{
			//若AVL树失去平衡,将自动恢复平衡,先LR,再LL
			TreeNode<T> *l = root->left;
			if (getHeight(l->right) > getHeight(l->left))
				root = leftRightRotation(root);
			else
				root = leftLeftRotation(root);
		}
	}
	else
	{
		//要删除的结点就是该结点的情况
		if (root->left&&root->right)
		{
			//若要删除的结点的左右孩子都非空
			if (getHeight(root->left) > getHeight(root->right))
			{
				// 如果要删除的结点的左子树比右子树高
				// 则(01)找出要删除的结点的左子树中的最大节点
				//   (02)将该最大节点的值赋值给要删除的结点
				//   (03)删除该最大节点
				// 这类似于用"要删除的结点的左子树中最大节点"做"要删除的结点"的替身
				// 采用这种方式的好处是:删除"要删除的结点的左子树中最大节点"之后,AVL树仍然是平衡的
				TreeNode<T> *Maximum;
				Maximum = getMax(root->left);
				root->key = Maximum->key;
				root->left = removeAt(root->left, Maximum->key);
			}
			else
			{
				// 如果要删除的结点的左子树不比右子树高(即它们相等,或右子树比左子树高1)
				// 则(01)找出要删除的结点的右子树中的最小节点
				//   (02)将该最小节点的值赋值给要删除的结点
				//   (03)删除该最小节点
				// 这类似于用"要删除的结点的右子树中最小节点"做"要删除的结点"的替身
				// 采用这种方式的好处是:删除"要删除的结点的右子树中最小节点"之后,AVL树仍然是平衡的
				TreeNode<T> *Minimum;
				Minimum = getMin(root->right);
				root->key = Minimum->key;
				root->right = removeAt(root->right, Minimum->key);
			}
		}
		else
		{
			//若要删除的结点的左右孩子至少有一个为空的情况
			TreeNode<T> *temp;
			temp = root;
			root = root->left ? root->left : root->right;
			delete temp;
			temp = nullptr;
		}
	}
	return root;
}

//------------------------------------------------------
/*
	删除结点,若删除成功则返回true,失败则返回false
	若删除后AVL树失去平衡,会自动回复平衡
	T e:要删除的值

	@Return bool
*/
template <typename T>
bool AVLTree<T>::remove(T e)
{
	if (!search(e))
		return false;

	removeAt(root, e);
	_size--;
	return true;
}

//------------------------------------------------------
/*
	重载[]操作符,按中序遍历输出
	int r:索引

	@Return T
*/
template <typename T>
T AVLTree<T>::operator[] (int r)
{
	if (r < 0 || r >= _size)
		return NULL;

	vector<T> v = InOrderTraverse();
	return v[r];
}

//------------------------------------------------------
/*
	重载<<操作符,按中序遍历输出
	ostream &os:输出流
	AVLTree<T> &m:要输出的二叉搜索树

	@Return ostream
*/
template <typename T>
ostream &operator<<(ostream &os, AVLTree<T> &m)
{
	vector<T> v = m.InOrderTraverse();
	if (v.size() == 0)
		return os;

	if (v.size() == 1)
	{
		os << v.front();
		return os;
	}
	else
	{
		for (unsigned int i = 0; i < v.size() - 1; i++)
			os << v[i] << " ";
		os << v.back();
		return os;
	}
}

#endif // !AVLTREE
