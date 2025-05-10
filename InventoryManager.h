#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include <memory>
#include "Stationery.h"
#include "Transaction.h"

class InventoryManager {
private:
	std::vector<std::shared_ptr<Stationery>> items; // Используем shared_ptr
	std::vector<Transaction> transactions;

public:
	void addItem(const std::shared_ptr<Stationery>& item);
	void restockItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date);
	void sellItem(const std::shared_ptr<Stationery>& item, int quantity, const Date& date);

	// Поиск товара по имени (возвращает nullptr, если не найден)
	std::shared_ptr<Stationery> findItemByName(const std::string& name);

	// Получить список всех товаров
	const std::vector<std::shared_ptr<Stationery>>& getAllItems() const;

	// Отчеты
	void generateSalesReport(const Date& start, const Date& end, const std::string& filename);
	void generateProfitReport(const Date& start, const Date& end, const std::string& filename);
};

#endif