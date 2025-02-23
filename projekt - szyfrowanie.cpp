#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio> // remove();

using namespace std;

const int k = 7;

const string alphabetLowercase = "abcdefghijklmnopqrstuvwxyz";
const string alphabetUppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string getFileName(int type) {
    string str;
    switch (type)
    {
    case 1:
        cout << "Podaj nazwę pliku wejsciowego: ";
        break;

    case 2:
        cout << "Podaj nazwę pliku wyjsciowego: ";
        break;

    default:
        cout << "error" << endl;
        break;
    }

    cin >> str;
    str = str + ".txt";
    return str;
}

int getOffset() {
    int offset;
    cout << "Podaj przesuniecie: ";
    cin >> offset;
    return offset;
}

void display(int& whichOne, vector<string> loadStr, vector<string> writeStr, vector<string> writeStr2 = {}, bool crackMode = false) {
    int currentMaxSize;
    int input = 3;
    int previousInput = 3;
    int pages;
    float percentage;
    bool forceLast = false;
    bool forcePrev = false;

    if ((loadStr.size() % k) != 0) pages = (loadStr.size() / k) + 1;
    else pages = (loadStr.size() / k);

    if (crackMode == false) writeStr2 = writeStr;

    for (int i = 0; i < pages; ++i) {
        system("cls");

        cout << "1 - poprzednia strona\t" << "2 - następna strona\t" << "3 - plik wejsciowy";
        if (crackMode == false) cout << "\t4 - plik wyjsciowy" << endl << endl;
        else cout << endl << "4 - potencjalny 1\t" << "5 - potencjalny 2\t" << "6 - zapisz 1\t" << "7 - zapisz 2" << endl << endl;

        switch (input)
        {

        case 1:
            if (i > 1) {
                if (forcePrev == false) i = i - 2;
                else i = i - 1;
            }
            input = 3;

        case 2:
            ++i;

        case 3:
            if (i != 0) --i;
            if (forceLast == true) ++i;
            if (i == (pages - 1)) {
                for (int j = 0; j < loadStr.size() % k; ++j) {
                    cout << loadStr[k * i + j] << endl;
                    if (j == k - 1) currentMaxSize = j;
                }
            }
            else {
                for (int j = 0; j < k; ++j) {
                    cout << loadStr[k * i + j] << endl;
                    if (j == k - 1) currentMaxSize = j;
                }
            }
            break;

        case 4:
            if (i != 0) --i;
            if (forceLast == true) ++i;
            if (i == (pages - 1) && writeStr.size() % k != 0) {
                for (int j = 0; j < writeStr.size() % k; ++j) {
                    cout << writeStr[k * i + j] << endl;
                    if (j == k - 1) currentMaxSize = j;
                }
            }
            else {
                for (int j = 0; j < k; ++j) {
                    cout << writeStr[k * i + j] << endl;
                    if (j == k - 1) currentMaxSize = j;
                }
            }
            break;

        case 5:
            if (crackMode == true) {
                if (i != 0) --i;
                if (forceLast == true) ++i;
                if (i == (pages - 1) && writeStr2.size() % k != 0) {
                    for (int j = 0; j < writeStr2.size() % k; ++j) {
                        cout << writeStr2[k * i + j] << endl;
                        if (j == k - 1) currentMaxSize = j;
                    }
                }
                else {
                    for (int j = 0; j < k; ++j) {
                        cout << writeStr2[k * i + j] << endl;
                        if (j == k - 1) currentMaxSize = j;
                    }
                }
            }
            break;

        case 6:
            if (crackMode == true) {
                whichOne = 1;
                break;
            }

        case 7:
            if (crackMode == true) {
                whichOne = 2;
                break;

            }

        default:
            break;
        }

        forceLast = false;
        forcePrev = false;
        percentage = 100 - ((float)(k * i + currentMaxSize) / (float)loadStr.size()) * 100;

        cout << endl << endl << "Pozostalo ";
        if (i != (pages - 1)) cout << (loadStr.size() - (k * i + currentMaxSize)) << " (" << percentage << " %)";
        else cout << "0 (0%)";
        cout << " wierszy" << endl;

        cin >> input;
        if (i == (pages - 1) && (input == 3 || input == 4)) {
            i = i - 1;
            forceLast = true;
        }
        else if (i == (pages - 1) && input == 1) {
            i = i - 1;
            forcePrev = true;
        }
        else if (i == (pages - 1) && input == 2) cout << endl << "Koniec tekstu - wychodze z programu" << endl;

    }

}

void caesarCrack(string importString, int& offsetA, int& offsetE) {
    int counter[26] = { 0 };
    int pos = 0;
    int max = 0;

    for (int i = 0; i < importString.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (importString[i] == alphabetLowercase[j] || importString[i] == alphabetUppercase[j]) counter[j]++;
        }
    }

    for (int i = 0; i < 26; ++i) {
        if (counter[i] > max) {
            pos = i;
            max = counter[i];
            /**
            cout << "POS = " << pos << endl;
            cout << "i = " << i << endl;
            cout << "counter[i] == " << counter[i] << endl << endl << endl;
            */
        }
    }

    offsetA = pos;
    if (pos < 4) offsetE = 22 + pos;
    else offsetE = pos - 4;

    /*/
    cout << endl << endl;
    cout << "OFFSET A = " << offsetA << endl << endl;
    cout << "OFFSET E = " << offsetE << endl << endl;
    system("pause");
    */
}

void caesarDecryptedCode(string& lwrcs, string& uprcs, int offset = 0, bool encrypt = false) {
    lwrcs = alphabetLowercase;
    uprcs = alphabetUppercase;

    string lowerCopy = lwrcs;
    string upperCopy = uprcs;

    string endStrLower = "";
    string endStrUpper = "";


    if (encrypt == true) {
        for (int i = 0; i < 26; ++i) {
            lwrcs[i] = (lowerCopy[(i + offset) % 26]);
            uprcs[i] = (upperCopy[(i + offset) % 26]);
        }
    }

    else {
        for (int i = 0; i < offset; ++i) {
            endStrLower = lowerCopy[lowerCopy.size() - 1] + endStrLower;
            endStrUpper = upperCopy[upperCopy.size() - 1] + endStrUpper;

            lwrcs.pop_back();
            uprcs.pop_back();

            lowerCopy = endStrLower + lwrcs;
            upperCopy = endStrUpper + uprcs;

        }
        lwrcs = lowerCopy;
        uprcs = upperCopy;
    }

    /**
    cout << lwrcs.size();

    cout << endl << "lowercase: " << endl;
    for (int i = 0; i < lwrcs.size(); ++i) {
        cout << lwrcs[i] << " ";
    }
    cout << "|" << endl << endl;

    cout << endl << "uppercase: " << endl;
    for (int i = 0; i < uprcs.size(); ++i) {
        cout << uprcs[i] << " ";
    }
    cout << "|" << endl << endl;

    system("pause");
    */
}

void encrypt() {
    int useless;
    vector<string> loadString;
    vector<string> writeString;

    ifstream load;
    ofstream write;

    string file_load;
    string file_write;
    int offset;

    string temp;

    file_load = getFileName(1);
    file_write = getFileName(2);
    offset = getOffset();

    load.open(file_load);
    write.open(file_write);

    string importString;

    while (!load.eof()) {
        getline(load, temp);
        loadString.push_back(temp);
        importString += temp + "\n";
    }

    load.close();

    string uppercase;
    string lowercase;

    caesarDecryptedCode(lowercase, uppercase, offset, true);

    bool foundLetter = false;

    for (int i = 0; i < importString.size(); ++i) {
        foundLetter = false;

        while (foundLetter == false) {

            for (int chk = 0; chk < 26; ++chk) {

                if (alphabetLowercase[chk] == importString[i] && foundLetter == false) {
                    importString[i] = lowercase[chk];
                    foundLetter = true;
                }

                else if (alphabetUppercase[chk] == importString[i] && foundLetter == false) {
                    importString[i] = uppercase[chk];
                    foundLetter = true;
                }

                else if (chk == 25) foundLetter = true;
            }
        }
    }

    write << importString;
    write.close();

    load.open(file_write);
    while (!load.eof()) {
        getline(load, temp);
        writeString.push_back(temp);
    }
    load.close();

    display(useless, loadString, writeString);


}



void decrypt(bool crack = false) {
    int whichOne;
    vector<string> loadString;
    vector<string> writeString;

    ifstream load;
    ofstream write;

    string file_load;
    string file_write;
    int offset;

    string temp;

    file_load = getFileName(1);
    file_write = getFileName(2);
    if (crack == false) offset = getOffset();

    load.open(file_load);

    string importString;

    while (!load.eof()) {
        getline(load, temp);
        loadString.push_back(temp);
        importString += temp + "\n";
    }

    load.close();



    if (crack == true) {
        int offsetA = 0;
        int offsetE = 0;
        string uppercaseA;
        string lowercaseA;
        string uppercaseE;
        string lowercaseE;

        vector<string> writeStringA;
        vector<string> writeStringE;

        caesarCrack(importString, offsetA, offsetE);
        string importString2 = importString;

        // cout << "DECRYPT" << endl << "offset: " << endl << "a:" << offsetA << endl << "e:" << offsetE << endl << endl;

        caesarDecryptedCode(lowercaseA, uppercaseA, offsetA, false);
        caesarDecryptedCode(lowercaseE, uppercaseE, offsetE, false);

        bool foundLetter = false;

        for (int i = 0; i < importString.size(); ++i) {
            foundLetter = false;

            while (foundLetter == false) {

                for (int chk = 0; chk < 26; ++chk) {

                    if (alphabetLowercase[chk] == importString[i] && foundLetter == false) {
                        importString[i] = lowercaseA[chk];
                        foundLetter = true;
                    }

                    else if (alphabetUppercase[chk] == importString[i] && foundLetter == false) {
                        importString[i] = uppercaseA[chk];
                        foundLetter = true;
                    }

                    else if (chk == 25) foundLetter = true;
                }
            }
        }

        write.open("type1.txt");
        write << importString;
        write.close();

        load.open("type1.txt");
        while (!load.eof()) {
            getline(load, temp);
            writeStringA.push_back(temp);
        }
        load.close();

        for (int i = 0; i < importString2.size(); ++i) {
            foundLetter = false;

            while (foundLetter == false) {

                for (int chk = 0; chk < 26; ++chk) {

                    if (alphabetLowercase[chk] == importString2[i] && foundLetter == false) {
                        importString2[i] = lowercaseE[chk];
                        foundLetter = true;
                    }

                    else if (alphabetUppercase[chk] == importString2[i] && foundLetter == false) {
                        importString2[i] = uppercaseE[chk];
                        foundLetter = true;
                    }

                    else if (chk == 25) foundLetter = true;
                }
            }
        }

        write.open("type2.txt");
        write << importString2;
        write.close();

        load.open("type2.txt");
        while (!load.eof()) {
            getline(load, temp);
            writeStringE.push_back(temp);
        }
        load.close();

        display(whichOne, loadString, writeStringA, writeStringE, true);

        write.open(file_write);
        if (whichOne == 1) write << importString;
        else if (whichOne == 2) write << importString2;
        write.close();

        remove("type1.txt");
        remove("type2.txt");
    }
    else {
        write.open(file_write);
        string uppercase;
        string lowercase;
        caesarDecryptedCode(lowercase, uppercase, offset, false);

        bool foundLetter = false;

        for (int i = 0; i < importString.size(); ++i) {
            foundLetter = false;

            while (foundLetter == false) {

                for (int chk = 0; chk < 26; ++chk) {

                    if (alphabetLowercase[chk] == importString[i] && foundLetter == false) {
                        importString[i] = lowercase[chk];
                        foundLetter = true;
                    }

                    else if (alphabetUppercase[chk] == importString[i] && foundLetter == false) {
                        importString[i] = uppercase[chk];
                        foundLetter = true;
                    }

                    else if (chk == 25) foundLetter = true;
                }
            }
        }

        write << importString;
        write.close();

        load.open(file_write);
        while (!load.eof()) {
            getline(load, temp);
            writeString.push_back(temp);
        }
        load.close();

        display(whichOne, loadString, writeString);
    }

}

void initialize() {
    int choice = 0;
    cout << "Wybierz metodę szyfrowania" << endl;

    do {
        cout << "1 - cezar" << endl << endl << "Wybor: ";
        cin >> choice;
        cout << endl << endl;
    } while (choice != 1);

    choice = 0;

    do
    {
        cout << "1 - szyfrowanie" << endl << "2 - deszyfrowanie" << endl << "3 - lamanie szyfru" << endl << endl << "Wybor: ";
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);

    cout << endl << endl << "Prosze podawac nazwy plikow bez uwzgledniania rozszerzenia .txt w nazwie" << endl << endl;

    if (choice == 1) encrypt();
    else if (choice == 2) decrypt();
    else if (choice == 3) decrypt(true);
    else {
        cout << "Nie wybrano poprawnej opcji - wychodze z programu";
    }
}

int main()
{
    initialize();
}