#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Stationery.h"
#include "Date.h"
#include <string>

enum class TransactionType { SALE, RESTOCK };

class Transaction {
private:
	Date date;
	TransactionType type;
	Stationery* item;
	int quantity;

public:
	Transaction(const Date& date, TransactionType type, Stationery* item, int quantity);

	// Геттеры
	Date getDate() const;
	TransactionType getType() const;
	Stationery* getItem() const;
	int getQuantity() const;
};

#endif