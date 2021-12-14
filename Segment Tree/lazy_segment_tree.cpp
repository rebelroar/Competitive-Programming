#include<bits/stdc++.h>
using namespace std;

int lazy[1000] = {0};

// In this method we are not gonna update all node of the given range we just update the root of that range
// and increment the lazy value of their children nodes(here we are not gonna update the value of children nodes)
// whenever we need any query of that particular range we just change the value of that range (i.e. increment by its lazy value)
// so instead of O(N) tc it take O(log(n)) for update range
void updateRangeLazy(vector<int> &tree, int ss, int se, int l, int r, int inc, int tree_ind) {

	// before going down resolve the lazy value if exist
	if (lazy[tree_ind] != 0) {
		tree[tree_ind] += lazy[tree_ind];
		// if it is not leaf node
		if (ss != se) {
			lazy[2 * tree_ind] += lazy[tree_ind];
			lazy[2 * tree_ind + 1] += lazy[tree_ind];
		}
		lazy[tree_ind] = 0; // clear the lazy value at cur index
	}

	// No overlap
	if (se < l || r < ss) return;

	// Complete overlap
	// here we update the root and lazy value of children of root and return
	if (ss >= l && r >= se) {
		tree[tree_ind] += inc;

		if (ss != se) {
			lazy[2 * tree_ind] += inc;
			lazy[2 * tree_ind + 1] += inc;
		}
		// Here we are returning, not going going for the children node
		return;
	}
	int mid = (ss + se) >> 1;
	updateRangeLazy(tree, ss, mid, l, r, inc, 2 * tree_ind);
	updateRangeLazy(tree, mid + 1, se, l, r, inc, 2 * tree_ind + 1);
	// update the cur index like postorder traversal

	tree[tree_ind] = min(tree[2 * tree_ind], tree[2 * tree_ind + 1]);
	return;
}

int query(vector<int> &tree, int ss, int se, int qs, int qe, int tree_ind) {

	// first resolve lazy value at current node
	if (lazy[tree_ind] != 0) {
		tree[tree_ind] += lazy[tree_ind];
		if (ss != se) {
			lazy[2 * tree_ind] += lazy[tree_ind];
			lazy[2 * tree_ind + 1] += lazy[tree_ind];

		}
		lazy[tree_ind] = 0;
	}
	// No overlap
	if (ss > qe or se < qs) return INT_MAX;

	//complete overlap
	if (ss >= qs && se <= qe) return tree[tree_ind];

	// Partial overlap
	int mid = (ss + se) >> 1;
	int left = query(tree, ss, mid, qs, qe, 2 * tree_ind);
	int right = query(tree, mid + 1, se, qs, qe, 2 * tree_ind + 1);
	return min(left, right);
}

void build_tree(vector<int> &tree, int tree_ind, int ss, int se, vector<int> a) {
	if (ss == se) {
		tree[tree_ind] = a[ss];
		return;
	}
	int mid = (ss + se) >> 1;
	build_tree(tree, 2 * tree_ind, ss, mid, a);
	build_tree(tree, 2 * tree_ind + 1, mid + 1, se, a);
	tree[tree_ind] = min(tree[2 * tree_ind], tree[2 * tree_ind + 1]);
	return;
}

int main() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int u = 0; u < n; u++)cin >> a[u];

	vector<int> tree(4 * n + 1, 0);

	build_tree(tree, 1, 0, n - 1, a);

	updateRangeLazy(tree, 0, n - 1, 0, 2, +10, 1);

	updateRangeLazy(tree, 0, n - 1, 2, 2, +5, 1);

	cout << "Query 0-3 " << query(tree, 0, n - 1, 0, 3, 1) << endl;

	updateRangeLazy(tree, 0, n - 1, 3, 4, +10, 1);

	cout << "Query 3-5 " << query(tree, 0, n - 1, 3, 5, 1) << endl;

	return 0;
}