#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "field.h"

/**
 * @brief The FieldWidget class
 * Класс для виджета с шашечным полем.
 */
class FieldWidget : public QGraphicsView {
    Q_OBJECT

public:
    FieldWidget();
    ~FieldWidget();
    void set_field(Field *field);

private:
    void resizeEvent(QResizeEvent *event);

private:
    Field *field;
    QGraphicsScene *scene;
};

#endif // FIELDWIDGET_H
