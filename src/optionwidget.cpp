#include "optionwidget.h"

/**
 * @brief OptionWidget::OptionWidget
 * Конструктор класса.
 */
OptionWidget::OptionWidget (unsigned int number_of_rows, unsigned int number_of_columns) : QObject(), QGraphicsItemGroup() {
    this->number_of_columns = number_of_columns;
    this->number_of_rows = number_of_rows;
    for (unsigned int row = 0; row < this->number_of_rows; row++) {
        for (unsigned int column = 0; column < this->number_of_columns; column++) {

        }
    }
}

/**
 * @brief OptionWidget::~OptionWidget
 * Деструктор класса.
 */
OptionWidget::~OptionWidget() {

}
