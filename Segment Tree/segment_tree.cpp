#include <bits/stdc++.h>
using namespace std;

void buildTree(vector<int> a, int s, int e, vector<int> &tree, int tree_ind) {
	if (s == e) {
		tree[tree_ind] = a[s];
		return;
	}
	int mid = (s + e) >> 1;
	buildTree(a, s, mid, tree, 2 * tree_ind);
	buildTree(a, mid + 1, e, tree, 2 * tree_ind + 1);
	tree[tree_ind] = min(tree[2 * tree_ind], tree[2 * tree_ind + 1]);
	return;
}

int query(vector<int> tree, int start, int end, int ss, int se, int tree_ind) {
	// For finding minimum

	// full overlap
	if (start <= ss && end >= se) return tree[tree_ind];

	// No overlap
	if (start > se || end < ss) return INT_MAX;

	int mid = (ss + se) >> 1;
	int left = query(tree, start, end, ss, mid, 2 * tree_ind);
	int right = query(tree, start, end, mid + 1, se, 2 * tree_ind + 1);
	return min(left, right);
}

void updateNode(vector<int> &tree, int ss, int se, int tree_ind, int update_ind, int increment) {
	if (update_ind > se || update_ind < ss) {
		return;
	}
	if (ss == se) {
		tree[tree_ind] += increment;
		return;
	}
	int mid = (se + ss) >> 1;
	updateNode(tree, ss, mid, 2 * tree_ind, update_ind, increment);
	updateNode(tree, mid + 1, se, 2 * tree_ind + 1, update_ind, increment);
	tree[tree_ind] = min(tree[tree_ind * 2], tree[2 * tree_ind + 1]);
	//return;
}

void updateRange(vector<int> &tree, int ss, int se, int start, int end, int tree_ind, int increment) {
	if (start > se || end < ss) return;

	if (ss == se) {
		tree[tree_ind] += increment;
		return;
	}

	int mid = (se + ss) >> 1;
	updateRange(tree, ss, mid, start, end, 2 * tree_ind, increment);
	updateRange(tree, mid + 1, se, start, end, 2 * tree_ind + 1, increment);

	tree[tree_ind] = min(tree[2 * tree_ind], tree[2 * tree_ind + 1]);
	return;
}

int main() {
	int n, q, start, end;
	cin >> n;
	std::vector<int> a(n), tree(4 * n + 1);
	for (int u = 0; u < n; u++)cin >> a[u];
	buildTree(a, 0, n - 1, tree, 1);

	// Increment all values from index 1 to 3 by +5
	updateRange(tree, 0, n - 1, 1, 3, 1, +5);

	cin >> q;
	while (q--) {
		cin >> start >> end;
		cout << query(tree, start, end, 0, n - 1, 1) << endl;
	}
	return 0;
}
