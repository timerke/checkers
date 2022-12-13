#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

/**
 * @brief The AuthorizationDialog class
 * Класс для диалогового окна авторизации игроков.
 */
class AuthorizationDialog : public QDialog {

public:
    AuthorizationDialog(QString name_of_black_player, QString name_of_white_player);
    ~AuthorizationDialog();
    QString get_black_player_name();
    QString get_white_player_name();

private slots:
    void handle_ok();

private:
    QPushButton *button_cancel;
    QPushButton *button_ok;
    QLineEdit *line_edit_black;
    QLineEdit *line_edit_white;
};

#endif // AUTHORIZATIONDIALOG_H
