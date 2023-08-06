#pragma once

#include <limits>
#include <queue>
#include <vector>

template<class T>
std::vector<long long> dijkstra(std::vector<std::vector<std::pair<int,T>>>& to, int s=0) {
    struct QueElem {
        int v;
        long long c;
        bool operator<(const QueElem a) const {return c > a.c;}
        QueElem(int v, long long c): v(v), c(c) {}
    };
    std::priority_queue<QueElem> q;
    std::vector<long long> dist(to.size(), std::numeric_limits<T>::max());
    dist[s] = 0;
    q.emplace(s, 0);
    while(!q.empty()) {
        QueElem qe = q.top(); q.pop();
        int u = qe.v;
        long long c = qe.c;
        if (c > dist[u]) continue;
        for(auto vc: to[u]) {
            int v = vc.first;
            long long nc = c + vc.second;
            if (nc < dist[v]) {
                dist[v] = nc;
                q.emplace(v, nc);
            }
        }
    }
    return dist;
}