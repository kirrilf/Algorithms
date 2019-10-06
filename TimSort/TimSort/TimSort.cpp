#include <iostream>

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
	for (int i = startPoint+1; i < finishPoint; i++)
		for (int j = i; j > startPoint; j--)
			if (mas[j - 1] > mas[j])
				swap(mas[j - 1], mas[j]);
}

void reverseMas(int* mas, int startPoint, int finishPoint) {
	for (int i = 0; i < (finishPoint-startPoint)/2; i++) {
		swap(mas[startPoint+i], mas[finishPoint - 1 - i]);
	}

}

bool findingAnOrderedArrayFinishPoint(int* mas, int sizeMas, int startPoint, int &finishPoint) {
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

void findingAnOrderedArray(int* mas, int sizeMas) {
	int startPoint = 0;
	int finishPoint = 0;
	//int minRun = getMinrun(sizeMas);
	int minRun = 5;
	bool endPoint = false;
	while (!endPoint) {

		endPoint = findingAnOrderedArrayFinishPoint(mas, sizeMas, startPoint, finishPoint);

		
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
		
		/*
		for (int i = startPoint; i < finishPoint; i++) {
			cout << mas[i] << " ";
		}
		cout << "      " << startPoint << " " << finishPoint << endl;
		*/


		insertionSort(mas, sizeMas, startPoint, finishPoint);


		




		/*
		for (int i = startPoint; i < finishPoint; i++) {
			cout << mas[i] << " ";
		}
		cout << "      " << startPoint << " " << finishPoint << endl;
		*/


		startPoint = finishPoint;
	

	
		
	
	}

}






void timSort(int *mas, int sizeMas) {
	findingAnOrderedArray(mas, sizeMas);

	

}



int main()
{
	int mas[21] = { 1, 2, 3, 9, 11, 50, 199, 10, 465, 63, 7, 12, 13, 9, 4, 3, 2, -1, -5, 15, 14};
	timSort(mas, 21);
	/*for (int i = 0; i < 11; i++) {
		cout << mas[i] << endl;
	}*/


	return 0;
}
