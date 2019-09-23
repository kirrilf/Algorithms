
#include <iostream>

using namespace std;


template<typename T>
class List {

public:

	List();
	~List();
	void pop_back();
	void push_back(T data);
	void pop_front();
	void push_front(T data);
	void clear();
	int GetSize() { return Size; }
	T& operator[](const int index);
	

private:

	template<typename T>
	class Node 
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;

		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}

		
	};
	int Size;
	Node<T>* head;
	Node<T>* tail;
};

template<typename T>
List<T>::List() {
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
List<T>::~List() {
	clear();
}

template<typename T>
void List<T>::pop_back()
{
	if (!tail)
		cout << "Empty" << endl;
	else
	{
		Node<T>* temp = tail;
		tail = tail->pPrev;
		delete temp;
		if (tail)
			tail->pNext = nullptr;
		Size--;
	}
}

template<typename T>
void List<T>::push_back(T data) {
	Node<T>* temp = new Node<T>(data);
	temp->pNext = nullptr;
	temp->pPrev = nullptr;

	if (tail == nullptr)
	{
		head = temp;
		tail = temp;
		head->pNext = tail;
		tail->pPrev = head;
	}
	else
	{
		temp->pPrev = tail;
		tail->pNext = temp;
		tail = temp;
	}
	Size++;

}
template<typename T>
void List<T>::pop_front()
{
	if (!head)
		cout << "Empty" << endl;
	else
	{
		Node<T>* temp = head;
		head = head->pNext;
		delete temp;
		if (head)
			head->pPrev = nullptr;
		Size--;
	}

}

template<typename T>
void List<T>::push_front(T data)
{
	Node<T>* temp = new Node<T>(data);
	temp->pNext = nullptr;
	temp->pPrev = nullptr;

	if (head == nullptr)
	{
		head = temp;
		tail = temp;
		head->pNext = tail;
		tail->pPrev = head;
	}
	else
	{
		temp->pNext = head;
		head->pPrev = temp;
		head = temp;
	}
	Size++;
}

template<typename T>
void List<T>::clear()
{
	while (Size) 
	{
		pop_front();
	}

}


template<typename T>
T& List<T>::operator[](const int index)
{
	
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr) 
	{
		if (counter == index) 
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}


}





int main()
{
	List<int> lst;
	lst.push_back(5);
	lst.push_back(10);
	lst.push_front(11);
	lst.pop_front();
	lst.pop_back();
	lst.clear();
	

	for (int i = 0; i < lst.GetSize(); i++) {
		cout << lst[i] << endl;
	}
	

	return 0;
}

