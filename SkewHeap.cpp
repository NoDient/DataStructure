#include <iostream>
using namespace std;

#define stop_value -999
struct Node {
	int data;
	Node* right, * left;
};
typedef Node* Tree;

void createTree(Tree& root) {
	root = NULL;
}
Node* createNode(int x) {
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

void Swap(Node*& ptr1, Node*& ptr2) {
	Node* temp = ptr1;
	ptr1 = ptr2;
	ptr2 = temp;
}

Node* Merge(Node*& r1, Node*& r2) {
	if (r2 == NULL) return r1;
	else if (r1 == NULL) {
		return r1 = r2; // gán r2 cho r1 rồi trả về
	}
	else {
		Node* temp = NULL;
		if (r1->data > r2->data) Swap(r1, r2); // Bước 1
		Swap(r1->left, r1->right); // Bước 2
		r1->left = Merge(r1->left, r2); // Bước 3
	}
	r2 = NULL;
	return r1;
}

Node* Insert(Node*& r, int x) {
	Node* r2 = createNode(x);
	r = Merge(r, r2);
	return r;
}

Node* Delete(Node*& r) {
	if (r == NULL) return r;
	Node* r1 = r->left; // giữ lại cây con trái
	Node* r2 = r->right; // giữ lại cây con phải
	delete r;
	r = Merge(r1, r2); // kết hợp cây con trái và cây con phải
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

	// Xóa nút gốc
	Delete(root);
	cout << "\nCay sau khi xoa nut Min";
	cout << "\nNLR: "; preOrder(root);
	cout << "\nLNR: "; inOrder(root);
	cout << "\nLRN: "; postOrder(root);

	cin.ignore();
	cin.get();
	return 0;
}