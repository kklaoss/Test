#ifndef STATIONERY_H
#define STATIONERY_H

#include <string>

class Stationery {
protected:
	std::string name;
	double purchasePrice;
	double salePrice;
	int quantity;

public:
	Stationery(const std::string& name, double purchasePrice, double salePrice, int quantity);
	virtual ~Stationery() = default;

	// Виртуальный метод для получения категории
	virtual std::string getCategory() const = 0;

	// Геттеры
	std::string getName() const;
	double getPurchasePrice() const;
	double getSalePrice() const;
	int getQuantity() const;

	void setQuantity(int newQuantity);
};

// Пример категорий
class WritingSupplies : public Stationery {
public:
	WritingSupplies(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

class PaperProducts : public Stationery {
public:
	PaperProducts(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

class OfficeEquipment : public Stationery {
public:
	OfficeEquipment(const std::string& name, double purchasePrice, double salePrice, int quantity);
	std::string getCategory() const override;
};

#endif