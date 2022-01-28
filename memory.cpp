#include "memory.h"


memory::memory()
=default;
memory::memory(ifstream& f)
{
    this->readFile(f);
}
void memory::readFile(ifstream& fin)
{
    string uint;
    vector <string> temp;
    while(getline(fin,uint,','))
    {
        temp.push_back(uint);
    }
    for(int i=0;i<temp.size();i++)
    {
        unsigned int dig=atoi(temp[i].c_str());
        PC.push_back(dig);
    }
}