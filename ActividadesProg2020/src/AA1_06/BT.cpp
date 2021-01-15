#include "BT.h"

BT::BT() {
	root = new Node(2);
	root->left = new Node(7);
	root->right = new Node(5);
	root->left->right = new Node(6);
	root->left->right->left = new Node(1);
	root->left->right->right = new Node(11);
	root->right->right = new Node(9);
	root->right->right->left = new Node(4);
};

//Implementar (AA106)
BT::~BT() {
	Destroy(root);
}

void BT::PreOrder()
{
	PreOrder(root);
}

void BT::PreOrder(Node* n)
{
	if (n == nullptr) return;
	std::cout << n->key << '-';  //raiz
	PreOrder(n->left);	  // se va al hijo izquierdo
	PreOrder(n->right);	  // se va al hijo derecho
}

void BT::InOrder()
{
	InOrder(root);
}

void BT::InOrder(Node* n)
{
	if (n == nullptr) return;
	InOrder(n->left);	  // se va al hijo izquierdo
	std::cout << n->key;  //raiz
	InOrder(n->right);	  // se va al hijo derecho
}

void BT::PostOrder()
{
	PostOrder(root);
}

void BT::PostOrder(Node* n)
{
	if (n == nullptr) return;
	PostOrder(n->left);	  // se va al hijo izquierdo
	PostOrder(n->right);	  // se va al hijo derecho
	std::cout << n->key;  //raiz
}

//Implementar (AA106)
bool BT::Exist(int key)
{
	return Exist(root, key);
}

bool BT::Exist(Node* n, int key)
{
	if (n == nullptr) return false;
	if (n->key == key) return true;
	bool e1 = Exist(n->left, key);
	if (e1) return true;
	bool e2 = Exist(n->right, key);
	return e2;
}

//Implementar (AA106)
BT::Node* BT::Search(int key)
{
	return Search(root, key);
}

BT::Node* BT::Search(Node* n, int key)
{
	Node* tmp;
	if (n == nullptr) return tmp = nullptr;
	if (n->key == key) return tmp = n;
	Node* s1 = Search(n->left, key);
	if (s1 != nullptr) return s1;
	Node* s2 = Search(n->right, key);
	return s2;
}

//Implementar uno de los siguientes: PreOrderI, InOrderI o PostOrderI
void BT::PreOrderI()
{
	Node* n = root;
	//Caso: tree no vacio
	if (n != nullptr)
	{
		std::queue<Node*> q;  //para guardar a los nodos que me quedan por visitar

		int count = 0; // contador de nodos
		q.push(n);
		while (!q.empty())
		{
			Node *temp = q.front();
			q.pop();

			std::cout << temp->key;  //raiz

			if (temp->left != nullptr)
				q.push(temp->left);

			else if (temp->right != nullptr)
				q.push(temp->right);
		}
	}
	//Caso: tree vacio
	else {}
}

void BT::InOrderI()
{
}

void BT::PostOrderI()
{
}

//Devuelve en un vector los valores pares encontrados 
void BT::GetNPair(std::vector<int>& v) {
	return GetNPair(root, v);
};
void BT::GetNPair(Node* n, std::vector<int>& v) {
	if (n == nullptr) return;
	if (n->key % 2 == 0) { v.push_back(n->key); };
	GetNPair(n->left, v);
	GetNPair(n->right, v);
}

//Implementar (AA106)
int BT::Height()
{
	Node* n = root;
	if (n == nullptr) return 0;
	else {
		int leftH = GetNumberNodes(n->left);
		int rightH = GetNumberNodes(n->right);
		if (leftH >= rightH)
			return leftH;
		else
			return rightH;
	}
}

bool BT::IsBalanced(Node* n)
{
	return true;
}

//Implementar (AA106)
bool BT::IsBalanced() {
	return true;
}

void BT::Destroy(Node* n)
{
	if (n != nullptr) {
		Destroy(n->left);
		Destroy(n->right);
		delete n;
	}
}

//Implementar (AA106)
int BT::Max()
{
	return 0;
}

//Implementar (AA106)
int BT::Min()
{
	return 0;
}


//Versión recursiva
int BT::GetNumberNodes() {
	return GetNumberNodes(root);
}

int BT::GetNumberNodes(Node* n) {
	if (n == nullptr) return 0;
	return GetNumberNodes(n->left) + GetNumberNodes(n->right) + 1;
}

//Versión iterativa
int BT::GetNumberNodesI() {
	Node* n = root;
	// Caso: tree vacio
	if (n == nullptr)	return 0;

	//Caso: tree no vacio
	std::queue<Node*> q;  //para guardar a los nodos que me quedan por visitar

	int count = 0; // contador de nodos
	q.push(n);
	while (!q.empty())
	{
		Node* temp = q.front();
		q.pop();

		count++;

		if (temp->left != nullptr)
			q.push(temp->left);

		if (temp->right != nullptr)
			q.push(temp->right);
	}
	return count;
}