#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// Define a product structure
struct Product {
    int productId;
    double score;

    Product(int id, double s) : productId(id), score(s) {}
};

// Min-Heap comparator (lowest score at top)
struct Compare {
    bool operator()(const Product& a, const Product& b) {
        return a.score > b.score;  // min-heap
    }
};

// Function to get top K recommendations
vector<Product> getTopKRecommendations(vector<Product>& products, int k) {
    priority_queue<Product, vector<Product>, Compare> minHeap;

    for (const auto& product : products) {
        if (minHeap.size() < k) {
            minHeap.push(product);
        } else if (product.score > minHeap.top().score) {
            minHeap.pop();
            minHeap.push(product);
        }
    }

    // Extract products from heap
    vector<Product> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    // Optional: sort descending by score
    sort(result.begin(), result.end(), [](const Product& a, const Product& b) {
        return a.score > b.score;
    });

    return result;
}

// Example usage
int main() {
    vector<Product> products = {
        Product(101, 0.91),
        Product(102, 0.78),
        Product(103, 0.88),
        Product(104, 0.95),
        Product(105, 0.65)
    };

    int k = 3;
    vector<Product> topProducts = getTopKRecommendations(products, k);

    cout << "Top " << k << " Recommended Products:\n";
    for (const auto& p : topProducts) {
        cout << "Product ID: " << p.productId << " | Score: " << p.score << "\n";
    }

    return 0;
}
