/* Implements a hash table using open addressing which is achieved using the technique of
 * linear probing
 *
 * author: Kunal Sinha
 */

#include <iostream>
#include <new>
#include <cstdlib>
#include <climits>

using std::cout;
using std::cin;
using std::endl;

class HashTable
{
    private:
        int table_size;
        int *table;
        const static int EMPTY = INT_MIN;
    public:
        explicit HashTable(const int _table_size) : table_size(_table_size)
        {
            try
            {
                table = new int[table_size];
            }
            catch(std::bad_alloc ex)
            {
                cout << "Allocation failure" << endl;
                exit(EXIT_FAILURE);
            }
            for(int i=0; i<table_size; ++i)
                table[i] = EMPTY;
        }
        
        ~HashTable()
        {
            if(table)
                delete[] table;
        }
        
        int hash(int key, int probe_number)
        {
            return (auxiliaryHash(key) + probe_number) % table_size;
        }
        
        int auxiliaryHash(int key)
        {
            return key % table_size;
        }
        
        void insert(int key)
        {
            int slot;
            int probe_number;
            for(probe_number=0; probe_number<table_size; ++probe_number)
            {
                slot = hash(key, probe_number);
                cout << "Hashed to slot " << slot << endl;
                if(table[slot] == EMPTY)
                {
                    table[slot] = key;
                    break;
                }
            }
            if(probe_number == table_size)
            {
                cout << "HashTable overflow" << endl;
                exit(EXIT_FAILURE);
            }
        }
        
        void printHashTable()
        {
            for(int i=0; i<table_size; ++i)
                if(table[i] == EMPTY)
                    cout << "Index " << i << ": EMPTY" << endl;
                else
                    cout << "Index " << i << ": " << table[i] << endl;
        }
};

int main()
{
    HashTable h(8);
    int num;
    while(true)
    {
        cout << "Enter a number into the hashtable (-1 to end): ";
        cin >> num;
        if(num == -1)
            break;
        h.insert(num);
    }
    h.printHashTable();
    return 1;
}