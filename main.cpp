#include "InMemoryDB.h"
#include <string>
#include <iostream>

int main()
{
    InMemoryDB bankDB;

    // should return null, because A doesn't exist in the DB yet
    int result = bankDB.get("A");
    cout << "step 1's result is: " << result << endl;
    cout << "and should return: null" << endl;

    // should throw an error because a transaction is not in progress
    cout << "step 2: " << endl;
    bankDB.put("A", 5);
    cout << "should throw an error" << endl;

    bankDB.begin_transaction();

    // set’s value of A to 5, but its not committed yet
    bankDB.put("A", 5);

    // should return null, because updates to A are not committed yet
    result = bankDB.get("A");
    cout << "step 3's result is: " << result << endl;
    cout << "and should return: null" << endl;

    // update A’s value to 6 within the transaction
    bankDB.put("A", 6);

    // commits the open transaction
    bankDB.commit();

    // should return 6, that was the last value of A to be committed
    result = bankDB.get("A");
    cout << "step 4's result is: " << result << endl;
    cout << "and should return: 6" << endl;

    // throws an error, because there is no open transaction
    bankDB.commit();
    cout << "should throw an error" << endl;

    // throws an error because there is no ongoing transaction
    bankDB.rollback();
    cout << "should throw an error" << endl;

    // should return null because B does not exist in the database
    result = bankDB.get("B");
    cout << "step 5's result is: " << result << endl;
    cout << "and should return: null" << endl;

    // starts a new transaction
    bankDB.begin_transaction();

    // Set key B’s value to 10 within the transaction
    bankDB.put("B", 10);

    // Rollback the transaction - revert any changes made to B
    bankDB.rollback();

    // Should return null because changes to B were rolled back
    result = bankDB.get("B");
    cout << "step 6's result is: " << result << endl;
    cout << "and should return: null" << endl;

    return 0;
}