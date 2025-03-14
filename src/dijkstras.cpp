#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    vector<int> min_distance(G.numVertices, INF);
    min_distance[source] = 0;
    previous = vector<int>(G.numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> vertex_queue;
    vertex_queue.push({min_distance[source], source});
    while (!vertex_queue.empty()) {
        int dist = vertex_queue.top().first;
        int u = vertex_queue.top().second;
        vertex_queue.pop();

        if (dist > min_distance[u])
            continue;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            int distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.push({min_distance[v], v});
            }
        }
    }

    return min_distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path.empty())
        return path;
    int total = distances[path.back()];
    print_path(path, total);
    return path;
}

void print_path(const vector<int>& v, int total) {
    int a = v.size();
    for (int i = 0; i < a; ++i) {
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << '\n';
}