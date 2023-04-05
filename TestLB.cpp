// Test the various Load Balance
// Yuchuan Wang
// yuchuan.wang@gmail.com

#include "LoadBalanceRoundRobin.h"
#include "LoadBalanceWeightedRoundRobin.h"
#include "LoadBalanceRandom.h"
#include "LoadBalanceWeightedRandom.h"
#include "LoadBalanceConsistentHashing.h"

/*
Server Hit stats with round robin:
192.168.1.14: 200000
192.168.1.13: 200000
192.168.1.12: 200000
192.168.1.11: 200000
192.168.1.10: 200000
*/
void TestRoundRobin()
{
    LoadBalanceRoundRobin lb;
    lb.AddServer("192.168.1.10");
    lb.AddServer("192.168.1.11");
    lb.AddServer("192.168.1.12");
    lb.AddServer("192.168.1.13");
    lb.AddServer("192.168.1.14");

    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }

    lb.PrintStats();
}

/*
Server Hit stats with weighted round robin: 
192.168.1.13: 200000
192.168.1.10: 50000
192.168.1.12: 150000
192.168.1.11: 100000
192.168.1.14: 500000
*/
void TestWeightedRoundRobin()
{
    LoadBalanceWeightedRoundRobin lb;
    lb.AddServer("192.168.1.10", 1);
    lb.AddServer("192.168.1.11", 2);
    lb.AddServer("192.168.1.12", 3);
    lb.AddServer("192.168.1.13", 4);
    lb.AddServer("192.168.1.14", 10);

    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }

    lb.PrintStats();
}

/*
Server Hit stats with random: 
192.168.1.13: 200448
192.168.1.10: 199584
192.168.1.14: 199799
192.168.1.11: 199495
192.168.1.12: 200674
*/
void TestRandom()
{
    LoadBalanceRandom lb;
    lb.AddServer("192.168.1.10");
    lb.AddServer("192.168.1.11");
    lb.AddServer("192.168.1.12");
    lb.AddServer("192.168.1.13");
    lb.AddServer("192.168.1.14");

    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }

    lb.PrintStats();
}

/*
Server Hit stats with weighted random: 
192.168.1.13: 200290
192.168.1.12: 149612
192.168.1.11: 100060
192.168.1.10: 50291
192.168.1.14: 499747
*/
void TestWeightedRandom()
{
    LoadBalanceWeightedRandom lb;
    lb.AddServer("192.168.1.10", 1);
    lb.AddServer("192.168.1.11", 2);
    lb.AddServer("192.168.1.12", 3);
    lb.AddServer("192.168.1.13", 4);
    lb.AddServer("192.168.1.14", 10);

    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }

    lb.PrintStats();
}

/*
Server Hit stats with Consistent Hashing: 
192.168.1.13: 200693
192.168.1.14: 140848
192.168.1.11: 180680
192.168.1.12: 265031
192.168.1.10: 212748
Server Hit stats with Consistent Hashing: 
192.168.1.14: 205757
192.168.1.10: 292805
192.168.1.11: 241764
192.168.1.13: 259674
*/
void TestConsistentHashing()
{
    LoadBalanceConsistentHashing lb;
    lb.AddServer("192.168.1.10");
    lb.AddServer("192.168.1.11");
    lb.AddServer("192.168.1.12");
    lb.AddServer("192.168.1.13");
    lb.AddServer("192.168.1.14");

    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }

    lb.PrintStats();

    // Delete one server, and try again
    lb.DeleteServer("192.168.1.12");
    lb.ResetStats();
    for(int i = 0; i < 1000000; i++)
    {
        lb.NextRequest();
    }
    lb.PrintStats();
}

int main()
{
    TestRoundRobin();
    TestWeightedRoundRobin();
    TestRandom();
    TestWeightedRandom();
    TestConsistentHashing();
    return 0;
}
