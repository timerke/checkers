#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsDialog; }
QT_END_NAMESPACE

/**
 * @brief The SettingsDialog class
 * Класс для окна с настройками.
 */
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    SettingsDialog();
    ~SettingsDialog();

private slots:
    void scroll_checkers();
    void scroll_fields();

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
