// finding the minimum in the given range

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
			lazy[2 * tree_ind + 1] += lazy[tree_ind];
			lazy[2 * tree_ind + 2] += lazy[tree_ind];
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
			lazy[2 * tree_ind + 1] += inc;
			lazy[2 * tree_ind + 2] += inc;
		}
		// Here we are returning, not going going for the children node
		return;
	}
	int mid = (ss + se) >> 1;
	updateRangeLazy(tree, ss, mid, l, r, inc, 2 * tree_ind + 1);
	updateRangeLazy(tree, mid + 1, se, l, r, inc, 2 * tree_ind + 2);
	// update the cur index like postorder traversal

	tree[tree_ind] = min(tree[2 * tree_ind + 1], tree[2 * tree_ind + 2]);
	return;
}

int query(vector<int> &tree, int ss, int se, int qs, int qe, int tree_ind) {

	// first resolve lazy value at current node
	if (lazy[tree_ind] != 0) {
		tree[tree_ind] += lazy[tree_ind];
		if (ss != se) {
			lazy[2 * tree_ind + 1] += lazy[tree_ind];
			lazy[2 * tree_ind + 2] += lazy[tree_ind];

		}
		lazy[tree_ind] = 0;
	}
	// No overlap
	if (ss > qe or se < qs) return INT_MAX;

	//complete overlap
	if (ss >= qs && se <= qe) return tree[tree_ind];

	// Partial overlap
	int mid = (ss + se) >> 1;
	int left = query(tree, ss, mid, qs, qe, 2 * tree_ind + 1);
	int right = query(tree, mid + 1, se, qs, qe, 2 * tree_ind + 2);
	return min(left, right);
}

void build_tree(vector<int> &tree, int tree_ind, int ss, int se, vector<int> a) {
	if (ss == se) {
		tree[tree_ind] = a[ss];
		return;
	}
	int mid = (ss + se) >> 1;
	build_tree(tree, 2 * tree_ind + 1, ss, mid, a);
	build_tree(tree, 2 * tree_ind + 2, mid + 1, se, a);
	tree[tree_ind] = min(tree[2 * tree_ind + 1], tree[2 * tree_ind + 2]);
	return;
}

int main() {
	vector<int> a{1, 3, 2, -5, 6, 4};
	int n = a.size();
	vector<int> tree(4 * n , 0);

	build_tree(tree, 0, 0, n - 1, a);

	// Update elements from 0 to 2 by +10
	updateRangeLazy(tree, 0, n - 1, 0, 2, +10, 0);
	// [10, 13, 12, -5, 6, 4]

	// Update elements from 2 to 2 by +5
	updateRangeLazy(tree, 0, n - 1, 2, 2, +5, 0);
	// [10, 13, 17, -5, 6, 4]

	cout << "Query 0-3 " << query(tree, 0, n - 1, 0, 3, 0) << endl;

	// Update elements from 3 to 4 by +10
	updateRangeLazy(tree, 0, n - 1, 3, 4, +10, 0);
	// [10, 13, 17, 5, 16, 4]

	cout << "Query 3-5 " << query(tree, 0, n - 1, 3, 5, 0) << endl;

	return 0;
}
