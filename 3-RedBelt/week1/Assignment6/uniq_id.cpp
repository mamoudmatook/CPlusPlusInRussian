#include <string>
#include <vector>
using namespace std; 
#define macro_line(line) var ## _ ## line
#define macro_name(line)  macro_line(line) 
#define UNIQ_ID macro_name(__LINE__) 

int main()
{
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}