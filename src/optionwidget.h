#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QGraphicsItemGroup>

/**
 * @brief The OptionWidget class
 * Класс для виджета с опцией выбора.
 */
class OptionWidget : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    OptionWidget(unsigned int number_of_rows, unsigned int number_of_columns);
    ~OptionWidget();

private:
    unsigned int number_of_columns;
    unsigned int number_of_rows;
};

#endif // OPTIONWIDGET_H
