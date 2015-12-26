#include "dsets.h"

using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        vSet.push_back(-1);
    }

}

int DisjointSets::find(int elem) {

    // //This method does not have path compression
    // if(vSet[elem] < 0) {
    //     return elem;
    // } else {
    //     return find(vSet[elem]);
    // }

    // Improved Method below, wth path compression
    if(vSet[elem] < 0) {
        return elem;
    } else {
        vSet[elem] = find(vSet[elem]);
        return find(vSet[elem]);
    }
}

void DisjointSets::setunion(int a, int b) {
    a = find(a);
    b = find(b);
    int newSize = vSet[a] + vSet[b];
    if (!isBigger(a,b)) {    // b has larger tree
        vSet[b] = a;            // make b parent of a
        vSet[a] = newSize;     // update # of items in b's tree
    } else {                    // a has equal or larger tree
        vSet[a] = b;            // make a parent of b
        vSet[b] = newSize;     // update # of items in a's tree
    }
}

bool DisjointSets::isBigger(int a, int b) {
    return vSet[a] > vSet[b];
}