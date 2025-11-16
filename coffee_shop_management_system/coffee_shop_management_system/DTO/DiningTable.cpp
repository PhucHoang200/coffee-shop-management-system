#include "DiningTable.h"

int DiningTable::getTableId() const { return tableId; }
QString DiningTable::getName() const { return name; }
int DiningTable::getSeats() const { return seats; }
bool DiningTable::getIsOccupied() const { return isOccupied; }

void DiningTable::setTableId(int id) { tableId = id; }
void DiningTable::setName(const QString& n) { name = n; }
void DiningTable::setSeats(int s) { seats = s; }
void DiningTable::setIsOccupied(bool occ) { isOccupied = occ; }
