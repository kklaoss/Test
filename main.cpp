#include <iostream>
#include <limits>
#include <memory>
#include "InventoryManager.h"
#include "Date.h"
#include <cstdlib>
// Прототипы функций
void displayMenu();
Date inputDate();
double inputPositiveDouble(const std::string& prompt);
int inputPositiveInt(const std::string& prompt);

int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "RUS");
	InventoryManager manager;
	int choice = 0;

	do {
		displayMenu();
		std::cin >> choice;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		try {
			switch (choice) {
			case 1: { // Добавить товар
				std::string name;
				int categoryChoice;

				std::cout << "Введите название товара: ";
				std::getline(std::cin, name);

				double pPrice = inputPositiveDouble("Цена закупки: ");
				double sPrice = inputPositiveDouble("Цена продажи: ");
				int qty = inputPositiveInt("Начальное количество: ");

				std::cout << "Выберите категорию:\n"
					<< "1. Письменные принадлежности\n"
					<< "2. Бумажная продукция\n"
					<< "3. Офисная техника\n"
					<< "Ваш выбор: ";
				std::cin >> categoryChoice;

				std::shared_ptr<Stationery> item;
				switch (categoryChoice) {
				case 1:
					item = std::make_shared<WritingSupplies>(name, pPrice, sPrice, qty);
					break;
				case 2:
					item = std::make_shared<PaperProducts>(name, pPrice, sPrice, qty);
					break;
				case 3:
					item = std::make_shared<OfficeEquipment>(name, pPrice, sPrice, qty);
					break;
				default:
					std::cout << "Неверный выбор, товар не добавлен!\n";
					continue;
				}

				manager.addItem(item);
				std::cout << "Товар добавлен!\n";
				break;
			}
			case 2: { // Просмотреть все товары
				const auto& items = manager.getAllItems();
				if (items.empty()) {
					std::cout << "Список товаров пуст.\n";
					break;
				}
				std::cout << "\nСписок товаров:\n";
				for (const auto& item : items) {
					std::cout << "Название: " << item->getName()
						<< ", Цена закупки: " << item->getPurchasePrice()
						<< ", Цена продажи: " << item->getSalePrice()
						<< ", Количество: " << item->getQuantity() << "\n";
				}
				break;
			}
			case 3: { // Пополнить запас
				std::string name;
				std::cout << "Введите название товара: ";
				std::getline(std::cin, name);

				auto item = manager.findItemByName(name);
				if (!item) {
					std::cout << "Товар не найден!\n";
					break;
				}

				int quantity = inputPositiveInt("Введите количество для пополнения: ");
				Date date = inputDate();
				manager.restockItem(item, quantity, date);
				std::cout << "Товар пополнен!\n";
				break;
			}
			case 4: { // Продать товар
				std::string name;
				std::cout << "Введите название товара: ";
				std::getline(std::cin, name);

				auto item = manager.findItemByName(name);
				if (!item) {
					std::cout << "Товар не найден!\n";
					break;
				}

				int quantity = inputPositiveInt("Введите количество для продажи: ");
				Date date = inputDate();
				manager.sellItem(item, quantity, date);
				std::cout << "Продажа оформлена!\n";
				break;
			}
			case 5: // Отчет по продажам
			case 6: { // Отчет по прибыли
				Date start = inputDate();
				Date end = inputDate();
				std::string filename;
				std::cout << "Введите имя файла для отчета: ";
				std::getline(std::cin, filename);

				if (choice == 5) {
					manager.generateSalesReport(start, end, filename);
				}
				else {
					manager.generateProfitReport(start, end, filename);
				}
				std::cout << "Отчет сохранен в " << filename << "!\n";
				break;
			}
			case 7: // Выход
				std::cout << "До свидания!\n";
				break;
			default:
				std::cout << "Неверный выбор. Попробуйте снова.\n";
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Ошибка: " << e.what() << "\n";
		}
	} while (choice != 7);

	return 0;
}

// Функция отображения меню
void displayMenu() {
	std::cout << "\n=== Меню управления ===\n"
		<< "1. Добавить новый товар\n"
		<< "2. Просмотреть все товары\n"
		<< "3. Пополнить запас товара\n"
		<< "4. Продать товар\n"
		<< "5. Сгенерировать отчет по продажам\n"
		<< "6. Сгенерировать отчет по прибыли\n"
		<< "7. Выход\n"
		<< "Выберите действие: ";
}

// Ввод даты с проверкой
Date inputDate() {
	int d, m, y;
	while (true) {
		std::cout << "Введите дату (дд мм гггг): ";
		std::cin >> d >> m >> y;
		if (std::cin.fail() || !Date(d, m, y).isValid()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Некорректная дата! Попробуйте снова.\n";
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
	}
	return Date(d, m, y);
}

// Ввод положительного числа (double)
double inputPositiveDouble(const std::string& prompt) {
	double value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "Число должно быть положительным! Попробуйте снова.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return value;
}

// Ввод положительного целого числа
int inputPositiveInt(const std::string& prompt) {
	int value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;
		if (value > 0) break;
		std::cout << "Число должно быть положительным! Попробуйте снова.\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return value;
}