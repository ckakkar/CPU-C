#include "RegFile.h"

RegFile::RegFile()
{
    for(int i=0;i<16;i++)
    {
        r[i].value=0;
        r[i].signal=true;
    }
}
RegFile::~RegFile()
{
    delete[] r;
}
void RegFile::setVal(const int& val,const int& pos)
{
    r[pos].value=val;
    r[pos].signal=true;
}
rgster& RegFile::operator[](const int& index) const
{
    if(r[index].signal)
    {
        return r[index];
    }
    else
    {
        cerr<<"\n\nvalue not ready!!"<<endl;
        abort();
    }
}