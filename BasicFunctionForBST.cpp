#include <iostream>
using namespace std;

// Các hàm cơ bản cho các cấu trúc cây nhị phân:
struct Node{
   int data;
   Node* right, *left;
};
typedef Node* Tree;

void createTree(Tree& root){
  root = NULL;
}
Node* createNode(int x){
   Node* n = new Node();
   n->data = x;
   n->right = n->left = NULL;
   return n;
}

void preOrder(Tree r) {
	if (r != NULL) {
		cout << r->data << " ";
		preOrder(r->left);
		preOrder(r->right);
	}
}

void inOrder(Tree r) {
	if (r != NULL) {
		inOrder(r->left);
		cout << r->data << " ";
		inOrder(r->right);
	}
}

void postOrder(Tree r) {
	if (r != NULL) {
		postOrder(r->left);
		postOrder(r->right);
		cout << r->data << " ";
	}
}


int main(){
  
  cin.ignore();
  cin.get();
}
