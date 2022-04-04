#include <iostream>
#include <algorithm>
using namespace std;

#define stop_value -999

struct Node {
	int data;
	Node* right, * left;
	int height; // thuộc tính chiều cao
};
typedef Node* Tree;

void createTree(Tree& r) {
	r = NULL;
}

Node* createNode(int value) {
	Node* p = new Node();
	p->data = value;
	p->right = p->left = NULL;
	p->height = 1; // mặc định 1 nút mới có độ cao là 1
	return p;
}

int height(Node* r) {
	if (r == NULL) return 0;
	return r->height; //trả về độ cao nút được truyền vào
}

Node* RotateRight(Node*& r) {
	Node* X = r->left;
	r->left = X->right; // Bước 1
	X->right = r; // Bước 2
	// Cập nhật lại độ cao của 2 nút vừa thao tác
	r->height = 1 + max(height(r->left), height(r->right));
	X->height = 1 + max(height(X->left), height(X->right));
	r = X; // cập nhật lại nút cha
	return r; // trả về nút cha mới
}

Node* RotateLeft(Node*& r) {
	Node* X = r->right;
	r->right = X->left; // Bước 1
	X->left = r; // Bước 2
	// Cập nhật lại độ cao của 2 nút vừa thao tác
	r->height = 1 + max(height(r->left), height(r->right));
	X->height = 1 + max(height(X->left), height(X->right));
	r = X; // cập nhật lại nút cha
	return r; // trả về nút cha mới
}

int getBalance(Node* r) {
	if (r == NULL) return 0;
	return height(r->left) - height(r->right);
}

Node* makeBalance(Node*& r) {
	int Balance = getBalance(r);
	if (Balance > 1) { // lệch sang nhánh trái
		if (getBalance(r->left) >= 0) return RotateRight(r);
		else { // lệch trái - phải
			r->left = RotateLeft(r->left);
			return RotateRight(r);
		}
	}
	else if (Balance < -1) { // lệch sang nhánh phải
		if (getBalance(r->right) <= 0) return RotateLeft(r->left);
		else { // lệch phải - trái
			r->right = RotateRight(r->right);
			return RotateLeft(r);
		}
	}
}

Node* Insert(Node*& r, int x) {
	if (r == NULL) {
		r = createNode(x);
		return r;
	}
	else if (x > r->data) return Insert(r->right, x);
	else if (x < r->data) return Insert(r->left, x);
	else return NULL; // khóa đã tồn tại
	// cập nhật độ cao của các nút
	r->height = 1 + max(height(r->left), height(r->right));
	// Xử lý cân bằng lại cây nếu cần thiết
	makeBalance(r);
	return r;
}

Node* Delete(Node*& r, int x) {
	if (r == NULL) return r;
	if (x > r->data) r->right = Delete(r->right, x);
	else if (x < r->data) r->left = Delete(r->left, x);
	else {
		Node* temp = r;
		if (r->left == NULL) return r->right;
		else if (r->right == NULL) return r->left;
		else {
			temp = r->left;
			while (temp->right != NULL) {
				temp = temp->right;
			}
			r->data = temp->data;
			r->left = Delete(r->left, r->data);
		}
		delete temp;
	}
	r->height = 1 + max(height(r->right), height(r->left));
	makeBalance(r);
	return r;
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

Node* find(Tree r, int value) {
	if (r == NULL) return NULL;
	else {
		if (value > r->data) // tìm sang phải
			return find(r->right, value);
		else if (value < r->data) // tìm sang trái
			return find(r->left, value);
		else return r;
	}
}

int count(Tree r) {
	if (r == NULL) return 0; // cây rỗng
	return 1 + count(r->right) + count(r->left);
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