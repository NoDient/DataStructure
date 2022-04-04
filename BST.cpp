#include <iostream>
#include <algorithm>
using namespace std;

#define stop_value -999

struct Node {
	int data;
	Node* left, * right;
};
typedef Node* Tree; // định danh nút thành Tree

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

Node* Insert(Tree& r, int value) {
	if (r == NULL) { // tìm thấy nút cần chèn
		r = createNode(value);
		return r;
	}
	else if (value > r->data)
		return Insert(r->right, value);
	else if (value < r->data)
		return Insert(r->left, value);
	else return NULL; // đã tồn tại nút chứa giá trị
}

Node* Delete(Tree& r, int x) {
	if (r == NULL) return r; // không có gì để xóa
	if (x > r->data) return Delete(r->right, x); // xóa sang nhánh phải
	else if (x < r->data) return Delete(r->left, x); // xóa sang nhánh trái
	else {
		Node* temp = r; // giữ lại địa chỉ của nút cần xóa
		if (r->left == NULL) r = r->right;
		else if (r->right == NULL) r = r->left;
		else {
			temp = r->left;
			while (temp->right != NULL) { // tìm nút lớn nhất cây trái
				temp = temp->right;
			}
			r->data = temp->data; // chép giá trị với nút tìm được
			return Delete(r->left, r->data);
		}
		delete temp;
	}
	return r;
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

int heightOfTree(Tree r) {
	if (r == NULL) return 0;
	return 1 + max(heightOfTree(r->right), heightOfTree(r->left));
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