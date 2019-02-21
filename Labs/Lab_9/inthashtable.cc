#include <iostream>
#include <gtest/gtest.h>
#include <iomanip>
#include <math.h>
#include <random>

using namespace std;

/// Returns the bit index of the most significant bit.
/// If the input is zero, it returns zero
int mostSignificantBit(int x) {
    if (x == 0)
        return 0;
    int mostSignificantBit = 31;
    while ((x & (1 << mostSignificantBit)) == 0)
        mostSignificantBit--;
    return mostSignificantBit;
}

/// Good prime numbers to use as Hashtable sizes
int GoodPrimeNumbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
    24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
    12582917, 25165843, 50331653, 100663319, 201326611, 402653189,
    805306457, 1610612741
};

class Hashtable{
    enum BucketStatus {EMPTY, OCCUPIED, DELETED};
    
    /// The total number of collisions since the creation of the hashfunction.
    /// This includes the collisions encountered during insertions, searches,
    /// and deletions
    int numCollisions;
    
    /// Capacity of the hashtable
    int c;
    
    /// Current size
    int size;
    
    /// All the buckets in the hashtable
    vector<unsigned int> buckets;
    
    /// Status of all the buckets
    vector<BucketStatus> status;
    
    /// Find next prime
    void nextPrime()
    {
        for (int i = 0; i < sizeof(GoodPrimeNumbers) / sizeof(GoodPrimeNumbers[0]); ++i)
        {
            if (GoodPrimeNumbers[i] == c)
            {
                c = GoodPrimeNumbers[i + 1];
                break;
            }
        }
    }
    
    /// Adjusts the capacity of the hashtable and rehashes
    void expandAndRehash(int &counter) {
        // TODO
        ++counter;
        
        nextPrime();
        
        vector<unsigned int> tempBuckets(c);
        vector<BucketStatus> tempStatus(c);
        
        tempBuckets.swap(buckets), tempStatus.swap(status);
        
        size = 0;
        
        for (int i = 0; i < tempBuckets.size(); ++i)
        {
            insert(tempBuckets.at(i), counter);
        }
    }
    
public:
    Hashtable(int n) : numCollisions(0), size(0){
        // Initialize the hashtable to a good prime number whose most significant bit is at a higher index than n
        int msb = mostSignificantBit(n);
        c = GoodPrimeNumbers[msb <= 4 ? 0 : msb - 4];
        buckets.resize(c);
        status.resize(c);
    }
    
    ~Hashtable() {
    }
    
    unsigned int hash(unsigned int key) {
        // See https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
        return key*2654435761;
    }
    
    /// Tries to insert the given key into the hashtable.
    /// Returns true if the element was inserted and false if not.
    /// The insertion will fail if the element already exists in the input.
    bool insert(unsigned int key, int &counter) {
        float a = static_cast<float>(size) / static_cast<float>(buckets.size());
        
        if (a >= 0.5)
        {
            expandAndRehash(counter);  
        }
       
        unsigned int h = hash(key) % c;
        unsigned int i = 0;
        unsigned int hi = h;
        while (status[hi] == OCCUPIED) {
            if (buckets[hi] == key)
                return false; // Key already exists
            numCollisions++;
            ++i;
            hi = (h + i) % c;
        }
        status[hi] = OCCUPIED;
        buckets[hi] = key;
        ++size;
        
        return true; // Key inserted successfully
    }
    
    bool search(unsigned int key) {
        unsigned int h = hash(key) % c;
        unsigned int i = 0;
        unsigned int hi = h;
        while (status[hi] != EMPTY) {
            if (status[hi] == OCCUPIED && buckets[hi] == key) {
                // Key found
                return true;
            }
            numCollisions++;
            ++i;
            hi = (h + i) % c;
        }
        // Key not found. Hit an empty bucket.
        return false;
    }
    
    bool erase(unsigned int key) {
        unsigned int h = hash(key) % c;
        unsigned int i = 0;
        unsigned int hi = h;
        while (status[hi] != EMPTY) {
            if (status[hi] == OCCUPIED && buckets[hi] == key) {
                // Key found, delete it.
                status[hi] = DELETED;
                --size;
                return true;
            }
            numCollisions++;
            ++i;
            hi = (h + i) % c;
        }
        // Key not found an hit an empty bucket.
        return false;
    }

    int getNumCollisions() const {
        return numCollisions;
    }
};

void generate_random_numbers(vector<unsigned int>& values) {
    cout << "Generating random numbers ...";
    for (int i = 0; i < values.size(); i++) {
		values[i] = (rand() % 31 + 1) + ((rand() % 12 + 1) * 100) + (rand() % 100 + 2000) * 10000;
	}
	cout << " Done!" << endl;
}


void testHashtable(Hashtable& hashtable, int n, int &counter) {
    // Generate a set of random numbers
    vector<unsigned int> values;
    values.resize(n);
    generate_random_numbers(values);
    
    // Insert all values into the hashtable
    int count = 0;
    for (int x : values) {
        if (hashtable.insert(x, counter))
            count++;
    }
    
    cout << "Number of rehashes for " << n << " elements: " << counter << endl;
    cout << "Number of collisions after " << count << " successful insertions: " << hashtable.getNumCollisions() << endl;
    
    // Search for all values in the hashtable
    for (int x : values) {
        EXPECT_TRUE(hashtable.search(x));
    }
    
    cout << "Number of collisions after " << n << " searches: " << hashtable.getNumCollisions() << endl;
    
    // Delete all the elements
    for (int x : values) {
        hashtable.erase(x);
    }
    
    cout << "Number of collisions after " << count << " deletions: " << hashtable.getNumCollisions() << endl;
}

int main() {
    int sizes[] = {100, 1000, 10000};
    for (int hashtableSize : sizes) {
        int counter = 0;
        Hashtable hashtable(10);
        testHashtable(hashtable, hashtableSize, counter);
    }
	
	return 0;
}