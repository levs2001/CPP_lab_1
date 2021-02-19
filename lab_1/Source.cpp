#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

class FileChanger {
public:
	FileChanger(string filename, size_t needLength) : needLength(needLength) {
		file.open(filename);
		if (!file.is_open())
			fileOk = false;
		else
			fileOk = true;
	}

	void ChangeAndPrint() {
		while (getWords()) {
			SubstrIprintStr();
			strWords.clear();
		}
	}

	~FileChanger() {
		file.close();
		strWords.clear();
	}

	bool fileOk;
private:
	string givenStr;
	vector<string> strWords;
	ifstream file;
	size_t needLength;

	bool getWords() {
		if (getline(file, givenStr)) {
			istringstream strStream(givenStr);
			copy(istream_iterator<string>(strStream), istream_iterator<string>(), back_inserter(strWords));
			return true;
		}
		return false;
	}

	void PrintStr(string str) {
		int spaces_c = (int)(needLength - str.length()) / 2;
		string strFormatted;
		strFormatted.insert(0, spaces_c, ' ');
		strFormatted.insert(strFormatted.length(), str);
		strFormatted.insert(strFormatted.length(), spaces_c, ' ');
		cout << strFormatted << endl;
	}

	void SubstrIprintStr() {
		int spaces_c = (int)(needLength - givenStr.length()) / 2;
		if (spaces_c > 0) {
			PrintStr(givenStr);
		}
		else {
			size_t length = 0;
			string str;
			for (auto& word : strWords) {
				if (word.length() > needLength) {
					int pos = 0;
					string splStr;
					do {
						splStr = givenStr.string::substr(pos, needLength);
						PrintStr(splStr);
						pos += needLength;
					} while (pos < givenStr.length());
				}
				else if (length + word.length() <= needLength) {
					str += (word + " ");
					length += (word.length() + 1);
				}
				else {
					PrintStr(str);
					str.clear();
					str += (word + " ");
					length = word.length() + 1;

				}
			}
			if (str.size() != 0) {
				PrintStr(str);
				length = 0;
				str.clear();
			}
		}
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	string filename = "..\\text.txt";
	size_t maxLength = 25;
	
	FileChanger session(filename, maxLength);
	if (session.fileOk)
		session.ChangeAndPrint();
	else
		cout << "can't open a file!" << endl;

	return 0;
}
