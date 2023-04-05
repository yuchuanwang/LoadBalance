// Load Balance with Weighted Round Robin
// Yuchuan Wang
// yuchuan.wang@gmail.com

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>

class LoadBalanceWeightedRoundRobin
{
public: 
    LoadBalanceWeightedRoundRobin()
    {
        current = -1;
    }

    ~LoadBalanceWeightedRoundRobin()
    {
    }

    bool AddServer(const std::string& srv, int weight)
    {
        if(weight < 1)
        {
            std::cout << "Weight should be equal or greater than 1." << std::endl;
            return false;
        }

        for(int i = 0; i < weight; i++)
        {
            // Add weight times to vector
            servers.push_back(srv);
        }

        // Shuffle the vector so that servers will be out of order
        std::random_shuffle(servers.begin(), servers.end());
        return true;
    }

    // Simulate a new request
    bool NextRequest()
    {
        if(servers.empty())
        {
            std::cout << "Please add servers first. " << std::endl;
            return false; 
        }

        // Move to next server
        current = (current + 1) % servers.size();
        // Update stats
        stats[servers[current]]++;

        return true; 
    }

    void PrintStats() const
    {
        std::cout << "Server Hit stats with weighted round robin: ";
        for(auto x : stats)
        {
            std::cout << std::endl;
            std::cout << x.first << ": " << x.second;
        }
        std::cout << std::endl;
    }

private:
    // The servers to be balanced
    std::vector<std::string> servers; 
    // Index of server hit
    int current;
    // Stats, key is the server, value is the hit count
    std::unordered_map<std::string, int> stats; 
};
