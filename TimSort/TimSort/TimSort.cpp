#include <iostream>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
#include <ctime>



using namespace std;

int getMinrun(int n)
{
	int r = 0;
	while (n >= 64) {
		r |= n & 1;
		n >>= 1;
	}
	return n + r;
}



void insertionSort(int* mas, int sizeMas, int startPoint, int finishPoint) {
	for (int i = startPoint + 1; i < finishPoint; i++) {
		for (int j = i; j > startPoint; j--) {
			if (mas[j - 1] > mas[j]) {
				swap(mas[j - 1], mas[j]);

			}
		}
	}
}

void reverseMas(int* mas, int startPoint, int finishPoint) {
	for (int i = 0; i < (finishPoint-startPoint)/2; i++) {
		swap(mas[startPoint+i], mas[finishPoint - 1 - i]);
	}

}

bool timSortFinishPoint(int* mas, int sizeMas, int startPoint, int &finishPoint) {
	bool positive = true, negative = true, endPoint = false;;
	for (int i = startPoint + 1; i < sizeMas; i++) {
		if (mas[i - 1] < mas[i] && positive) {
			negative = false;
		}
		else if (mas[i - 1] > mas[i] && negative) {
			positive = false;
		}
		else if (mas[i - 1] < mas[i] && !positive) {
			finishPoint = i;
			return false;
		}
		else if (mas[i - 1] > mas[i] && !negative) {
			finishPoint = i;
			return false;
		}
		if (i == sizeMas - 1) {
			finishPoint = sizeMas;
			endPoint = true;
		}

	}
	if (startPoint == finishPoint) {
		endPoint = true;
	}
	return endPoint;
	
}



void merge(int* mas, int sizeMas, int firstStartPoint, int firstfinishPoint, int secondStartPoint, int secondFinishPoint){
	int* temp1 = new int[secondFinishPoint - secondStartPoint];
	for (int i = secondStartPoint, j = 0; i < secondFinishPoint; i++, j++) {
		temp1[j] = mas[i];
	}

	int* temp2 = new int[firstfinishPoint - firstStartPoint];
	for (int i = firstStartPoint, j = 0; i < firstfinishPoint; i++, j++) {
		temp2[j] = mas[i];
	}

	int i = 0, j = 0, k = firstStartPoint;
	while (true) {
		
		if (temp2[i] > temp1[j]) {

			mas[k] = temp1[j];
			k++;
			j++;
		}
		else {
			mas[k] = temp2[i];
			k++;
			i++;
		}
		if (i == firstfinishPoint-firstStartPoint) {
			while (j != secondFinishPoint-secondStartPoint){
				mas[k] = temp1[j];
				k++;
				j++;
			}
			
			delete[] temp1;
			delete[] temp2;
			break;
		}
		if (j == secondFinishPoint - secondStartPoint) {
			while (i != firstfinishPoint - firstStartPoint) {
				mas[k] = temp2[i];
				k++;
				i++;
			}
			
			delete[] temp1;
			delete[] temp2; 
			break;
		}
	
	}
	
}



void timSort(int* mas, int sizeMas) {
	stack<pair<int, int>> stackForMerge;
	int startPoint = 0;
	int finishPoint = 0;
	int count = 0;
	int minRun = getMinrun(sizeMas);
	bool endPoint = false;
	while (!endPoint) {

		endPoint = timSortFinishPoint(mas, sizeMas, startPoint, finishPoint);

		
		if (mas[startPoint] > mas[finishPoint - 1]) {
			reverseMas(mas, startPoint, finishPoint);
		}

		if ((finishPoint - startPoint) < minRun) {
			if (finishPoint + minRun > sizeMas) {
				finishPoint = sizeMas;
			}
			else {
				finishPoint += minRun-(finishPoint-startPoint);
			}
			
		}
		
		insertionSort(mas, sizeMas, startPoint, finishPoint);

		stackForMerge.push({ startPoint, finishPoint});

		
		while (stackForMerge.size() >= 3) {
			if (startPoint == sizeMas) {
				return;
			}
			pair<int, int> x = stackForMerge.top();
			stackForMerge.pop();
			pair<int, int> y = stackForMerge.top();
			stackForMerge.pop();
			pair<int, int> z = stackForMerge.top();
			stackForMerge.pop();
			if (x.second - x.first >= y.second - y.first + z.second-z.first && y.second-y.first >= z.second-z.first) {
			
				merge(mas, sizeMas, y.first, y.second, x.first, x.second);
			
				stackForMerge.push({ z.first, z.second });
				stackForMerge.push({ y.first, x.second });
				
			}
			else if (x.second-x.first >= z.second-z.first) {
				
					merge(mas, sizeMas, z.first, z.second, y.first, y.second);
				
				stackForMerge.push({z.first, y.second});
				stackForMerge.push({ x.first, x.second });
			}
			else {
			
				merge(mas, sizeMas, y.first, y.second, x.first, x.second);
				
				stackForMerge.push({ z.first, z.second });
				stackForMerge.push({ y.first, x.second });
			}
		}
		

		startPoint = finishPoint;
		

		if (stackForMerge.size() < 3 && startPoint == sizeMas) {
			pair<int, int> x = stackForMerge.top();
			stackForMerge.pop();
			pair<int, int> y = stackForMerge.top();
			stackForMerge.pop();
		
			merge(mas, sizeMas, y.first, y.second, x.first, x.second);
		
			return;
		}
		
	
	}
	
}














int main()
{
	
	int size = 10000;
	int* mas = new int[size];

	for (int i = 0; i < size; i++) {
		mas[i] = rand() % 100 + 1;
	}

	
	timSort(mas, size);


	for (int i = 1; i < size; i++) {
		if (mas[i] < mas[i - 1]) {
			system("pause");
		}
	}


	delete[] mas;


	


	
	

return 0;
}
