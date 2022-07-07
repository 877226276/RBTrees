#include<iostream>
#include<assert.h>
using namespace std;


//������ڵ�����
typedef enum{RED=0,BLACK}Color;

//������Ľڵ����Ͷ���
template<typename Type>
struct RBTNode
{
	Color color;//��ɫ

	Type key;//�ؼ���

	RBTNode* left;//����

	RBTNode* right;//�Һ���

	RBTNode* parent;//���ڵ�
};

//���������
template <typename Type>
class RBTree
{
public:
	//���캯��
	RBTree()
	{
		Nil = BuyNode();
		root = Nil;
		Nil->color = BLACK;
	}

	//��������
	~RBTree()
	{
		destroy(root);//���ٴ����ķ�Nil�ڵ�
		delete Nil;//���ɾ��Nil�ڵ�
		Nil = NULL;
	}

	//�������
	void InOrder()
	{
		InOrder(root);
	}

	//����
	//1��RBT��ʽ����
	//2������ƽ��
	bool Insert(const Type& value)
	{
		RBTNode<Type>* pr = Nil;//pr������ס��ϵ�ڵ�
		RBTNode<Type>* s = root;//�������sָ���

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
		}//ѭ���� s==Nil   prΪs�ĸ��ڵ�

		s = BuyNode(value);//����ڵ�

		if (pr == Nil)//����������û��Ԫ��   sΪ���ڵ�  prΪNil
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
		//����
		Insert_Fixup(s);
		return true;
	}

	//ɾ��key�ڵ�   �Ȳ���  �ٵ����ڲ�ɾ��
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

	//���������ӡ�ڵ�  ��ϸ��ӡ
	void InOrderPrint()
	{
		InOrderPrint(root);
	}

protected:
	//����ڵ�   ���ڵ����ɫ��ʼΪ��ɫ  ��ʼ���ڵ�Ĺؼ���  ������ʼ��Ϊ��
	RBTNode<Type>* BuyNode(const Type& x = Type())
	{
		RBTNode<Type>* s = new RBTNode<Type>();
		assert(s != NULL);
		s->color = RED;
		s->left = s->right = s->parent = Nil;
		s->key = x;
		return s;
	}

	//�������
	void InOrder(RBTNode<Type>* root)
	{
		if (root != Nil)
		{
			InOrder(root->left);
			cout << root->key << " ";
			InOrder(root->right);
		}
	}

	//��ת  ��z�ڵ������ת
	void LeftRotate(RBTNode<Type>* z)
	{
		//��yָ��z���ҽڵ�
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
		else if(z->parent->left==z)//z����ڵ�
		{
			z->parent->left = y;
		}
		else//z���ҽڵ�
		{
			z->parent->right = y;
		}
		y->left = z;
		z->parent = y;
	}

	//��ת  ��z������ת
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
	    
	//�����ĵ�������
	void Insert_Fixup(RBTNode<Type>* s)
	{
		RBTNode<Type>* uncle;//���ڵ���ֵܽڵ�
		while (s->parent->color == RED)//���ڵ����ɫΪ��ɫ
		{
			if (s->parent == s->parent->parent->left)//���ڵ�Ϊ��ڵ�
			{
				uncle = s->parent->parent->right;
				if (uncle->color == RED)//��ڵ�Ϊ��ɫ
				{
					//�����ڵ����ڵ��Ϊ��ɫ
					uncle->color = BLACK;
					s->parent->color = BLACK;
					//���游����ɫ��Ϊ��ɫ
					s->parent->parent->color = RED;
					//��ָ��ָ���游
					s = s->parent->parent;
				}
				else//û����ڵ����Ϊ��ɫ
				{
					if (s == s->parent->right)//s���ҽڵ���
					{
						s = s->parent;//�Ƚ�ָ��ָ�򸸽ڵ�
						LeftRotate(s);//����ת
					}
					//���s����ڵ���
					//�����ڵ��Ϊ��ɫ   �游�ڵ��Ϊ��ɫ   ����ת�游�ڵ�
					s->parent->color = BLACK;
					s->parent->parent->color = RED;
					RightRotate(s->parent->parent);
				}
			}
			else//���ڵ����ҽڵ�
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
		root->color = BLACK;//��󽫸��ڵ����Ϊ��ɫ
	}

	//����key�ڵ�
	RBTNode<Type>* Search(RBTNode<Type>* root, Type key)const
	{
		if (root == Nil)//rootΪ��  �����Ϊ��
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

	//��u�����ֽ�vָ��u��ָ���Ϊָ��u�ĸ��ڵ�
	void Transplant(RBTNode<Type>* u, RBTNode<Type>* v)
	{
		if (u->parent == Nil)//u�ĸ��ڵ�Ϊ��   uΪ���ڵ�
		{
			root = v;
		}
		else if (u == u->parent->left)//uΪ��ڵ�
		{
			u->parent->left = v;
		}
		else//uΪ�ҽڵ�
		{
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	//�ҵ�root�ұߵ���Сֵ
	RBTNode<Type>* Minmum(RBTNode<Type>* x)
	{
		if (x->left == Nil)
		{
			return x;
		}
		return Minmum(x->left);
	}

	//ɾ��������ڵ�z
	void Remove(RBTNode<Type>* z)
	{
		RBTNode<Type>* x = Nil;
		RBTNode<Type>* y = z;//��סz��λ��
		Color ycolor = y->color;
		if (z->left == Nil)//ֻ���ҽڵ�
		{
			y = z->right;
			Transplant(z, z->right);
		}
		else if (z->right == Nil)//ֻ����ڵ�
		{
			y = z->left;
			Transplant(z, z->left);
		}
		else//���ҽڵ㶼��
		{
			y = Minmum(z->right);//y��z�ҽڵ���С��ֵ
			ycolor = y->color;
			x = y->right;
			if (y->parent == z)//z�ҽڵ�û����ڵ�
			{
				x->parent = y;
			}
			else//z���ҽڵ�����Сֵ
			{
				Transplant(y, x);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			//�ı�ָ�뷽��
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (ycolor == BLACK)
		{
			Remove_Fixup(x);
		}
	}

	//�����ɾ������
	void Remove_Fixup(RBTNode<Type>* x)
	{
		while (x != root && x->color == BLACK)
		{
			if (x == x->parent->left)//x��x��������
			{
				RBTNode<Type>* w = x->parent->right;//w��x���ֵܽڵ�
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
					x = root;//����ѭ��
				}
			}
			else//����������
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
					x = root;//ѭ������
				}
			}
		}
		x->color = BLACK;
	}

	//���ٺ����
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

	//��ӡ���������ϸ��ӡ��
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
	RBTNode<Type>* root;//��ָ��
	RBTNode<Type>* Nil;//�ⲿָ��  ��ʾ�սڵ�
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

