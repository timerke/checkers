#ifndef CHECKER_H
#define CHECKER_H

#include <QGraphicsItemGroup>
#include "cell.h"

enum CheckerType {
    BLACK_CHECKER,
    WHITE_CHECKER
};

/**
 * @brief The Checker class
 * Класс для шашки.
 */
class Checker : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    explicit Checker(CheckerType checker_type);
    ~Checker();
    QPointF get_pos_of_center();
    void handle_click(bool clicked);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void redraw();
    void set_position(Cell *cell);

private:
    QBrush get_brush(int circle_index);
    QPen get_pen(bool selected);

signals:
    void checker_moved(QPointF pos);
    void checker_pressed_or_released(bool pressed, Checker *checker);

public:
    Cell *cell;
    CheckerType checker_type;

private:
    static const int CIRCLES_NUMBER = 3;
    int checker_size;
    QGraphicsEllipseItem *circles[CIRCLES_NUMBER];
};

#endif // CHECKER_H
