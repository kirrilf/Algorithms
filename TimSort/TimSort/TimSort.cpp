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
				insertionSort(mas, sizeMas, startPoint, finishPoint);
			}
			else {
				finishPoint += minRun-(finishPoint-startPoint);
				insertionSort(mas, sizeMas, startPoint, finishPoint);
			}
			
		}
		
		

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




void tests() {

	int size1 = 1000;
	int size2 = 100000;
	int size3 = 1000000;
	int* mas1 = new int[size1];
	int* mas2 = new int[size2];
	int* mas3 = new int[size3];
	for (int i = 0; i < size1; i++) {
		mas1[i] = (rand() % 20000) - 10000;
	}
	for (int i = 0; i < size2; i++) {
		mas2[i] = (rand() % 20000) - 10000;
	}
	for (int i = 0; i < size3; i++) {
		mas3[i] = (rand() % 20000) - 10000;
	}

	int start = clock();
	timSort(mas1, size1);
	int end = clock();
	for (int i = 1; i < size1; i++) {
		if (mas1[i] < mas1[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout << "Time for 1000 random elements: " <<end - start << endl;
	


	start = clock();
	timSort(mas2, size2);
	end = clock();
	for (int i = 1; i < size2; i++) {
		if (mas2[i] < mas2[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout <<"Time for 100k random elements: " <<  end - start << endl;

	start = clock();
	timSort(mas3, size3);
	end = clock();
	for (int i = 1; i < size3; i++) {
		if (mas3[i] < mas3[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout << "Time for 1M random elements: " << end - start << endl;

	for (int i = 0; i < size1; i++) {
		if (i < 100) {
			mas1[i] = i;
		}
		else if (i < 200) {
			mas1[i] = i - 100;
		}
		else if (i < 300) {
			mas1[i] = rand() % 100 + 1;
		}
		else if (i < 400) {
			mas1[i] = i;
		}
		else if (i < 500) {
			mas1[i] = i - 54;
		}
		else if (i < 600) {
			mas1[i] = i;
		}
		else if (i < 700) {
			mas1[i] = rand() % 10 + 1;
		}
		else if (i < 800) {
			mas1[i] = i - 1000;
		}
		else if (i < 900) {
			mas1[i] = i;
		}
		else if (i < 1000) {
			mas1[i] = i - 20000;
		}
	}

	for (int i = 0; i < size2; i++) {
		if (i < 10000) {
			mas2[i] = i;
		}
		else if (i < 20000) {
			mas2[i] = i - 100;
		}
		else if (i < 30000) {
			mas2[i] = rand() % 100 + 1;
		}
		else if (i < 40000) {
			mas2[i] = i;
		}
		else if (i < 50000) {
			mas2[i] = i - 54;
		}
		else if (i < 60000) {
			mas2[i] = i;
		}
		else if (i < 70000) {
			mas2[i] = rand() % 10 + 1;
		}
		else if (i < 80000) {
			mas2[i] = i - 1000;
		}
		else if (i < 90000) {
			mas2[i] = i;
		}
		else if (i < 100000) {
			mas2[i] = i - 20000;
		}
	}

	for (int i = 0; i < size3; i++) {
		if (i < 100000) {
			mas3[i] = i;
		}
		else if (i < 200000) {
			mas3[i] = i - 100;
		}
		else if (i < 300000) {
			mas3[i] = rand() % 100 + 1;
		}
		else if (i < 400000) {
			mas3[i] = i;
		}
		else if (i < 500000) {
			mas3[i] = i - 54;
		}
		else if (i < 600000) {
			mas3[i] = i;
		}
		else if (i < 700000) {
			mas3[i] = rand() % 10 + 1;
		}
		else if (i < 800000) {
			mas3[i] = i - 1000;
		}
		else if (i < 900000) {
			mas3[i] = i;
		}
		else if (i < 1000000) {
			mas3[i] = i - 20000;
		}
	}

	start = clock();
	timSort(mas1, size1);
	end = clock();
	for (int i = 1; i < size1; i++) {
		if (mas1[i] < mas1[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout << "Time for 1000 elements: " << end - start << endl;

	start = clock();
	timSort(mas2, size2);
	end = clock();
	for (int i = 1; i < size2; i++) {
		if (mas2[i] < mas2[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout << "Time for 100k elements: " << end - start << endl;

	start = clock();
	timSort(mas3, size3);
	end = clock();
	for (int i = 1; i < size3; i++) {
		if (mas3[i] < mas3[i - 1]) {
			cout << "ERROR";
			system("pause");
		}
	}
	cout << "Time for 1M elements: " << end - start << endl;


	

	delete[] mas1;
	delete[] mas2;
	delete[] mas3;
	
}


	






int main()
{

	tests();

	


	
	

return 0;
}
