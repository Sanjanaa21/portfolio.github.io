struct Product {
    int id;
    vector<pair<int, double>> neighbors; // pair<neighbor_id, cost>
};

double heuristic(int productA, int goalProduct) {
    // A heuristic estimating "distance" or difference between productA and goalProduct
    // e.g., difference in features, category similarity score, etc.
    // For simplicity, return 0 (Dijkstra's behavior) or a predefined heuristic.
    return 0.0;
}

vector<int> aStarRecommend(int startProduct, int goalProduct, const vector<Product>& products) {
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> openSet;
    unordered_map<int, int> cameFrom;
    unordered_map<int, double> gScore;
    unordered_map<int, double> fScore;

    for (const auto& p : products) {
        gScore[p.id] = INFINITY;
        fScore[p.id] = INFINITY;
    }
    gScore[startProduct] = 0;
    fScore[startProduct] = heuristic(startProduct, goalProduct);

    openSet.push({fScore[startProduct], startProduct});

    while (!openSet.empty()) {
        int current = openSet.top().second;
        if (current == goalProduct) {
            // reconstruct path
            vector<int> path;
            while (cameFrom.find(current) != cameFrom.end()) {
                path.push_back(current);
                current = cameFrom[current];
            }
            path.push_back(startProduct);
            reverse(path.begin(), path.end());
            return path; // recommended product path
        }
        openSet.pop();

        for (auto& neighbor : products[current].neighbors) {
            int neighborID = neighbor.first;
            double cost = neighbor.second;
            double tentative_gScore = gScore[current] + cost;

            if (tentative_gScore < gScore[neighborID]) {
                cameFrom[neighborID] = current;
                gScore[neighborID] = tentative_gScore;
                fScore[neighborID] = tentative_gScore + heuristic(neighborID, goalProduct);
                openSet.push({fScore[neighborID], neighborID});
            }
        }
    }

    return {}; // no path found
}
