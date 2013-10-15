#include <iostream>
#include <new>
#include <cstdlib>
#include <climits>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;

struct record
{
    int data;
    struct record *next;
};

class HashTable
{
    private:
        record **table;
        int index, size;
    public:
        HashTable(int _index) : index(_index)
        {
            size = pow(2, index);
            try
            {
                table = new record *[size];
                for(int i=0; i<size; ++i)
                    table[i] = NULL;
            }
            catch(std::bad_alloc ex)
            {
                cout << "Allocation failure" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        ~HashTable()
        {
            delete[] table;
        }
        
        void insert(int key)
        {
            int slot = hash(key);
            cout << "Hashing to slot " << slot << endl;
            copyToSlot(slot, key);
        }
        
        record *search(int key)
        {
            int slot = hash(key);
            record *r;
            
            while(true)
            {
                r = table[slot];
                if(r == NULL)
                    return NULL;
                if(r->data == key)
                    return r;
                r = r->next;
            }
        }
        
        void copyToSlot(int slot, int key)
        {
            record *r;
            try
            {
                r = new record;
                r->data = key;
            }
            catch(std::bad_alloc ex)
            {
                cout << "Allocation failure when inserting " << key << endl;
                exit(EXIT_FAILURE);
            }
            
            if(table[slot] == NULL)
            {
                r->next = NULL;
                table[slot] = r;
            }
            else
            {
                r->next = table[slot];
                table[slot] = r;
            }
        }
        
        /* Multiplication method to calculate hash of a key.
         */
        int hash(long long key)
        {
            key = abs(key);
            double a = (pow(5, 0.5) - 1)/2;
            cout.precision(20);
            double kamod1 = (key * a) - (long)(key * a);
            long h = (long)(kamod1 * size);
            return h;
        }
        //*/
        
        void printHashTable()
        {
            record *r;
            for(int i=0; i<size; ++i)
            {
                cout << "Index " << i << ":\t";
                r = table[i];
                while(r != NULL)
                {
                    cout << r->data << "\t";
                    r = r->next;
                }
                cout << endl;
            }
        }
};

int main()
{
    int size;
    cout << "Enter x where 2^x is the size of hash table." << endl;
    cin >> size;
    HashTable h(size);
    
    long long num;
    /**/
    while(true)
    {
        cout << "Enter a number (-1 to end): ";
        cin >> num;
        if(num == -1)
            break;
        h.insert(num);
    }
    while(true)
    {
        cout << "Enter key to search (-1 to end):";
        cin >> num;
        if(num == -1)
            break;
        record *r = h.search(num);
        if(r == NULL)
            cout << num << " not found" << endl;
        else
            cout << r->data << endl;
    }
    //*/
    return 1;
}
