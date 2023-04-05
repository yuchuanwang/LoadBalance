// Load Balance with Consistent Hashing
// Yuchuan Wang
// yuchuan.wang@gmail.com

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>
#include <iostream>

class LoadBalanceConsistentHashing
{
public: 
    LoadBalanceConsistentHashing(int vNum = 32)
    {
        virtualNum = vNum; 
    }

    ~LoadBalanceConsistentHashing()
    {
    }

    bool AddServer(const std::string& srv)
    {
        servers.push_back(srv);

        // Insert virtual nodes for each real server
        for(int i = 0; i < virtualNum; i++)
        {
            // Compose name like: 192.168.1.10#1
            std::stringstream srvName;
            srvName << srv << "#" << i; 
            unsigned int hashKey = std::hash<std::string>{}(srvName.str());
            nodes.insert({hashKey, srv});
        }

        return true;
    }

    bool DeleteServer(const std::string& srv)
    {
        auto server = std::find(servers.begin(), servers.end(), srv);
        if(server == servers.end())
        {
            std::cout << "Invalid server to delete. " << std::endl;
            return false; 
        }

        // Delete from real servers
        servers.erase(server);

        // Delete virtual nodes for this real server
        for(int i = 0; i < virtualNum; i++)
        {
            // Compose name like: 192.168.1.10#1
            std::stringstream srvName;
            srvName << srv << "#" << i; 
            unsigned int hashKey = std::hash<std::string>{}(srvName.str());

            // Find and delete
            auto it = nodes.find(hashKey);
            if(it != nodes.end()) 
            {
                nodes.erase(it);
            }
        }

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

        // Find the node for this request
        int val = rand(); 
        unsigned int hashKey = std::hash<std::string>{}(std::to_string(val));
        auto node = nodes.lower_bound(hashKey);
        if(node == nodes.end())
        {
            // Use the first node if not found
            node = nodes.begin();
        }

        // Update stats
        stats[node->second]++;

        return true; 
    }

    void ResetStats()
    {
        stats.clear();
    }

    void PrintStats() const
    {
        std::cout << "Server Hit stats with Consistent Hashing: ";
        for(auto x : stats)
        {
            std::cout << std::endl;
            std::cout << x.first << ": " << x.second;
        }
        std::cout << std::endl;
    }

private:
    // Virtual nodes number for each real server
    int virtualNum; 
    // The real servers
    std::vector<std::string> servers; 
    // The virtual servers. Key is hash, value is the real server
    std::map<unsigned int, std::string> nodes; 
    // Stats, key is the real server, value is the hit count
    std::unordered_map<std::string, int> stats; 
};
