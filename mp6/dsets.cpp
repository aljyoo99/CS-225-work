/* Your code here! */
#include "dsets.h"

/* This function initializes the disjoint set. */
void DisjointSets::addelements(int num) {
	for (int i = 0; i < num; i++) {
		sets.push_back(-1);
	}
}

/* This function returns the index of the root in the up-tree in which the given element exists */
int DisjointSets::find(int elem) {
	if (sets[elem] < 0) {
		return elem;
	}
	int root = find(sets[elem]);
	sets[elem] = root;
	return root;

}	

/* This function does a union by size of two disjoint sets at their roots. Smaller set points to the larger set. */
void DisjointSets::setunion(int a, int b) {
	int root1 = find(a);
	int root2 = find(b);
	int newSize = sets[root1] + sets[root2];

	if (sets[root1] < sets[root2]) {
		sets[root2] = root1;
		sets[root1] = newSize;
	} else {
		sets[root1] = root2;
		sets[root2] = newSize;
	}
}		

/* This function returns the number of nodes in the up-tree containing the element */
int DisjointSets::size(int elem) {
	int root = find(elem);
	int count = 0;


	for (int i = 0; i < (int)sets.size(); i++) {
		if (find(i) == root) {
			count++;
		}
	}
	return count;
}
