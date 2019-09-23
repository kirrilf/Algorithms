#include <iostream>

using namespace std;

#include <iomanip>

template <typename T>
class Stack
{
private:
	T* stackPtr; 
	int size; 
	int top; 
public:
	Stack(int = 40);
	~Stack();
	bool push(const T); 
	bool pop();
	int Top();
	bool empty();
	
};

template <typename T>
Stack<T>::Stack(int s)
{
	size = s;   
	stackPtr = new T[size]; 
	top = -1; 
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] stackPtr; 
}

template <typename T>
bool Stack<T>::push(const T value)
{
	if (top == size - 1)
		return false;

	top++;
	stackPtr[top] = value;

	return true;
}

template <typename T>
bool Stack<T>::pop()
{
	if (top == -1)
		return false; 

	stackPtr[top] = 0;
	top--;

	return true; 
}

template<typename T>
int Stack<T>::Top()
{
	return stackPtr[top];
}

template<typename T>
bool Stack<T>::empty()
{
	if (top == -1) {
		return false;
	}
	return true;

}





Stack <char> stckBackPolish(50);

void conversion(char now) {

	bool flag = false;
	
	while (!flag) {
		if (!stckBackPolish.empty()) {
			flag = stckBackPolish.push(now);
			
		}
		else {
			if ((now == '*' || now == '/') && (stckBackPolish.Top() == '+' || stckBackPolish.Top() == '-' || stckBackPolish.Top() == '(')) {
				flag = stckBackPolish.push(now);

			}
			else if ((now == '+' || now == '-') && stckBackPolish.Top() == '(') {
				flag = stckBackPolish.push(now);
				
			}
			else if (now == '(') {
				flag = stckBackPolish.push(now);
				
			}
			else if ((now == '+' || now == '-') && (stckBackPolish.Top() == '+' || stckBackPolish.Top() == '-' || stckBackPolish.Top() == '*' || stckBackPolish.Top() == '/' || stckBackPolish.Top() == '^')) {
				cout << (char) stckBackPolish.Top();
				stckBackPolish.pop();
				
			}
			else if (now == '^' && (stckBackPolish.Top() == '+' || stckBackPolish.Top() == '-' || stckBackPolish.Top() == '*' || stckBackPolish.Top() == '/' || stckBackPolish.Top() == '^')) {
				flag = stckBackPolish.push(now);

			}
			else if ((now == '*' || now == '/') && (stckBackPolish.Top() == '*' || stckBackPolish.Top() == '/' || stckBackPolish.Top() == '^')) {
				cout << (char) stckBackPolish.Top();
				stckBackPolish.pop();
				
			}
			else if (now == ')' && stckBackPolish.Top() == '(') {
				flag = stckBackPolish.pop();
				
			}
			else if (now == ')') {
				cout << (char) stckBackPolish.Top();
				stckBackPolish.pop();
			}


		}


	}



}


void input() {
	string str;
	cin >> str;
	bool flag = false;
	int number = 0;
	for (auto now : str) {
		if (now - '0' >= 0 && now - '0' <= 9) {
			number *= 10;
			number += (now - '0');
			flag = true;
		}
		else if (now == '+' || now == '-' || now == '*' || now == '/' || now == '(' || now == ')' || now == '^') {
			if (flag) {
				cout << number;
				flag = false;
			}
			number = 0;
			conversion(now);
		}

	}

	if (flag) {
		cout << number;
	}
	while (stckBackPolish.empty()) 
	{
		cout << (char) stckBackPolish.Top();
		stckBackPolish.pop();
	}




}




int main()
{
	

	input();
	

	return 0;
}

