#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

template <typename K>
class HashFunction {
public:
    virtual unsigned int operator()(const K& key) const = 0;
};

class SimpleStringHash : public HashFunction<string> {
public:
    // Computes a simple hash value for a string
    unsigned int operator()(const string& key) const {
		int seed = 193;
		unsigned long hash = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hash = (hash * seed) + key[i];
		}
	
		return hash;
    }

// 		unsigned int hash = 0;
// 		for (int i = 0; i < key.size(); i++) {
// 			hash += key[i];
// 		}
		
// 		return hash;
//     }
};

/// An abstract collision resolution function
class ResolutionFunction {
public:
    virtual unsigned int operator()(int i) const = 0;
};

/// The instructor did the hard part for you and implemented the two resolution functions. Phew!
class LinearProbing : public ResolutionFunction {
public:
    unsigned int operator()(int i) const {
        return i;
    }
};

class QuadraticProbing : public ResolutionFunction {
public:
    unsigned int operator()(int i) const {
        return i * i;
    }
};

/// Returns the bit index of the most significant bit.
/// If the input is zero, it returns zero
/// This function will help you locate the crrect good prime in the array below
/// It will also help you compute the next power of two
int mostSignificantBit(int x) {
    if (x == 0)
        return 0;
    int mostSignificantBit = 31;
    while ((x & (1 << mostSignificantBit)) == 0)
        mostSignificantBit--;
    return mostSignificantBit;
}

/// Good prime numbers to use as Hashtable sizes
/// Copied from https://web.archive.org/web/20120705020114/http://planetmath.org/encyclopedia/GoodHashTablePrimes.html
int GoodPrimeNumbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
    24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
    12582917, 25165843, 50331653, 100663319, 201326611, 402653189,
    805306457, 1610612741
};

int findPrime(int n)
{
	int temp = 0;
	int c = mostSignificantBit(n);
	
	for (int i = 0; i < 26; ++i)
	{
		temp = mostSignificantBit(GoodPrimeNumbers[i]);

		if (c <= 5)
		{
			if (n > GoodPrimeNumbers[i])
			{
			    c = 97;
			    break;
			}
			else
			{
			    c = 53;
			    break;
			}
		}
		else if (c == temp)
		{
			if (n > GoodPrimeNumbers[i])
			{
				c = GoodPrimeNumbers[i + 1];
				break;
			}
			else
			{
				c = GoodPrimeNumbers[i];
				break;
			}
		}
		else if (c + 1 == temp)
		{
			if (GoodPrimeNumbers[i] < n)
			{
				c = GoodPrimeNumbers[i + 1];
				break;
			}
			else
			{
				c = GoodPrimeNumbers[i];
				break;
			}
		}
	}
	
	return c;
}

int findPowerOfTwo(int n)
{
    int c = pow(2, mostSignificantBit(n));
    
    if (n > c)
    {
        c = pow(2, mostSignificantBit(n) + 1);
    }
    
    return c;
}

template <typename K>
class Hashtable{
    enum BucketStatus {EMPTY, OCCUPIED, DELETED};
    
    /// The total number of collisions since the creation of the hashfunction.
    /// This includes the collisions encountered during insertions, searches,
    /// and deletions
    int numCollisions;
    
    /// All the buckets in the hashtable
    // TODO define a list of buckets of type K
    vector<K> buckets;
    
    /// Status of all the buckets
    // TODO define a list of status
    vector<BucketStatus> status;
    
    /// The hash function
    HashFunction<K>* hash;
    
    /// The collision resolution function
    ResolutionFunction* f;
public:
    Hashtable(int n, HashFunction<K>* _h, ResolutionFunction* _f) : numCollisions(0), hash(_h), f(_f) {
		int c = findPrime(n); // Initialize to 150% of the maximum size. This is a bad choice; change it!
		// TODO initialize the buckets and status to the given capacity
		buckets.resize(c);
        status.reisze(c);
    }
    
	void insert(const K& key) {
		// TODO implement the insert function
		unsigned int h = hash->operator()(key) % buckets.size();
        unsigned int x = h;
		unsigned int i = 0;
        
		while (status[x] == OCCUPIED)
		{
			if (buckets[x] == key)
            {
                return;
            }
            
			++numCollisions;
			x = (h + f->operator()(++i)) % buckets.size();
		}

		buckets[x] = key;
		status[x] = OCCUPIED;
	}

	bool search(const K& key) {
		// TODO implement the search function
		unsigned int h = hash->operator()(key) % buckets.size();
		unsigned int i = 0;
		unsigned int x = h;
		
		while (status[x] == OCCUPIED)
		{
			if (buckets[x] == key)
			{
				return true;
			}
			else
			{
			    ++numCollisions;
				x = (h + f->operator()(++i)) % buckets.size();
			}
		}

		return false;
	}

	bool erase(const K& key) {
		// TODO implement the delete function
		unsigned int h = hash->operator()(key) % buckets.size();
        unsigned int x = h;
		unsigned int i = 0;

		while (status[x] == OCCUPIED)
		{
			if (buckets[x] == key)
			{
				status[x] = DELETED;
				return true;
			}
			else
			{
				++numCollisions;
				x = (h + f->operator()(++i)) % buckets.size();
			}
		}

		return false;
	}
    
    int getNumCollisions() const {
        return numCollisions;
    }
};

/// The following code is only for testing. Any changes you make
/// beyond this point will be ignored in the final deliverable

vector<string> loadWords(string filename) {
    ifstream file(filename);
    vector<string> lines;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            // Remove trailing newlines
            while (line[line.size() - 1] == '\r' || line[line.size() - 1] == '\n')
                line = line.substr(0, line.size() - 1);
            lines.push_back(line);
        }
    }
    return lines;
}

void generateRandomPhrases(const vector<string>& words, int numPhrases, vector<string>& phrases) {
    srand(0);
    for (int i = 0; i < numPhrases; i++) {
        string line;
        int length = rand() % 4 + 2; // Generate a random number in [2, 5]
        for (int iWord = 0; iWord < length; iWord++) {
            if (iWord != 0)
                line += " ";
            string word = words[rand() % words.size()];
            line = line + word;
        }
        phrases.push_back(line);
    }
    sort(phrases.begin(), phrases.end());
    int newSize = unique(phrases.begin(), phrases.end()) - phrases.begin();
    phrases.resize(newSize);
    shuffle (phrases.begin(), phrases.end(), std::default_random_engine(0));
}

void testHashtableSimple() {
    HashFunction<string>* hash = new SimpleStringHash();
    ResolutionFunction* f = new LinearProbing();
    Hashtable<string> hashtable = Hashtable<string>(10, hash, f);
    hashtable.insert("first word");
    hashtable.insert("second word");
    hashtable.insert("third word");
    EXPECT_TRUE(hashtable.search("first word"));
    EXPECT_TRUE(hashtable.search("second word"));
    EXPECT_TRUE(hashtable.search("third word"));
    EXPECT_FALSE(hashtable.search("fourth word"));
    EXPECT_TRUE(hashtable.erase("first word"));
    EXPECT_FALSE(hashtable.search("first word"));
    EXPECT_TRUE(hashtable.search("second word"));
    EXPECT_TRUE(hashtable.search("third word"));
    
    delete hash;
    delete f;
}

int stressTest(int hashtableSize) {
    // Load words from file
    vector<string> words = loadWords("1kwords.txt");
    // Generate random phrases
    vector<string> phrases;
    generateRandomPhrases(words, hashtableSize, phrases);

    // Create the hashtable
    HashFunction<string>* hash = new SimpleStringHash();
    ResolutionFunction* f = new LinearProbing();
    // ResolutionFunction* f = new QuadraticProbing();
    Hashtable<string> hashtable = Hashtable<string>(hashtableSize, hash, f);

    
    // Insert all phrases into the hashtable
    for (string phrase : phrases)
        hashtable.insert(phrase);
    // Search for all phrases
    for (string phrase : phrases)
        hashtable.search(phrase);
        
    delete hash;
    delete f;
    // return number of collisions
    return hashtable.getNumCollisions();
}

int main() {
    testHashtableSimple();
    int sizes[] = {100, 1000, 10000, 100000};
    for (int hashtableSize : sizes) {
        int numCollisions = stressTest(hashtableSize);
        cout << "Number of collisions with " << hashtableSize << " phrases is " << numCollisions << endl;
    }
	return 0;
}
