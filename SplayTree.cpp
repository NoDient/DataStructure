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

Node* RightRotation(Node*& r) {
	Node* X = r->left;
	r->left = X->right;
	X->right = r;
	r = X;
	return r;
}

Node* LeftRotation(Node*& r) {
	Node* X = r->right;
	r->right = X->left;
	X->left = r;
	r = X;
	return r;
}

Node* Splay(Node*& r, int x) {
	if (r == NULL || r->data == x) return r; // không cần loe
	else if (r->data > x) { // sang cây con trái
		if (r->left == NULL) return r; // không có cây trái
		else if (r->left->data > x) { // sang cây con trái (Zig-Zig)
			r->left->left = Splay(r->left->left, x);
			r = RightRotation(r);
		}
		else if (r->left->data < x) { // sang cây con phải (Zig-Zag)
			r->left->right = Splay(r->left->right, x);
			r->left = LeftRotation(r->left);
		}
		r = RightRotation(r);
	}
	else if (r->data < x) { // sang cây con phải
		if (r->right == NULL) return r; // không có cây phải
		else if (r->right->data < x) { // sang cây phải (Zig-Zig)
			r->right->right = Splay(r->right->right, x);
			r = LeftRotation(r);
		}
		else if (r->right->data > x) { // sang cây trái (Zig-Zag)
			r->right->left = Splay(r->right->left, x);
			r->right = RightRotation(r->right);
		}
		r = LeftRotation(r);
	}
	return r;
}


Node* Insert(Node*& r, int x) {
	if (r == NULL) {
		r = createNode(x);
		return r;
	}
	if (x > r->data) return Insert(r->right, x);
	else if (x < r->data) return Insert(r->left, x);
	else return r; // khóa đã tồn tại trong cây
}

Node* InsertAndSplay(Node*& r, int x) {
	Insert(r, x);
	Splay(r, x);
	return r;
}

Node* Delete(Node*& r, int x) {
	Splay(r, x); // loe nút có khóa x lên làm nút gốc
	if (r->data != x) return r; // không tìm thấy nút xóa
	Splay(r->left, r->data); // tìm nút tận cùng bên phải cây trái
	if (r->left != NULL) {
		Node* temp = r;
		r->left->right = r->right;
		r = r->left;
		delete temp;
	}
	return r; // trả về nút r mới
}

Node* Find(Node* r, int x) {
	r = Splay(r, x);
	if (r->data != x) return NULL; // không tìm thấy
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
		else InsertAndSplay(root, x);
	} while (true);

	cout << "\nXuat cay:";
	cout << "\nNLR: "; preOrder(root);
	cout << "\nLNR: "; inOrder(root);
	cout << "\nLRN: "; postOrder(root);

	// Xóa nút
	int del_value;
	cout << "\n\nNhap gia tri can xoa: ";
	cin >> del_value;
	Delete(root, del_value);
	cout << "\nCay sau khi xoa nut :" << del_value;
	cout << "\nNLR: "; preOrder(root);
	cout << "\nLNR: "; inOrder(root);
	cout << "\nLRN: "; postOrder(root);

	cin.ignore();
	cin.get();
	return 0;
}