#include "InMemoryDB.h"

int InMemoryDB::get(string key)
{
    auto it = database.find(key);
    if (it != database.end())
    {
        return it->second;
    }
    else
    {
        // Return a null value if you can't find the key within the database
        return -1;
    }
}
void InMemoryDB::put(string key, int val)
{
    if (!transactionInProgress)
    {
        try
        {
            throw runtime_error("An error occurred!");
        }
        catch (const exception &e)
        {
            cout << "Caught exception: " << e.what() << endl;
        }
        // cout << "Caught exception: An error occurred!" << endl;
    }
    else
    {
        tempDatabase[key] = val;
    }
}
void InMemoryDB::begin_transaction()
{
    if (transactionInProgress == false)
    {
        transactionInProgress = true;
    }
    else
    {
        cout << "Transaction already in progress!" << endl;
    }
}
void InMemoryDB::commit()
{
    // check to see if there's a transaction going on, which there should be for a commit
    if (transactionInProgress)
    {
        // Iterates through the entirety of the temporary database and
        // 1. checks if the key in the temporary database exists in the main database
        // 1.(a) if the key exists, updates it to the new value from the temporary database
        // 1.(b) if the key doesn't exist, add the new key-value pair from the temporary database
        for (auto i = tempDatabase.begin(); i != tempDatabase.end(); i++)
        {
            database[i->first] = i->second;
        }
        // clears the temporary database for a **new** transaction to have a clean database
        // for temporary information
        tempDatabase.clear();
        transactionInProgress = false;
    }
    else
    {
        try
        {
            throw runtime_error("An error occurred!");
        }
        catch (const exception &e)
        {
            cout << "Caught exception: " << e.what() << endl;
        }
    }
}
void InMemoryDB::rollback()
{
    // check to see if there's a transaction going on, which there should be for a rollback
    if (transactionInProgress)
    {
        // clears the temporary database for a **new** transaction to have a clean database
        // for temporary information
        tempDatabase.clear();
        transactionInProgress = false;
    }
    else
    {
        try
        {
            throw runtime_error("An error occurred!");
        }
        catch (const exception &e)
        {
            cout << "Caught exception: " << e.what() << endl;
        }
    }
}