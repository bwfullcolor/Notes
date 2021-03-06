/*
 * 一个产生AVL树的程序
 * 该树是基于非重复二叉排序树
 * 该树结点中使用指针来指向左右子树，而非数组
 */
#include <iostream>
#include <algorithm>			//使用max

using namespace std;

struct AVLNode
{
	int element;				//数据项
	AVLNode *left, *right;		//左右子树
	int height;					//此节点树的高度

	/*
	* lt -> left tree, rt -> right tree
	*/
	AVLNode(int element, AVLNode *lt, AVLNode *rt, int height = 0)
		:element(element), left(lt), right(rt), height(height)
	{}
};

/*
 * return the height of node T or -1 if NULL
 */
int height(AVLNode *T)
{
	return T == NULL ? -1 : T->height;
}

/*
 * 单旋转左子树
 * 将k2设置为k1的右子树，将Y(k1的右子树)设置为k2的左子树，将k1设置为新的根节点
 * 更新根节点(k1)与k2的高度
 * 这样是一次左子树的平衡旋转
 */
void rotateWithLeftChild(AVLNode * &k2)
{
	//记录k1结点
	AVLNode *k1 = k2->left;
	
	//更新连接关系
	k2->left = k1->right;
	k1->right = k2;
	
	//更新高度，先更新k2因为现在k1的高度依赖k2的高度
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	
	//设置根节点
	//写成这样，因为参数k2是root的别名
	k2 = k1;
}

/*
 * 单旋转右子树
 * 具体算法：左子树的对称形式
 */
void rotateWithRightChild(AVLNode * &k2)
{
	AVLNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->right), k2->height) + 1;
	k2 = k1;
}

/*
 * 双旋转左子树
 * 先将k2旋转至k3的左子树，形成一字型的单旋转形式
 * 再旋转k3，更新高度
 */
void doubleWithLeftChild(AVLNode * &k3)
{
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}

/*
 * 双旋转右子树
 * 具体算法：左子树的对称形式
 */
void doubleWithRightChild(AVLNode * &k3)
{
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}

 /*
  * 将x插入树T
  * 如果树T高度变化，则可能调整树的平衡(左右子树高度差为2)
  */
void insert(int x, AVLNode * &T)
{
	if (T == NULL)						//找到位置，插入x结点
		T = new AVLNode(x, NULL, NULL);
	else if (x < T->element)			//插入左子树
	{
		insert(x, T->left);
		if (height(T->left) - height(T->right) == 2)
			if (x < T->left->element)
				rotateWithLeftChild(T);
			else
				doubleWithLeftChild(T);
	}
	else if (T->element < x)			//插入右子树
	{
		insert(x, T->right);
		if (height(T->right) - height(T->left) == 2)
			if (T->left->element < x)
				rotateWithRightChild(T);
			else
				doubleWithRightChild(T);
	}
	else
		;		//如果重复，则不做任何事情
	T->height = max(height(T->left), height(T->right)) + 1;
}

/*
 * 删除结点x，成功返回true，失败返回false
 * 失败原因：x不存在
 * 暂时未写，留下接口
 */
bool deleteNode(int x, const AVLNode * &T);

/*
 * 中序遍历树
 */
void preorderTraverse(AVLNode *T)
{
	if (T)
	{
		preorderTraverse(T->left);
		cout << T->element << " ";
		preorderTraverse(T->right);
	}
}

int main()
{
	AVLNode * root = NULL;
	insert(10, root);
	insert(20, root);
	insert(1, root);
	insert(5, root);
	preorderTraverse(root);
	cout << endl;
	return 0;
}
