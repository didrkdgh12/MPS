/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq( const string & infile ) : filename( infile ) { 
    /* nothing */
}

template <template <class K, class V> class Dict>
vector< pair<string, int> > WordFreq<Dict>::getWords( int threshold ) const {
    TextFile infile( filename );
    vector< pair<string, int> > ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
    Dict<string, int> hashTab(256);
    while(infile.good()){
    	string w = infile.getNextWord();
    	hashTab[w]++;
	}

    typename Dict<string, int>::iterator it;
    for(it = hashTab.begin(); it != hashTab.end(); it++) {
    	if(it->second >= threshold) {
    		ret.push_back(*it);
    	}
    }
    //(void) threshold; // prevent warnings... When you implement this function, remove this line.

    return ret;
}