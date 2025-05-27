#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
    vector<int> tree;
    int n;

public:
    SegmentTree(vector<int>& spending) {
        n = spending.size();
        tree.resize(4 * n);
        build(spending, 0, n - 1, 0);
    }

    void build(vector<int>& arr, int start, int end, int node) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(arr, start, mid, 2 * node + 1);
        build(arr, mid + 1, end, 2 * node + 2);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    int query(int l, int r) {
        return queryUtil(0, n - 1, l, r, 0);
    }

    int queryUtil(int start, int end, int l, int r, int node) {
        if (r < start || end < l)
            return 0;
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) / 2;
        return queryUtil(start, mid, l, r, 2 * node + 1) +
               queryUtil(mid + 1, end, l, r, 2 * node + 2);
    }

    void update(int index, int value) {
        updateUtil(0, n - 1, index, value, 0);
    }

    void updateUtil(int start, int end, int idx, int val, int node) {
        if (start == end) {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        if (idx <= mid)
            updateUtil(start, mid, idx, val, 2 * node + 1);
        else
            updateUtil(mid + 1, end, idx, val, 2 * node + 2);

        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }
};

int main() {
    vector<int> dailySpending = {1000, 800, 1200, 700, 900, 1100, 500, 600, 1500, 100};

    SegmentTree st(dailySpending);

    int l = 0, r = 4; // Query spending from day 1 to day 5
    int total = st.query(l, r);
    cout << "Total spending from day " << l + 1 << " to day " << r + 1 << ": ₹" << total << endl;

    if (total >= 5000)
        cout << "Eligible for Coupon" << endl;
    else
        cout << "Not eligible for Coupon" << endl;

    cout << "\nUpdating day 3 spending to ₹2000" << endl;
    st.update(2, 2000); 

    total = st.query(l, r);
    cout << "Updated total from day " << l + 1 << " to day " << r + 1 << ": ₹" << total << endl;

    if (total >= 5000)
        cout << "Eligible for Coupon" << endl;
    else
        cout << "Not eligible for Coupon" << endl;

    return 0;
}
