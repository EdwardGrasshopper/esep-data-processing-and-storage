#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class InMemoryDB
{
    bool transactionInProgress = false;
    unordered_map<string, int> database;
    unordered_map<string, int> tempDatabase;

public:
    int get(string key);
    void put(string key, int val);
    void begin_transaction();
    void commit();
    void rollback();
};