#ifndef UTILS_HPP
#define UTILS_HPP

#include<iostream>
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

#endif // UTILS_HPP
