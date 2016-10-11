#pragma once

#include <map>
#include <string>

class Inventory;

class InventoryHandler
{
public:
	InventoryHandler();
	~InventoryHandler();
	void addInventory(const std::string& inventoryName,int count=1);
	//************************************
	// Method:    addInventory
	// FullName:  InventoryHandler::addInventory
	// Access:    public 
	// Returns:   void
	// Qualifier: ������ inventory ָ��
	// Parameter: Inventory * inventory
	//************************************
	void addInventory(Inventory* inventory,int count=1);
	void removeInventory(std::string inventoryName, int count);
	void removeInventory(int index, int count);
	std::map<std::string, int>& getAllInventory();
	int getCount(const std::string& inventoryName);
	Inventory* getInventory(std::string inventoryName);
	Inventory* getInventory(int index);
protected:
	//��¼ÿ��inventory�ĸ���
	std::map<std::string, int> inventoryBox;
};
