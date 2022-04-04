#include <iostream>
#include <algorithm>
using namespace std;

#define stop_value -999

struct Node {
	int data;
	Node* right, * left; // chứa 2 nút con phải và trái
};
typedef Node* Tree;

void createTree(Tree& r) {
	r = NULL;
}

Node* createNode(int value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->left = newNode->right = NULL;
	return newNode;
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

Node* RotateRight(Node*& r) {
	Node* X = r->left;
	r->left = X->right;
	X->right = r;
	r = X;
	return r;
}

Node* RotateLeft(Node*& r) {
	Node* X = r->right;
	r->right = X->left;
	X->left = r;
	r = X;
	return r;
}

Node* Insert(Node*& r, int x) {
	if (r == NULL) {
		r = createNode(x);
		return r;
	}
	if (x > r->data) r->right = Insert(r->right, x);
	else if (x < r->data) r->left = Insert(r->left, x);
	else return r;
	// Loe cây từ dưới lên theo luồng quay lui
	if (x > r->data) r = RotateLeft(r); // x đã được thêm vào bên phải
	else if (x < r->data) r = RotateRight(r); // x đã thêm vào bên trái
	return r;
}

Node* Delete(Node*& r, int x) {
	if (r == NULL) return r; // trường hợp đưa vào cây rỗng
	if (r->right == r->left) return r;
	else if (x > r->data && r->right != NULL) {
		r->right = Delete(r->right, x);
		r = RotateLeft(r);
	}
	else if (x < r->data && r->left != NULL) {
		r->left = Delete(r->left, x);
		r = RotateRight(r);
	}
	else return r;
	if (r->data == x) {
		Node* p = r;
		r->left = Delete(r->left, r->data);
		r->left->right = r->right;
		r = r->left;
		delete p;
	}
	return r;
}

Node* Find(Node* r, int x) {
	if (r->left == r->right) return r;
	else if (r->data < x) {
		r->right = Find(r->right, x);
		r = RotateLeft(r);
	}
	else if (r->data > x) {
		r->left = Find(r->left, x);
		r = RotateRight(r);
	}
	return r;
}

int main() {
	Tree root;
	createTree(root);
	// Nhập cây - Chèn nút
	do {
		int x = 0;
		cout << "\nNhap gia tri them vao cay (Nhap -999 de dung viec nhap): ";
		cin >> x;
		if (x == stop_value) break;
		else Insert(root, x);
	} while (true);

	cout << "\nXuat cay:";
	cout << "\nNLR: "; preOrder(root);
	cout << "\nLNR: "; inOrder(root);
	cout << "\nLRN: "; postOrder(root);

	// Xóa nút
	int del_value;
	cout << "\n\nNhap gia tri can xoa: ";
	cin >> del_value;
	Node* result = Delete(root, del_value);
	if (result == NULL) cout << "\nKhong tim thay nut can xoa!\n";
	else {
		cout << "\nCay sau khi xoa nut :" << del_value;
		cout << "\nNLR: "; preOrder(root);
		cout << "\nLNR: "; inOrder(root);
		cout << "\nLRN: "; postOrder(root);
	}
	cin.ignore();
	cin.get();
	return 0;
}