#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

using namespace std;

vector<string> delimRemove(vector<string> &v, char delimiter)
{
	vector<string> tempVec;

	for (int i = 0; i < v.size(); ++i)
	{
		string temp = v.at(i);
		string temp2;

		istringstream iss(temp);

		while (getline(iss, temp2, delimiter))
		{
			tempVec.push_back(temp2);
		}
	}

	return tempVec;
}

unordered_map<string, int> wordCount(string filename) {
	vector<string> tempVec;

	ifstream file(filename);
	string line;
	string separators = " \t,.";
	if (file.is_open()) {
		while (getline(file, line)) {
			string temp = "";
			istringstream iss(line);

			while (iss >> temp)
			{
				tempVec.push_back(temp);
			}
		}
	}

	tempVec = delimRemove(tempVec, ',');
	tempVec = delimRemove(tempVec, '.');
	tempVec = delimRemove(tempVec, ';');

	unordered_map<string, int> umap;
	
	for (int i = 0; i < tempVec.size(); ++i)
	{
		string temp = tempVec.at(i);

		++umap[temp];
	}

	return umap;
}

int main(){
    auto counts = wordCount("SampleTextFile_10kb.txt");
    for (auto i = counts.begin(); i != counts.end(); i++) {
        cout << i->first << "\t" << i->second << endl;
    }
    cout << "End of program" << endl;
	return 0;
}