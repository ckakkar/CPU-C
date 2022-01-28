#include "statistic.h"


statistic::statistic()
{
    clk=0;
}
void statistic::updateCLK()
{
    clk++;
}
void statistic::updateLatency(const double& time)
{
    latency.push_back(time);
}
void statistic::updateThroughput(const int& lat)
{
    throughput.push_back(lat);
};
void statistic::print_stats()
{
    double avgLat = 0;
    double avgTp = 0;

    for(int i=0;i<latency.size();i++)
        avgLat=avgLat+latency[i];

    for(int i=0;i<throughput.size();i++)
        avgTp=avgTp+throughput[i];

    avgLat = avgLat/avgTp;
    avgTp = avgTp/clk;
    cout<<"\nAverage latency per instruction: "<<fixed<<setprecision(5)<<avgLat<<endl;
    cout<<"Average throughput per cycle: "<<fixed<<setprecision(5)<<avgTp<<endl;
}