#include "NetworkManager.h"
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <array>
#include <memory>

void NetworkManager::showNetworkInfo() const {
    struct ifaddrs* interfaces = nullptr;
    if (getifaddrs(&interfaces) == -1) {
        perror("getifaddrs");
        return;
    }

    std::cout << "\n=== Network Interfaces ===\n";
    for (struct ifaddrs* ifa = interfaces; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) continue;
        int family = ifa->ifa_addr->sa_family;
        if (family != AF_INET && family != AF_INET6) continue;

        char host[NI_MAXHOST]{};
        int rc = getnameinfo(ifa->ifa_addr,
                             family == AF_INET ? sizeof(sockaddr_in) : sizeof(sockaddr_in6),
                             host, sizeof(host), nullptr, 0, NI_NUMERICHOST);
        if (rc == 0) {
            std::cout << ifa->ifa_name << "\t" << (family == AF_INET ? "IPv4" : "IPv6")
                      << "\t" << host << '\n';
        }
    }
    freeifaddrs(interfaces);
}

void NetworkManager::dnsLookup(const std::string& host) const {
    struct addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo* result = nullptr;
    int rc = getaddrinfo(host.c_str(), nullptr, &hints, &result);
    if (rc != 0) {
        std::cerr << "DNS lookup failed: " << gai_strerror(rc) << '\n';
        return;
    }

    std::cout << "\n=== DNS Lookup: " << host << " ===\n";
    for (struct addrinfo* p = result; p != nullptr; p = p->ai_next) {
        char address[NI_MAXHOST]{};
        rc = getnameinfo(p->ai_addr, p->ai_addrlen, address, sizeof(address), nullptr, 0, NI_NUMERICHOST);
        if (rc == 0) std::cout << address << '\n';
    }
    freeaddrinfo(result);
}

void NetworkManager::pingHost(const std::string& host) const {
    // Use exec-style shell invocation with a simple fixed argument pattern.
    // The host is quoted so shell metacharacters are not interpreted as commands.
    std::string safe;
    safe.reserve(host.size() + 2);
    safe = "'";
    for (char c : host) {
        if (c == '\'') safe += "'\\''";
        else safe += c;
    }
    safe += "'";

    std::string command = "ping -c 4 " + safe;
    std::cout << "\n=== Ping: " << host << " ===\n";
    int rc = std::system(command.c_str());
    if (rc == -1) std::cerr << "Failed to start ping.\n";
}
