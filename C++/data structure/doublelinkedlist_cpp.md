```
#include <iostream>

using namespace std;

template<class T>
class Node {
public:
	Node(T data) {
		value = data;
		pre = nullptr;
		next = nullptr;
	}

	~Node() {}

	Node<T>* pre;
	Node<T>* next;
	T value;
};

template<class T>
class LinkedList {
public:
	LinkedList() {
		count = 0;
		head = nullptr;
		tail = nullptr;
	}

	~LinkedList() {
		if (head->next == nullptr) {
			delete head;
			head = nullptr;
		}
		else {
			Node<T>* current;
			Node<T>* clear;
			current = head;
			while (current != nullptr) {
				clear = current;
				current = current->next;
				delete clear;
				clear = nullptr;
			}
		}
	}

	int size() { return count; }
	void front() { cout << head->value << endl; }
	void back() { cout << tail->value << endl; }

	void push_back(T value) {
		Node<T>* node = new Node<T>(value);
		if (count == 0)
			head = node;
		else {
			tail->next = node;
			node->pre = tail;
		}
		tail = node;
		count++;
	}

	void push_front(T value) {
		Node<T>* node = new Node<T>(value);
		if (count == 0)
			tail = node;
		else {
			head->pre = node;
			node->next = head;
		}
		head = node;
		count++;
	}

	void pop_back() {
		Node<T>* tmp;
		if (count == 0)
			return;
		else if (count == 1) {
			tmp = head;
			delete tmp;
			tmp = nullptr;
			head = nullptr;
			tail = nullptr;
		}
		else{
			tmp = tail;
			tail->pre->next = nullptr;
			tail = tail->pre;
			tail->next = nullptr;
			delete tmp;
			tmp = nullptr;
		}
		count--;
	}

	void pop_front() {
		Node<T>* tmp;
		if (count == 0)
			return;
		else if (count == 1) {
			tmp = head;
			delete tmp;
			tmp = nullptr;
			head = nullptr;
			tail = nullptr;
		}
		else {
			tmp = head;
			head->next->pre = nullptr;
			head = head->next;
			tmp->next = nullptr;
			delete tmp;
			tmp = nullptr;
			
		}
		count--;
	}

	void show_forward() {
		Node<T>* node = head;
		while (node != nullptr) {
			cout << node->value << " -> ";
			node = node->next;
		}
		cout << "NULL" << endl;
	}

	void show_backward() {
		Node<T>* node = tail;
		while (node != nullptr) {
			cout << node->value << " -> ";
			node = node->pre;
		}
		cout << "NULL" << endl;
	}

private:
	Node<T>* head;
	Node<T>* tail;
	int count;
};


int main()
{
	LinkedList<int> list;
	list.push_back(123);
	list.push_back(456);
	list.push_back(789);
	list.push_front(0);
	list.pop_back();
	list.pop_front();

	list.show_forward();
	list.show_backward();

	system("PAUSE");
	return 0;
}

```

 https://emn178.pixnet.net/blog/post/93557502 