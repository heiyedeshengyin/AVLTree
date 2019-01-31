# AVLTree
其它数据结构:[二叉树](https://github.com/heiyedeshengyin/BinaryTree) [二叉搜索树](https://github.com/heiyedeshengyin/BinarySearchTree) [链表](https://github.com/heiyedeshengyin/LinkedList) [双链表](https://github.com/heiyedeshengyin/DoublyLinkedList)

### 简介
AVL树,能一直保持平衡的二叉搜索树  
注意AVL树中只能存储重载了>,<,==,>=,<=,!=这些运算符的对象  
中序遍历AVL树会从小到大输出这些对象  
代码中有详细的注释  
写这些代码花了我一晚上的时间

### 使用方法
下载解压后打开src/AVLTree.cpp  
在后面编写自己的主函数后编译运行

### 数据结构
#### AVL树结点
```cpp
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
```
#### AVL树
```cpp
template <typename T>
class AVLTree
{
	TreeNode<T> *root;	//根结点
	int _size;	//结点个数
};
```
### 函数列表
#### AVL树成员函数
AVLTree();	//无参构造函数  
AVLTree(T x);	//创建一个根结点  
AVLTree(TreeNode\<T\>* _root);	//用一个已有的根结点赋值给根结点  
AVLTree(AVLTree\<T\> &_root);	//拷贝构造函数  
AVLTree(vector\<T\> v);	//用一个数组来创建AVL树  
~AVLTree();	//析构函数  
vector\<T\> PerOrderTraverse();	//先序遍历  
vector\<T\> InOrderTraverse();	//中序遍历  
vector\<T\> PostOrderTraverse();	//后序遍历  
vector\<T\> LevelOrderTraverse();	//层序遍历  
void clear();	//清空二叉树  
bool isEmpty();	//判断二叉树是否为空  
bool isBalanced();	//判断是否为平衡二叉树,在AVL树中始终返回true  
int height();	//获取树的高度  
int size();	//获取结点个数  
T maximum();	//获取最大值  
T minimum();	//获取最小值  
TreeNode\<T\>* search(T e);	//搜索结点  
bool insert(T e);	//插入节点  
bool remove(T e);	//删除结点  
T operator[] (int r);	//重载[]操作符  

#### TreeNode结点的操作函数
TreeNode\<T\>* copyBiTree(TreeNode\<T\>* &root) //复制一个二叉树到新的内存中  
void destroyBiTree(TreeNode\<T\>* &root)  //销毁一个二叉树  
void Per(TreeNode\<T\>* &root, vector\<T\> &v)  //先序遍历  
void In(TreeNode\<T\>* &root, vector\<T\> &v) //中序遍历  
void Post(TreeNode\<T\>* &root, vector\<T\> &v) //后序遍历  
bool isBalancedBiTree(TreeNode\<T\>* &root) //判断是否为平衡二叉树,在AVL树中始终返回true  
int getHeight(TreeNode\<T\>* &root) //获取树的高度  
int getSize(TreeNode\<T\>* &root) //获取结点个数  
TreeNode\<T\>* getMax(TreeNode\<T\>* &root) //返回AVL树中存储最大值的结点  
TreeNode\<T\>* getMin(TreeNode\<T\>* &root) //返回AVL树中存储最小值的结点  
TreeNode\<T\>* leftLeftRotation(TreeNode\<T\>* &k2) //LL旋转  
TreeNode\<T\>* rightRightRotation(TreeNode\<T\>* &k1) //RR旋转  
TreeNode\<T\>* leftRightRotation(TreeNode\<T\>* &k3)  //LR旋转  
TreeNode\<T\>* rightLeftRotation(TreeNode\<T\>* &k1)  //RL旋转  
TreeNode\<T\>* searchIn(TreeNode\<T\>* &root, T val)  //搜索结点  
TreeNode\<T\>* insertIn(TreeNode\<T\>* &root, T _key) //插入节点  
TreeNode\<T\>* removeAt(TreeNode\<T\>* &root, T _key) //删除结点  
ostream &operator<<(ostream &os, AVLTree\<T\> &m) //重载<<操作符,按中序遍历输出  

### 一个主函数的例子
```cpp
#include "AVLTree.cpp"

int main()
{
	AVLTree<int> avl1;
	avl1.insert(234);
	avl1.insert(345);
	avl1.insert(456);
	avl1.insert(678);
	avl1.insert(343);
	avl1.insert(1);
	avl1.insert(2);
	avl1.insert(3);
	avl1.insert(7);
	avl1.insert(6);
	avl1.insert(5);

	cout << avl1 << endl;
	cout << avl1.size() << endl;
	cout << avl1.height() << endl;
	cout << avl1.maximum() << endl;
	cout << avl1[5] << endl;

	if (avl1.isBalanced())
		cout << "Balanced" << endl;
	else
		cout << "Not Balanced" << endl;

	AVLTree<int> avl2(avl1);

	cout << avl2 << endl;
	cout << avl2.size() << endl;
	cout << avl2.height() << endl;

	if (avl2.isBalanced())
		cout << "Balanced" << endl;
	else
		cout << "Not Balanced" << endl;

	return 0;
}
```

### 参考资料
[AVL树(二)之 C++的实现](https://www.cnblogs.com/skywang12345/p/3577360.html)
