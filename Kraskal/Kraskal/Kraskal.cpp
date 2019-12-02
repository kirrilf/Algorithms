// Kraskal.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <sstream>

//a e 1 a b 3 e b 4 e c 6 b c 5 e p 7 c p 2
//a d 5 a b 7 d b 9 b c 8 b e 7 c e 5 d e 15 d f 6 f e 8 f g 11 e g 9


using namespace std;

struct node {
	int weight;
	string firstNode;
	string secondNode;
};

bool find(vector<string>tree,  string node) {
	
	for (auto now : tree) {
		if (now == node)
			return true;
	}
	return false;
}

void quickSortForGraf(vector<node> &graf, int first, int last)
{
	if (first < last)
	{
		int left = first, right = last, middle = graf[(left + right) / 2].weight;
		do
		{
			while (graf[left].weight < middle) left++;
			while (graf[right].weight > middle) right--;
			if (left <= right)
			{
				node tmp = graf[left];
				graf[left] = graf[right];
				graf[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);
		quickSortForGraf(graf, first, right);
		quickSortForGraf(graf, left, last);
	}

	
}

int num(string str) {
	int res = 0;
	for (char i : str) {
		res *= 10;
		res += int(i) - 48;
	}
	return res;
}

void input(vector <node> &graf) {
	string str;
	getline(cin, str);
	istringstream input(str);
	vector<string> result;
	
	// extract substrings one-by-one
	while (!input.eof()) {
		std::string substring;
		input >> substring;
		result.push_back(substring);
	}

	int cop = 0;
	node temp;
	for (auto now : result) {
		if (cop == 0) {
			temp.firstNode = now;
		}
		else if (cop == 1) {
			temp.secondNode = now;
		}
		else if (cop == 2) {
			temp.weight = num(now);

		}
		cop++;
		if (cop > 2) {
			cop = 0;
			graf.push_back(temp);
		}
	}
	
	
}

int cycleCheck(vector<node> graf, vector<vector<string>> tree, node rib) {
	for (int i = 0; i < tree.size(); i++) {

		if (find(tree[i], rib.firstNode) && find(tree[i], rib.secondNode))
			return -1;
	}

	

	for (int i = 0; i < tree.size(); i++) {
		if (find(tree[i], rib.firstNode) || find(tree[i], rib.secondNode))
			return i;
	}


	return -2;
	
}


void add(vector<vector<string>> &tree, int first, int second) {
	for (int i = 0; i < tree[second].size(); i++) {
		tree[first].push_back(tree[second][i]);
	}
	tree[second].clear();
}

void cheak(vector<vector<string>> &tree) {
	map<int, int> addNumbers;
	for (int i = 0; i < tree.size(); i++) {
		for (int j = i+1; j < tree.size(); j++) {
			for (int k = 0; k < tree[j].size(); k++) {
				if (find(tree[i], tree[j][k])) {
					addNumbers.insert(make_pair(i, j));
				}
			}
		}
	}

	cout << "set" << endl;
	for (auto now : addNumbers) {
		cout << now.first  << " " << now.second << endl;
		add(tree, now.first, now.second);
	}
	cout << endl << endl;
	
}

void alg(vector<node> graf) {
	//vector<node> tree = {};
	
	vector<vector<string>> tree;
	int cou = 0, numberInSetOfConnectedEdges = 0;
	for (int i = 0; i < graf.size(); i++) {
		numberInSetOfConnectedEdges = cycleCheck(graf, tree, graf[i]);
		if (numberInSetOfConnectedEdges == -2) {
			vector<string> temp;
			temp.push_back(graf[i].firstNode);
			temp.push_back(graf[i].secondNode);
			tree.push_back(temp);
		}
		else if (numberInSetOfConnectedEdges == -1) {
			continue;
		}
		else {
			tree[numberInSetOfConnectedEdges].push_back(graf[i].firstNode);
			tree[numberInSetOfConnectedEdges].push_back(graf[i].secondNode);
			cheak(tree);
		}
	}

	cout << endl;
	
	int mas=0;
		for (int j = 0; j < tree[0].size()-1; j+=2) {
			//cout << tree[0][j] << " " << tree[0][j+1] << endl;
			for (auto now : graf) {
				if ((now.firstNode == tree[0][j] && now.secondNode == tree[0][j + 1]) || (now.firstNode == tree[0][j+1] && now.secondNode == tree[0][j])) {
					cout << now.firstNode << " " <<  now.secondNode << endl;
					mas += now.weight;
				}
			}
		}
		cout << mas;
		cout << endl;
	
	
	

}



int main()
{
	vector<node> graf = {};
	input(graf);
	for (auto now : graf) {
		cout << now.firstNode << " " << now.secondNode << " " << now.weight << endl;
	}

	quickSortForGraf(graf, 0, graf.size() - 1);

	cout << endl;

	for (auto now : graf) {
		cout << now.firstNode << " " << now.secondNode << " " << now.weight << endl;
	}

	
	alg(graf);


	return 0;
}
