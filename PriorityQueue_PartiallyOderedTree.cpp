#include <iostream>
#include <algorithm>
using namespace std;

#define stop_value -999
#define MAX 100

struct PriorityQueue {
	int node[MAX];
	int size;
};

void Init(PriorityQueue& q) {
	q.size = 0; // hàng ưu tiên chưa có phần tử
}

bool isEmpty(PriorityQueue q) {
	return (q.size == 0);
}

bool isFull(PriorityQueue q) {
	return (q.size == MAX);
}

int Front(PriorityQueue q) {
	if (q.size == 0) return -1;
	return q.node[0];
}

int LeftOf(int i) {
	return (2 * i + 1);
}

int RightOf(int i) {
	return (2 * i + 2);
}

int ParentOf(int k) {
	if (k % 2 == 0) return (k - 2) / 2;
	else return (k - 1) / 2;
}
int shiftUp(PriorityQueue& q) {
	int i = 0;
	for (i = q.size - 1; i > 0; i--) {
		int parent = ParentOf(i);
		if (q.node[parent] > q.node[i]) {
			swap(q.node[parent], q.node[i]);
			i = parent + 1;
		}
		else break;
	}
	return i;
}

// Đệ quy
//int shiftUp(PriorityQueue& q, int i) {
//	if (i <= 0) return 0;
//	int parent = ParentOf(i);
//	if (q.node[i] < q.node[parent]) {
//		swap(q.node[i], q.node[parent]);
//		shiftUp(q, parent);
//	}
//	else return i; // trả về vị trí của nút sau khi shift
//}

int shiftDown(PriorityQueue& q) {
	int i = 0, min_i = 0;
	for (i = 0; i < q.size; i++) {
		int left = LeftOf(i), right = RightOf(i);
		if (left >= q.size) break;
		else if (right >= q.size) min_i = left;
		else min_i = (q.node[left] > q.node[right]) ? right : left;
		if (q.node[i] > q.node[min_i]) {
			swap(q.node[i], q.node[min_i]);
			i = min_i - 1;
		}
		else break;
	}
	return i;
}

// Đệ quy
//int shiftDown(PriorityQueue& q, int i = 0) {
//	if (i >= q.size) return i;
//	int temp_idx = i;
//	int left = LeftOf(i), right = RightOf(i);
//	if (left >= q.size) return i;
//	else if (right >= q.size) i = left;
//	else i = (q.node[left] > q.node[right]) ? right : left;
//	if (q.node[temp_idx] > q.node[i]) {
//		swap(q.node[temp_idx], q.node[i]);
//		shiftDown(q, i);
//	}
//	else return temp_idx;
//}

int Insert(PriorityQueue& q, int x) {
	q.node[q.size] = x; // thêm vào cuối hàng ưu tiên
	q.size++; // tăng số lượng nút
	int i = 0;
	for (i = q.size - 1; i > 0; i--) {
		int parent_index = ParentOf(i);
		if (q.node[parent_index] > q.node[i]) {
			swap(q.node[parent_index], q.node[i]); // Bước 2.1
			i = parent_index + 1; // cộng 1 vì sau vòng lặp có i--
		}
		else break; // dừng lại - Bước 2.2
	}
	// hoặc thay vòng lặp for thành hàm shiftUp()
	// i = shiftUp(q);
	return i; // trả về vị trí mới của nút được thêm vào
}

int Delete(PriorityQueue& q) { // deQueue
	if (q.size == 0) return -1;
	int old_key = q.node[0]; // giữ lại giá trị của nút bị xóa
	q.node[0] = q.node[--q.size]; // chép giá trị với phần tử cuối
	int min_i = 0;
	for (int i = 0; i < q.size; i++) {
		int left = LeftOf(i), right = RightOf(i);
		if (left >= q.size) break; // không có nút con nào
		else if (right >= q.size) min_i = left; // có nút con trái
		else min_i = (q.node[left] > q.node[right]) ? right : left;
		if (q.node[i] > q.node[min_i]) {
			swap(q.node[i], q.node[min_i]);
			i = min_i - 1;
		}
		else break;
	}
	// hoặc thay vòng lặp for thành hàm shiftDown()
	// shiftDown(q);
	return old_key;
}



void Print(PriorityQueue q) {
	for (int i = 0; i < q.size; i++) {
		cout << q.node[i] << " ";
	}
	cout << "\n";
}

int main() {
	PriorityQueue q;
	Init(q);
	do {
		int x = 0;
		cout << "\nNhap gia tri them vao cay (Nhap -999 de dung viec nhap): ";
		cin >> x;
		if (x == stop_value) break;
		else Insert(q, x);
	} while (true);
	Print(q);
	cout << "\nSau khi xoa nut dau: ";
	Delete(q);
	Print(q);
	cin.ignore();
	cin.get();
	return 0;
}