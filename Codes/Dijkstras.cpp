#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> Edge; // (cost, destination)

class Graph {
    int V;
    vector<vector<Edge>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int cost) {
        adj[u].push_back({cost, v});
        adj[v].push_back({cost, u}); // undirected graph
    }

    void dijkstra(int src) {
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
        vector<int> dist(V, INT_MAX);

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            for (auto edge : adj[u]) {
                int weight = edge.first;
                int v = edge.second;

                if (dist[v] > d + weight) {
                    dist[v] = d + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nMinimum distances from source (" << src << "):\n";
        for (int i = 0; i < V; i++) {
            cout << "To node " << i << " : " << dist[i] << endl;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter number of locations (nodes): ";
    cin >> V;

    cout << "Enter number of roads (edges): ";
    cin >> E;

    Graph g(V);

    cout << "Enter roads as: source destination cost\n";
    for (int i = 0; i < E; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        g.addEdge(u, v, cost);
    }

    int source;
    cout << "Enter source location: ";
    cin >> source;

    g.dijkstra(source);

    return 0;
}
