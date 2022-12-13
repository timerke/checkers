#ifndef AUTHORIZATIONDIALOG_H
#define AUTHORIZATIONDIALOG_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "checker.h"

/**
 * @brief The Anonymous:1 struct
 * Структура для хранения логина и пароля игрока.
 */
struct {
    QString name;
    QString password;
} typedef PlayerData;

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

/**
 * @brief The AuthorizationDialog class
 * Класс для диалогового окна авторизации игроков.
 */
class AuthorizationDialog : public QDialog {
    Q_OBJECT

public:
    AuthorizationDialog(CheckerType checker_type);
    ~AuthorizationDialog();
    CheckerType get_checker_type();
    QString get_player_name();

private:
    void read_database();
    void write_database();

private slots:
    void handle_authorise();
    void handle_register();

private:
    const QString DATABASE_NAME = "auth";
    CheckerType checker_type;
    QVector<PlayerData> database;
    Ui::Dialog *ui;
};

#endif // AUTHORIZATIONDIALOG_H
