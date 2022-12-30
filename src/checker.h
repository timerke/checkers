#ifndef CHECKER_H
#define CHECKER_H
#pragma once

#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include "cell.h"

class Game;

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

    friend class Game;

public:
    explicit Checker(int index, CheckerType checker_type, int checker_variant = 1);
    ~Checker();
    void change_checker_status(bool king, int checker_variant = 0);
    void handle_click(bool clicked);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void redraw();
    void set_position(Cell *cell);

private:
    QString get_file_for_checker();
    QPen get_pen_for_selected_checker();

signals:
    void checker_moved(QPointF pos);
    void checker_pressed_or_released(bool pressed, Checker *checker);

public:
    Cell *cell;
    CheckerType checker_type;
    int index;

private:
    int checker_variant;
    QGraphicsEllipseItem *circle;
    bool king;
    QGraphicsPixmapItem *pixmap_item;
};

#endif // CHECKER_H
