#ifndef CELL_H
#define CELL_H

#include <QBrush>
#include <QGraphicsRectItem>

enum CellType {
    BLACK_CELL,
    WHITE_CELL
};

/**
 * @brief The Cell class
 * Класс для ячейки шашечной доски.
 */
class Cell : public QGraphicsRectItem {

public:
    Cell(int row, int column);
    ~Cell();
    bool check_black();
    bool check_pos_in_cell(QPointF pos);
    void deselect_cell_for_move();
    void select_cell_for_move();

private:
    QBrush get_brush_for_cell();
    CellType get_cell_type(int row, int column);

public:
    CellType cell_type;
    int column;
    int row;
};

#endif // CELL_H
