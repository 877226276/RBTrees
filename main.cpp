#include<iostream>
#include<assert.h>
using namespace std;


//红黑树节点类型
typedef enum{RED=0,BLACK}Color;

//红黑树的节点类型定义
template<typename Type>
struct RBTNode
{
	Color color;//颜色

	Type key;//关键字

	RBTNode* left;//左孩子

	RBTNode* right;//右孩子

	RBTNode* parent;//父节点
};

//红黑树类型
template <typename Type>
class RBTree
{
public:
	//构造函数
	RBTree()
	{
		Nil = BuyNode();
		root = Nil;
		Nil->color = BLACK;
	}

	//析构函数
	~RBTree()
	{
		destroy(root);//销毁创建的非Nil节点
		delete Nil;//最后删除Nil节点
		Nil = NULL;
	}

	//中序遍历
	void InOrder()
	{
		InOrder(root);
	}

	//插入
	//1、RBT方式插入
	//2、调整平衡
	bool Insert(const Type& value)
	{
		RBTNode<Type>* pr = Nil;//pr用来记住父系节点
		RBTNode<Type>* s = root;//定义变量s指向跟

		while (s != Nil)
		{
			if (value == s->key)
			{
				return false;
			}
			pr = s;
			if (value < s->key)
			{
				s = s->left;
			}
			else
			{
				s = s->right;
			}
		}//循环后 s==Nil   pr为s的父节点

		s = BuyNode(value);//申请节点

		if (pr == Nil)//如果红黑树中没有元素   s为跟节点  pr为Nil
		{
			root = s;
			root->parent = pr;
		}
		else
		{
			if (value < pr->key)
			{
				pr->left = s;
			}
			else
			{
				pr->right = s;
			}
			s->parent = pr;
		}
		//调整
		Insert_Fixup(s);
		return true;
	}

	//删除key节点   先查找  再调用内部删除
	void Remove(Type key)
	{
		RBTNode<Type>* t;
		t = Search(root, key);
		if (t != Nil)
		{
			Remove(t);
		}
		else
		{
			cout << "key is not exist" << endl;
		}
	}

	//中序遍历打印节点  详细打印
	void InOrderPrint()
	{
		InOrderPrint(root);
	}

protected:
	//申请节点   将节点的颜色初始为红色  初始化节点的关键字  其他初始化为空
	RBTNode<Type>* BuyNode(const Type& x = Type())
	{
		RBTNode<Type>* s = new RBTNode<Type>();
		assert(s != NULL);
		s->color = RED;
		s->left = s->right = s->parent = Nil;
		s->key = x;
		return s;
	}

	//中序遍历
	void InOrder(RBTNode<Type>* root)
	{
		if (root != Nil)
		{
			InOrder(root->left);
			cout << root->key << " ";
			InOrder(root->right);
		}
	}

	//左转  对z节点进行左转
	void LeftRotate(RBTNode<Type>* z)
	{
		//用y指向z的右节点
		RBTNode<Type>* y = z->right;
		z->right = y->left;
		if (y->left != Nil)
		{
			y->left->parent = z;
		}
		y->parent = z->parent;
		if (root == z)
		{
			root = y;
		}
		else if(z->parent->left==z)//z在左节点
		{
			z->parent->left = y;
		}
		else//z在右节点
		{
			z->parent->right = y;
		}
		y->left = z;
		z->parent = y;
	}

	//右转  对z进行右转
	void RightRotate(RBTNode<Type>* z)
	{
		RBTNode<Type>* y = z->left;
		z->left = y->right;
		if (y->right != Nil)
		{
			y->right->parent = z;
		}
		y->parent = z->parent;
		if (root == z)
		{
			root = y;
		}
		else if (z->parent->left == z)
		{
			z->parent->left = y;
		}
		else
		{
			z->parent->right = y;
		}
		y->right = z;
		z->parent = y;
	}
	    
	//插入后的调整函数
	void Insert_Fixup(RBTNode<Type>* s)
	{
		RBTNode<Type>* uncle;//父节点的兄弟节点
		while (s->parent->color == RED)//父节点的颜色为红色
		{
			if (s->parent == s->parent->parent->left)//父节点为左节点
			{
				uncle = s->parent->parent->right;
				if (uncle->color == RED)//叔节点为红色
				{
					//将父节点和叔节点变为黑色
					uncle->color = BLACK;
					s->parent->color = BLACK;
					//将祖父的颜色变为红色
					s->parent->parent->color = RED;
					//将指针指向祖父
					s = s->parent->parent;
				}
				else//没有叔节点或者为黑色
				{
					if (s == s->parent->right)//s在右节点上
					{
						s = s->parent;//先将指针指向父节点
						LeftRotate(s);//再左转
					}
					//如果s在左节点上
					//将父节点变为黑色   祖父节点变为红色   再右转祖父节点
					s->parent->color = BLACK;
					s->parent->parent->color = RED;
					RightRotate(s->parent->parent);
				}
			}
			else//父节点在右节点
			{
				uncle = s->parent->left;
				if (uncle->color == RED)
				{
					s->parent->color = BLACK;
					uncle->color = BLACK;
					s->parent->parent->color = RED;
					s = s->parent->parent;
				}
				else
				{
					if (s = s->parent->right)
					{
						s = s->parent;
						LeftRotate(s);
					}
					s->parent->parent->color = RED;
					s->parent->color = BLACK;
					RightRotate(s->parent->parent);
				}
			}
		}
		root->color = BLACK;//最后将根节点调整为黑色
	}

	//查找key节点
	RBTNode<Type>* Search(RBTNode<Type>* root, Type key)const
	{
		if (root == Nil)//root为空  红黑树为空
		{
			return Nil;
		}
		if (root->key == key)
		{
			return root;
		}
		else if (key < root->key)
		{
			return Search(root->left, key);
		}
		else
		{
			return Search(root->right, key);
		}
	}

	//将u的子字节v指向u的指针改为指向u的父节点
	void Transplant(RBTNode<Type>* u, RBTNode<Type>* v)
	{
		if (u->parent == Nil)//u的父节点为空   u为根节点
		{
			root = v;
		}
		else if (u == u->parent->left)//u为左节点
		{
			u->parent->left = v;
		}
		else//u为右节点
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	//找到root右边的最小值
	RBTNode<Type>* Minmum(RBTNode<Type>* x)
	{
		if (x->left == Nil)
		{
			return x;
		}
		return Minmum(x->left);
	}

	//删除红黑树节点z
	void Remove(RBTNode<Type>* z)
	{
		RBTNode<Type>* x = Nil;
		RBTNode<Type>* y = z;//记住z的位置
		Color ycolor = y->color;
		if (z->left == Nil)//只有右节点
		{
			y = z->right;
			Transplant(z, z->right);
		}
		else if (z->right == Nil)//只有左节点
		{
			y = z->left;
			Transplant(z, z->left);
		}
		else//左右节点都有
		{
			y = Minmum(z->right);//y是z右节点最小的值
			ycolor = y->color;
			x = y->right;
			if (y->parent == z)//z右节点没有左节点
			{
				x->parent = y;
			}
			else//z的右节点有最小值
			{
				Transplant(y, x);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			//改变指针方向
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (ycolor == BLACK)
		{
			Remove_Fixup(x);
		}
	}

	//红黑树删除调整
	void Remove_Fixup(RBTNode<Type>* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->left)//x在x的左子树
			{
				RBTNode<Type>* w = x->parent->right;//w是x的兄弟节点
				if (w->color == RED)
				{
					w->color = BLACK;
					x->parent->color = RED;
					LeftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->right->color == BLACK)
					{
						w->color = RED;
						w->left->color = BLACK;
						RightRotate(w);
						w = x->parent->right;
					}
					w->color = w->parent->color;
					w->parent->color = BLACK;
					w->right->color = BLACK;
					LeftRotate(x->parent);
					x = root;//结束循环
				}
			}
			else//在右子树上
			{
				RBTNode<Type>* w = x->parent->left;
				if (w->color == RED)
				{
					w->parent->color = RED;
					w->color = BLACK;
					RightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == BLACK && w->right->color == BLACK)
				{
					w->color = RED;
					x = x->parent;
				}
				else
				{
					if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						LeftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					w->parent->color= BLACK;
					w->left->color = BLACK;
					RightRotate(x->parent);
					x = root;//循环结束
				}
			}
		}
		x->color = BLACK;
	}

	//销毁红黑树
	void destroy(RBTNode<Type>*& root)
	{
		if (root == Nil)
		{
			return ;
		}
		if (root->left != Nil)
		{
			destroy(root->left);
		}
		if (root->right != Nil)
		{
			destroy(root->right);
		}
		delete root;
		root = NULL;
	}

	//打印红黑树（详细打印）
	void InOrderPrint(RBTNode<Type>* node)
	{
		if (node == Nil)
		{
			return;
		}
		if (node->left != Nil)
		{
			InOrderPrint(node->left);
		}
		cout << node->key << "(" << ((node->color == BLACK) ? "BLACK" : "RED") << ")" << " ";
		if (node->right != Nil)
		{
			InOrderPrint(node->right);
		}
	}

private:
	RBTNode<Type>* root;//跟指针
	RBTNode<Type>* Nil;//外部指针  表示空节点
};

int main(int argc, char* argv[])
{
	RBTree<int> rb;

	int arr[] = { 10, 7, 8, 15, 5, 6, 11 };
	int n = sizeof(arr) / sizeof(int);
	for (int i = 0; i < n; i++)
	{
		rb.Insert(arr[i]);
	}

	rb.InOrder();
	cout << endl;
	rb.InOrderPrint();
	cout << endl;
	rb.Remove(10);
	rb.InOrder();
	cout << endl;
	rb.InOrderPrint();
	cout << endl;
	rb.Remove(21);
	return 0;
}

