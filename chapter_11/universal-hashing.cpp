#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;

struct record
{
    int data;
    struct record *next;
};

/* Implements a hash table using universal hashing technique so as to prevent a bad worst-case runtime
 * for sets of keys that always hash to the same slot when using a single hash function
 */
class HashTable
{
    private:
        const static int word_length = 8;
        int table_size;
        record **table;
        int hash_factor[word_length];
        
    public:
        HashTable(int _table_size) : table_size(_table_size)
        {
            try
            {
                table = new record *[table_size];
                for(int i=0; i<table_size; ++i)
                    table[i] = NULL;
            }
            catch(std::bad_alloc ex)
            {
                cout << "Memory allocation for hash table failed" << endl;
                exit(-1);
            }
            
            generateRandomHashFactor(hash_factor);
            //printHashFactor();
        }
        
        ~HashTable()
        {
            delete[] table;
        }
        
        void generateRandomHashFactor(int *hash_factor)
        {
            srand(time(NULL));
            for(int i=0; i<word_length; ++i)
                hash_factor[i] = rand() % table_size;
        }
        
        /**/
        void insert(int key)
        {
            int key_base_table_size[word_length];
            convertBase(key, key_base_table_size);
            /**
            cout << key << " converted to base " << table_size << endl;
            for(int i=word_length-1; i>=0; --i)
                cout << key_base_table_size[i] << " ";
            cout << endl;
            //*/
            int slot = dotProduct(key_base_table_size, hash_factor) % table_size;
            cout << key << " hashed to slot " << slot << endl;
            copyToSlot(slot, key);
        }
        //*/
        
        record *search(int key)
        {
            int key_base_table_size[word_length];
            convertBase(key, key_base_table_size);
            int slot = dotProduct(key_base_table_size, hash_factor) % table_size;
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
        
        // Converts key into a table_size base number of length word_length
        void convertBase(int key, int *m)
        {
            if(key <= 0)
            {
                cout << "Cannot convert non-positive numbers" << endl;
                exit(-1);
            }
            
            for(int i=0; i<word_length; ++i)
                m[i] = 0;
            int pos = -1;
            while(key > 0)
            {
                m[++pos] = key % table_size;
                key /= table_size;
            }
        }
        
        int dotProduct(int *m1, int *m2)
        {
            int sum = 0;
            for(int i=0; i<word_length; ++i)
                sum += m1[i] * m2[i];
            return sum;
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
        
        void printHashFactor()
        {
            cout << "***Hash factor***" << endl;
            for(int i=word_length-1; i>=0; --i)
                cout << hash_factor[i] << " ";
            cout << endl;
        }
};

int main()
{
    HashTable h(701);
    char choice;
    int num;
    record *r = NULL;
    while(1)
    {
        cout << "Enter i to insert a number into the hash table, s to search the hash table and e to exit: " << endl;
        cin >> choice;
        switch(choice)
        {
            case 'i':
                cout << "Enter number to insert: ";
                cin >> num;
                h.insert(num);
                break;
            case 's':
                cout << "Enter number to search: ";
                cin >> num;
                r = h.search(num);
                if(r != NULL)
                    cout << r->data << " found" << endl;
                else
                    cout << num << " not present in hash table" << endl;
                break;
            case 'e':
                break;
            default:
                cout << "Wrong choice. Try again..." << endl;
                break;
        }
        if(choice == 'e')
            break;
    }
    
    return 1;
}