#pragma once
#include <string>

class NetworkManager {
public:
    void showNetworkInfo() const;
    void dnsLookup(const std::string& host) const;
    void pingHost(const std::string& host) const;
};
