/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h>

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    // cout << first[curDim] << " " << second[curDim] << endl;
    if(first[curDim] == second[curDim]) {
        return first < second;
    } else {
        return first[curDim] < second[curDim];    
    }
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
    int potTarDist = calculateDistance(potential, target);
    int curTarDist = calculateDistance(currentBest, target);
    if(potTarDist < curTarDist) {
        return true;
    } else if(potTarDist > curTarDist) {
        return false;
    } else {
        return potential < currentBest;
    }
}

template<int Dim>
int KDTree<Dim>::calculateDistance(const Point<Dim> & pointOne, const Point<Dim> & pointTwo) const{
    int squaredTotal = 0;
    for(int i = 0; i < Dim; i++) {
        squaredTotal = squaredTotal + ((pointOne[i] - pointTwo[i]) * (pointOne[i] - pointTwo[i]));
    }
    squaredTotal = sqrt(squaredTotal);
    return squaredTotal;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
    points = newPoints;
    if(points.size() != 0)
        bobTheBuilder(0, newPoints.size()-1, 0);
 }

template<int Dim>
void KDTree<Dim>::bobTheBuilder(int left, int right, int dim) {
    if(left>=right) {
        return;
    }
    int middle = (left+right)/2;
    quickSelect(left, right, dim%Dim, middle);
    // if(left < middle) {
    //     bobTheBuilder(left, middle-1, (dim+1)%Dim);
    // } else if(right > middle) {
    //     bobTheBuilder(middle+1, right, (dim+1)%Dim);
    // }
    bobTheBuilder(left, middle-1, (dim+1)%Dim);
    bobTheBuilder(middle+1, right, (dim+1)%Dim);
}

template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int dim, int middle) { 
   while(left != right) {
        int pIndex = partitionVector(left, right, dim, middle);
        if(pIndex == middle) {
            return;
        } else if (middle < pIndex) {
            right = pIndex - 1;
        } else {
            left = pIndex + 1;
        }
    }
    // if(left < right) {
    //     int pIndex = partitionVector(left, right, dim, 0);
    //     quickSelect(left, pIndex-1, (dim+1)%Dim, middle);
    //     quickSelect(pIndex+1, right, (dim+1)%Dim, middle);
    // }
}

template<int Dim>
int KDTree<Dim>::partitionVector(int left, int right, int dim, int middle) {
    Point<Dim> piv = points[middle];
    Point<Dim> holder = points[right];
    points[right] = points[middle];
    points[middle] = holder;
    int idx = left;
    for(int i = left; i < right; i++) {
        if (smallerDimVal(points[i], piv, dim) || points[i] == piv) {
            holder = points[idx];
            points[idx] = points[i];
            points[i] = holder;
            idx++;
        }
    }
    holder = points[right];
    points[right] = points[idx];
    points[idx] = holder;
    return idx;
    // Point<Dim> pivot = points[right];
    // int i = left; //Place for swapping
    // for(int j = left; j < right - 1; j++) {
    //     if(smallerDimVal(points[j], pivot, dim)) {
    //         swapPoints(i, j);
    //         i = i +1;
    //     }
    // }
    // swapPoints(i, right);
    // return i;
}

template<int Dim>
void KDTree<Dim>::swapPoints(int indexOne, int indexTwo) {
    Point<Dim> temp = points[indexOne];
    points[indexOne] = points[indexTwo];
    points[indexTwo] = temp;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> ret = Point<Dim>();
    if(points.size() != 0) {
        ret = neighborDetector(0, points.size()-1, 0, query, points[(points.size()-1)/2]);        
    }
    return ret;
}

template<int Dim>
Point<Dim> KDTree<Dim>::neighborDetector(int left, int right, int dim, const Point<Dim> &query, const Point<Dim> &currentBest) const {
    Point<Dim> ret = currentBest;
    bool target = true;
    if (left == right)
    {

        if (shouldReplace(query, currentBest, points[left]))
        {

             ret = points[left];
            return ret;
        }
        ret = currentBest;
        return ret;
    }

    int median = (left + right)/2;
    int otherSubMedian;
    if (smallerDimVal(points[median], query, dim) && right > median)
    {
        ret = neighborDetector(median+1, right, (dim+1)%Dim, query, currentBest);
        target = false;
        otherSubMedian = (left+median-1)/2;
    }
    if (smallerDimVal(query, points[median], dim) && left < median)
    {   
        ret = neighborDetector(left, median-1,(dim+1)%Dim, query, currentBest);
        target = true;
        otherSubMedian = (median+1+right-1)/2;
    }

    if (shouldReplace(query, ret, points[median]))
        ret = points[median];

    Point<Dim> a = points[median];
    if (pow(a[dim] - query[dim],2) <= calculateDistance(query, ret))
    {
        if (target && right > median)
            ret = neighborDetector(median+1, right, (dim+1)%Dim, query, ret);
        if (!target && left < median)
            ret = neighborDetector(left, median-1, (dim+1)%Dim, query, ret);
    }
    return ret;
}