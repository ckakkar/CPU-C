#include <iostream>
#include <deque>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

const int FETCH_WIDTH=1;
const int ISSUE_WIDTH=1;
const int COMMIT_WIDTH=1;
bool debug=false;

int bin2dec(const string& s)
{
    int sum=0,power=0;
    for(int i=s.length()-1;i>=0;i--)
    {
        if(s[i]=='1')
            sum+=pow(2,power);
        power++;
    }
    return sum;
}

class memory
{
private:
    void readFile(ifstream& fin);
protected:
    vector<unsigned int> PC;
public:
    memory();
    memory(ifstream& f);
};