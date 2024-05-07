#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

inline string getwithoutextension(char* filePath) {
    string path(filePath), ret="";
    int dotPos = -1;
    for(int i=path.length()-1;i>-1;i--) {
        if(path[i]=='.') { dotPos = i; break; }
    }
    if(dotPos > 0) ret = path.substr(0, dotPos);
    else ret = path;
    return ret;
}

inline string dquote_to_html(string s) {
    string temp = "";
    for(int i=0;i<s.size();i++) {
        if(s[i]=='"') temp = temp + "&quot;";
        else temp = temp + s[i]; 
    }
    return temp;
}

inline char* str_to_char(string s) {
    char *res = const_cast<char*> (s.c_str());
    return res;
}

inline vector<string> convertToWords(string line) {
    istringstream iss(line);
    vector<string> words;    
    string word;
    while(iss >> word) words.push_back(word);    
    return words;
}

inline string ret_line(string code, int i) {
    string ans = "";
    for(int j=i;j<code.length();j++) {
        if(code[j] == '\n') break;
        ans = ans + code[j];
    }
    return ans;
}

inline char* getFileName(char* filePath) {
    char* lastSlash = strrchr(filePath, '/');
    if (lastSlash != NULL) {
        // Move the pointer past the last slash
        filePath = lastSlash + 1;
    }
    // Copy the filename to a new buffer
    char* fileName = new char[strlen(filePath) + 1];
    strcpy(fileName, filePath);
    return fileName;
}

inline string readFromFile(const char* filePath) {
    ifstream file(filePath);
    string content;
    if (file.is_open()) {
        // Read the file line by line and append to content
        string line;
        while (getline(file, line)) {
            content += line + "\n"; // Adding newline character for each line
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filePath << endl;
    }
    return content;
}

inline bool isArray(string varName) {
    int pos = varName.find('[');
    if(pos != string::npos) return true;
    else return false;
}

inline string getArrayIdx(string varName) {
    int pos = varName.find('[');
    string idxName = varName.substr(pos+1);
    idxName.pop_back();
    return idxName;
}

inline string getArrayBase(string varName) {
    int pos = varName.find('[');
    string idxName = varName.substr(0,pos);
    return idxName;
}

#endif // UTILS_HPP
