/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

/** This function decides whether Point first is smaller than Point second at a certain dimension. */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	if (first[curDim] < second[curDim]) {
		return true;
	} else if (first[curDim] > second[curDim]) {
		return false;
	} else {
	    return first < second;
	}
}
/** This function decides whether potential is at a smaller distance to target than currentBest. It returns true if potential is at a smaller distance to target than currentBest. */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	double fromPotential = calculateDistance(target, potential);
	double fromCurrBest = calculateDistance(target, currentBest);
	if (fromPotential < fromCurrBest) {
		return true;
	} else if (fromPotential > fromCurrBest) {
		return false;
	} else {
		return potential < currentBest;
	}
}

/** This constructor constructs the KDTree using a recursive helper function that links the nodes together. */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

	size = 0;
	points = newPoints;
	if (newPoints.size() == 0) {
		root = NULL;
		return;
	} else if (newPoints.size() == 1) {
		size = 1;
		root = new KDTreeNode(newPoints.at(0));
		return;
	}

	buildTree(0, newPoints.size() - 1, 0, root);
	/* int zeroes = 0;
	for (auto & p : points) {
		if (p == Point<Dim>()) {
			zeroes++;
		}
	}
	cout << "zeroes " << zeroes << endl; */
}

/** This copy constructor constructs a KDTree based on the elements of another KDTree that is passed in. */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
	root = copy(other.root);
}

/** The operator= function reassigns the root to point to a new KDTree structure that is passed in. */
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}

	return *this;
}

/** This destructor frees the dynamically allocated memory of the KDTree class. */
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
	clear(root);
	root = NULL;
}

/** The function findNearestNeighbor finds the nearest point to the query among a group of points stored in a KDTree. */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {

    /**
     * @todo Implement this function!
     */
	//cout<<"new test"<<endl;
	double radius = 0;
	return findNearestHelper(query, root, 0, radius);  
}

/** This is a helper function to be called recursively to get the nearest neighboring point. */
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestHelper(const Point<Dim>& query, KDTreeNode* subroot, int dim, double& radius) const {
	Point<Dim> currBest = subroot->point;
	Point<Dim> newCurrBest;
	double childdistance;
	double currDistance;

	//cout<<"current node ";
	//subroot->point.print(cout);
	//cout<<endl;
	if (smallerDimVal(query, subroot->point, dim)) { // query smaller than current point
		if(subroot->left == NULL) {
			currBest = subroot->point;
		} else { // get child point
			currBest = findNearestHelper(query, subroot->left, (dim + 1)%Dim, radius); 
		}	
		if (shouldReplace(query, currBest, subroot->point)) { // current point closer to query than child point
			currBest = subroot->point;
		}
		radius = calculateDistance(query, currBest);

   		if (possibleOtherSide(query, subroot->point, dim, radius) && subroot->right != NULL) {
			newCurrBest = findNearestHelper(query, subroot->right, (dim + 1)%Dim, radius);
			if (shouldReplace(query, currBest, newCurrBest)) {
				currBest = newCurrBest;
			}
		}
		//currBest.print(cout);
		//cout<<endl;
		return currBest;

	} else {
		if(subroot->right == NULL) {
			currBest = subroot->point;
		} else { // get child point
			currBest = findNearestHelper(query, subroot->right, (dim + 1)%Dim, radius); 
		}
		if (shouldReplace(query, currBest, subroot->point)) { // current point closer to query than child point
			currBest = subroot->point;
		}
		radius = calculateDistance(query, currBest);

   		if (possibleOtherSide(query, subroot->point, dim, radius) && subroot->left != NULL) {
			newCurrBest = findNearestHelper(query, subroot->left, (dim + 1)%Dim, radius);
			if (shouldReplace(query, currBest, newCurrBest)) {
				currBest = newCurrBest;
			}
		}
		//currBest.print(cout);
		//cout<<endl;
		return currBest;
	}
}


/** This function returns true if the distance from the query to the splitting point is less than the radius between the query and the current point. */
template <int Dim>
bool KDTree<Dim>::possibleOtherSide(const Point<Dim>& query,
  const Point<Dim>& curr, int dimension, double distance) const
{
	return (curr[dimension]- query[dimension])*(curr[dimension]- query[dimension]) <= distance;
}




/** The helper function calculateDistance calculates the distance between two points. */
template <int Dim>
double KDTree<Dim>::calculateDistance(const Point<Dim> &a, const Point<Dim> &b) const
{
	double sum = 0;
	for (int i = 0; i < Dim; i++) {
		sum += (a[i] - b[i]) * (a[i] - b[i]);
	}

	return sum;
}

/** The function buildTree is a helper function to build the tree. */
template <int Dim>
void KDTree<Dim>::buildTree(int start, int end, int dimension, KDTreeNode *& node)
{
	if (start > end) {
		node = NULL;
		return;
	}
	
	int median = (start + end)/2;
	int newdim = (dimension + 1) % Dim;
	quickSelect(start, end, median, dimension);

	Point<Dim> p = points[median];
	node = new KDTreeNode(p);
	size++;	
	buildTree(start, median - 1, newdim, node->left);
	buildTree(median + 1, end, newdim, node->right);
}

/** The function quickSelect finds the kth smallest number in the array. */
template <int Dim>
void KDTree<Dim>::quickSelect(int start, int end, int k, int dimension)
{
	if (start >= end)
		return;
	int index = partition(start, end, (start + end)/2, dimension);
	if (index < k) {
		return quickSelect(index + 1, end, k, dimension);
	}

	if (index > k) {
		return quickSelect(start, index - 1, k, dimension);
	}
}

/** The function partition partitions the array based on the pivot. */
template <int Dim>
int KDTree<Dim>::partition(int start, int end, int pivot, int dimension)
{
	Point<Dim> point = points[pivot];
	int r = start;
	Point<Dim> temp;
	temp = points[pivot];
	points[pivot] = points[end];
	points[end] = temp;

	for (int i = start; i < end; i++) {
		if (smallerDimVal(points[i], point, dimension)) {
			temp = points[r];
			points[r] = points[i];
			points[i] = temp;
			r++;
		}
	}
	temp = points[r];
	points[r] = points[end];
	points[end] = temp;
	return r;
}


/** This helper function makes a copy of another tree. */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* subroot)
{
	if (subroot == NULL)
		return NULL;

	KDTreeNode* node = new KDTreeNode(subroot->point);
	node->left = copy(subroot->left);
	node->right = copy(subroot->right);
	return node;
}

/** This helper function deletes all the nodes in a tree. */
template<int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot)
{
	if (subroot == NULL)
		return;

	clear(subroot->left);
	clear(subroot->right);
	delete subroot;
	subroot = NULL;
}

