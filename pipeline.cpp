#include "pipeline.h"


pipeline::pipeline()
=default;
pipeline::pipeline(ifstream& f)
{
    jmp=0;
    instruction j(f);
    label:
    count+=FETCH_WIDTH;
    if(::debug)
    {
        cout<<"\n\n---------- Fetch -----------------"<<endl;
        cout<<"instruction->"<<j.getInstruct(count)<<endl;
    }
    updateInst(j,count);
    this->fetch();
    if(count<j.instNum())
        goto label;
    showStats();
}
void pipeline::fetch()
{
    time(&start);
    ios_base::sync_with_stdio(false);

    for(int i=0;i<IQ.size();i++)
    {
        ReorderBuffer f;
        f.ID=fatherCounter;
        f.type=IQ[i].type;
        f.OP=IQ[i].OP;
        f.s1=IQ[i].s1,f.s2=IQ[i].s1;
        f.destination=IQ[i].destination;
        ROB.push_back(f);
        fatherCounter++;
    }
    if(::debug)
    {
        cout<<"\n\n---------- instruction Queue -----------------"<<endl;
        cout<<"Dest\t"<<"V1\t"<<"Src1\t"<<"V2\t"<<"Src2\t"<<"type\n";
        for(int i=0;i<IQ.size();i++)
        {
            cout<<IQ[i].destination<<"\t"<<IQ[i].v1<<"\t"<<IQ[i].s1<<"\t"<<IQ[i].v2<<"\t"<<IQ[i].s2<<"\t"<<IQ[i].type<<endl;
        }
    }
    this->execute();
}
void pipeline::execute()
{
    if(IQ.size()<ISSUE_WIDTH)
        return;
    if(::debug)
    {
        cout<<"\n\n---------- execute -----------------"<<endl;
        for(int i=0;i<IQ.size();i++)
        {
            cout<<"checking status src1 R"<<IQ[i].s1<<", V="<<IQ[i].v1<<" checking status src2 R"<<IQ[i].s1<<", V="<<IQ[i].v1<<endl;
        }
    }
    for(int i=0;i<IQ.size();i++)
    {
        if(IQ[i].type=="00")
        {
            ALU a(IQ[i].OP,IQ[i].s1,IQ[i].s2);
            int res=a.getResult();
            r.setVal(res,IQ[i].destination);
        }
        else if(IQ[i].type=="01")
        {
            /*if(IQ[i].OP=="0101")
            {
                int comp1=r[IQ[i].destination].value;
                int comp2=r[IQ[i].s1].value;
                jmp=r[IQ[i].s2].value;
                if(comp1==comp2)
                {
                    IQ.clear();
                    ROB.clear();
                    count=jmp-FETCH_WIDTH;
                    fatherCounter=jmp;
                    return;
                }
                else
                {
                    jmp=0;
                }
            }
            else if(IQ[i].OP=="0110")
            {
                int comp1=r[IQ[i].destination].value;
                int comp2=r[IQ[i].s1].value;
                jmp=r[IQ[i].s2].value;
                if(comp1!=comp2)
                {
                    IQ.clear();
                    ROB.clear();
                    count=jmp-FETCH_WIDTH;
                    fatherCounter=jmp;
                    return;
                }
                else
                {
                    jmp=0;
                }
            }
            else
            {*/
                ALU a(IQ[i].OP,IQ[i].s1,IQ[i].s2);
                int res=a.getResult();
                r.setVal(res,IQ[i].destination);
            //}
        }
        else if(IQ[i].type=="11")
        {

            string bien;
            cout<<"\n\nP-type encountered, Enter a value: ";
            bab:
            cin>>bien;
            for(int i=0;i<bien.length();i++)
            {
                if((+bien[i]<48 || +bien[i]>57))
                {
                    cerr<<"\n\nPlease enter digits only: ";
                    goto bab;
                }
            }
            int n=stoi(bien);
            r.setVal(n,IQ[i].destination);
        }
        if(IQ[i].type=="10")
        {
            count=IQ[i].destination;
            break;
        }
        IQ[i].done=true;

    }
    this->commit();
}
void pipeline::commit()
{
    if(::debug)
        cout<<"\n\n---------- Commit -----------------"<<endl;
    if(IQ.size()<COMMIT_WIDTH)
        return;
    int ss=ROB.size();
    for(int i=0;i<ss;i++)
    {
        if(IQ[i].ROB_ID!=ROB[i].ID)
        {
            cerr<<"\n\nyou messed up";
            abort();
        }
    }
    for(int i=0;i<ss;i++)
    {
        if(IQ[i].done)
        {
            if(::debug)
                cout<<"committing ROB ID "<<IQ[i].ROB_ID;
            ROB.pop_front();
        }
    }
    for(int i=0;i<ss;i++)
    {
        IQ.pop_front();
    }
    stat.updateCLK();
    stat.updateThroughput(ISSUE_WIDTH);
    time(&end);
    double timeTaken=double(end-start);
    stat.updateLatency(timeTaken);
}
void pipeline::updateInst(instruction& t,const int& ind)
{
    for(int i=ind;i<FETCH_WIDTH+ind;i++)
    {
        dab temp;
        temp.type=t.getType(i);

        if(temp.type=="00")
        {
            temp.OP=t.getOpcode(i);
            int source1=bin2dec(t.getSrc1(i));
            temp.s1=r[source1].value;
            temp.v1=r[bin2dec(t.getSrc1(i))].signal;
            int source2=bin2dec(t.getSrc2(i));
            temp.s2=r[source2].value;
            temp.v2=r[bin2dec(t.getSrc2(i))].signal;
            temp.destination=bin2dec(t.getDest(i));
        }
        else if(temp.type=="01")
        {
            temp.OP=t.getOpcode(i);
            int source1=bin2dec(t.getSrc1(i));
            temp.s1=r[source1].value;
            temp.v1=r[bin2dec(t.getSrc1(i))].signal;
            temp.s2=bin2dec(t.getImme(i));
            temp.v2=true;
            temp.destination=bin2dec(t.getDest(i));
        }
        else if(temp.type=="10")
        {
            temp.destination=bin2dec(t.getImme(i));
        }
        else if(temp.type=="11")
        {
            temp.OP=t.getOpcode(i);
            temp.destination=bin2dec(t.getDest(i));
            if(temp.destination!=2)
            {
                cerr<<"\n\nP-type error"<<endl;
                abort();
            }
        }
        temp.done=false;
        temp.ROB_ID=i;
        IQ.push_back(temp);
    }
}
void pipeline::showStats()
{
    stat.print_stats();
}
void menu()
{
    char num;
    cout<<">>>>>>>>>>CPU-Simulator<<<<<<<<<<<";
    label:
    cout<<"\n\n\n\n";
    cout<<"What program would you like to run today: \n"<<endl;
    cout<<"1) Factorial"<<endl;
    cout<<"2) Fibonacci"<<endl;
    cout<<"3) Inst_mem"<<endl;
    cout<<"4) add2Num"<<endl;
    cout<<"5) Exit"<<endl<<endl;

    cout<<"Select the number: ";
    cin>>num;
    cin.ignore();
    if(+num!=49 && +num!=50 && +num!=51 && +num!=52 && +num!=53)
    {
        cerr<<"Please, select from the given options only!"<<endl;
        goto label;
    }
    switch(+num)
    {
        case 49:
        {
            ifstream finA("factorial.csv");
            if(finA.fail())
            {
                cerr<<"\nError while opening the Factorial program file."<<endl;
                goto label;
            }
            cout<<"\nreading file factorial.csv"<<endl;
            pipeline p(finA);
            break;
        }
        case 50:
        {
            ifstream finB("fibonacci.csv");
            if(finB.fail())
            {
                cerr<<"\nError while opening the Fibonacci program file."<<endl;
                goto label;
            }
            cout<<"\nreading file fibonacci.csv"<<endl;

            pipeline p(finB);
            break;
        }
        case 51:
        {
            ifstream finC("inst_mem.csv");
            if(finC.fail())
            {
                cerr<<"\nError while opening the Inst_mem program file."<<endl;
                goto label;
            }
            cout<<"\nreading file inst_mem.csv"<<endl;

            pipeline p(finC);
            break;
        }
        case 52:
        {
            ifstream finD(".csv");
            if(finD.fail())
            {
                cerr<<"\nError while opening the Inst_mem program file."<<endl;
                goto label;
            }
            cout<<"\nreading file add2Num.csv"<<endl;
            pipeline p(finD);
            break;
        }
        case 53:
        {
            cout<<"Cheers!"<<endl;
            return;
        }
    }
    goto label;
}