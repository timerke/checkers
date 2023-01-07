#ifndef SELECTIONWIDGET_H
#define SELECTIONWIDGET_H

#include <QGraphicsView>

/**
 * @brief The SelectionWidget class
 * Класс для виджета, содержащего разные варианты выбора и позволяющего прокручивать варианты.
 */
class SelectionWidget : public QGraphicsView {
    Q_OBJECT

public:
    SelectionWidget();
    ~SelectionWidget();
    void add_option();
    void remove_option();
    void scroll_left();
    void scroll_right();

private:
    QGraphicsScene *scene;
};

#endif // SELECTIONWIDGET_H
