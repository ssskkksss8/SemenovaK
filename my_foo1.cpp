#include <string>
using namespace std;

string foo(string stroka){
    string stroka2 = "";
    int lenst = stroka.length();
    for (int i = 0; i < lenst; ++i){
        if (stroka[i] == 'a'){
            stroka2 += 'b';
        }
        else if (stroka[i] == 'b'){
            stroka2 += 'a';
        }
        else if (stroka[i] == 'c'){
            stroka2 += 'c';
        } 
        else{
            stroka2 = "invalid input data";
            break;
        }     
    }
    return stroka2;
}