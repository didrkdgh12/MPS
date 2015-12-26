/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return currentIdx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    return currentIdx*2< _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    size_t leftchild = leftChild(currentIdx);
    size_t rightchild = rightChild(currentIdx);
    if (currentIdx*2+1<_elems.size()) {
        return (higherPriority(_elems[leftchild], _elems[rightchild]))? leftchild:rightchild;
    }
    else {
        return currentIdx*2;
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    if (hasAChild(currentIdx)) {
        size_t childIdx = maxPriorityChild(currentIdx);
        if (higherPriority(_elems[childIdx], _elems[currentIdx]))
        {
            std::swap(_elems[currentIdx], _elems[childIdx]);
            heapifyDown(childIdx);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    _elems.push_back(0);
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    _elems.push_back(0);
    for(size_t i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }
    for (int i = parent(_elems.size()); i > 0; i--) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    T ret = _elems[1];
    _elems[1] = _elems[_elems.size() - 1];

    _elems.pop_back();

    heapifyDown(1);
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    return _elems.size() == 1;
}
