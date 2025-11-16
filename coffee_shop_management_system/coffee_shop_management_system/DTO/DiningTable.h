#ifndef DININGTABLE_H
#define DININGTABLE_H

#include <QString>

class DiningTable {
private:
    int tableId;
    QString name;
    int seats;
    bool isOccupied;

public:
    DiningTable() = default;

    int getTableId() const;
    QString getName() const;
    int getSeats() const;
    bool getIsOccupied() const;

    void setTableId(int id);
    void setName(const QString& n);
    void setSeats(int s);
    void setIsOccupied(bool occ);
};

#endif
