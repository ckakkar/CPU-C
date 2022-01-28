#include "pipeline.cpp"

int main(int argc,char* argv[])
{
    if(argc>1)
    {
        string s=argv[argc-1];
        if(s=="debug")
            ::debug=true;
    }
    menu();
    return 0;
}