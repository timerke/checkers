#ifndef FIELD_H
#define FIELD_H

#include <QBrush>
#include <QGraphicsView>
#include <QPen>
#include <QVector>
#include "cell.h"
#include "checker.h"

/**
 * @brief The Field class
 * Класс для шашечного поля.
 */
class Field : public QGraphicsView {
    Q_OBJECT

public:
    Field();
    ~Field();
    bool check_empty_cell(Cell *cell);
    Cell * find_cell_at_pos(QPointF &pos);
    Checker ** get_black_checkers();
    Cell * get_cell(int row, int column);
    Checker ** get_white_checkers();
    void set_checkers_to_init_pos(int checker_variant);

private:
    void create_cells();
    void create_checkers(CheckerType checker_type, Checker **checkers);
    void draw_cells();
    void draw_checkers();
    void resizeEvent(QResizeEvent *event);

public:
    static const int CHECKERS_NUMBER = 12;

private:
    static const int CELLS_NUMBER = 8;
    Checker *black_checkers[CHECKERS_NUMBER];
    int cell_size;
    Cell *cells[CELLS_NUMBER][CELLS_NUMBER];
    QGraphicsScene *scene;
    Checker *white_checkers[CHECKERS_NUMBER];
};

#endif // FIELD_H
