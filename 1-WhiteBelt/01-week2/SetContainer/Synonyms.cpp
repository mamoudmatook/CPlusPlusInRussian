#include <iostream>
#include <map>
#include <string>
#include <set>
using namespace std;
int main()
{
    int n;
    cin >> n;
    map<string,set<string>> synonyms;
    for (int i = 0; i < n; i++)
    {
       string command;
       cin >> command;
       if (command == "ADD")
       {
           string w1, w2;
           cin >> w1 >> w2;
           if(synonyms.find(w1) != synonyms.end())
           {
              synonyms[w1].insert(w2); 
           }
           else
           {
               set<string> tmp;
               tmp.insert(w2);
               synonyms[w1] = tmp;
           }
           if(synonyms.find(w2) != synonyms.end())
           {
              synonyms[w2].insert(w1); 
           }
           else
           {
               set<string> tmp;
               tmp.insert(w1);
               synonyms[w2] = tmp;
           }
       }
       else if (command == "COUNT")
       {
           string w;
           cin >> w;
           if(synonyms.find(w) == synonyms.end())
           {
               cout << "0" << endl;
           }
           else
           {
               cout << synonyms[w].size() << endl;
           }
       }
       else
       {
            string w1, w2;
            cin >> w1 >> w2;    
            if (synonyms.find(w1) != synonyms.end())
            {
                if(synonyms[w1].count(w2))
                {
                    cout << "YES" << endl;
                }
                else
                {
                    cout << "NO" << endl;
                }
            }
            else
            {
                cout << "NO" << endl;
            }
       }
    }
    return 0;
}
