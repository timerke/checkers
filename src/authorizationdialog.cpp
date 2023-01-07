#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QRegExpValidator>
#include "authorizationdialog.h"
#include "./ui_authorizationdialog.h"

/**
 * @brief AuthorizationDialog::AuthorizationDialog
 * Конструктор класса диалогового окна для авторизации.
 */
AuthorizationDialog::AuthorizationDialog() : QDialog(), ui(new Ui::AuthorizationDialog) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/image/icon.png"));

    const QRegExp REG_EXP_FOR_NAME("^[\\w]+$");
    QRegExpValidator *validator_for_name = new QRegExpValidator(REG_EXP_FOR_NAME);
    this->ui->line_edit_name_auth->setValidator(validator_for_name);
    const QRegExp REG_EXP_FOR_PASSWORD("^[\\w!@#\\$%&\\*\\+\\-]+$");
    QRegExpValidator *validator_for_password = new QRegExpValidator(REG_EXP_FOR_PASSWORD);
    this->ui->line_edit_password_auth->setValidator(validator_for_password);
    connect(this->ui->button_cancel_auth, &QPushButton::clicked, this, &AuthorizationDialog::reject);
    connect(this->ui->button_ok_auth, &QPushButton::clicked, this, &AuthorizationDialog::handle_authorise);

    this->ui->line_edit_name_reg->setValidator(validator_for_name);
    this->ui->line_edit_password_reg->setValidator(validator_for_password);
    this->ui->line_edit_password_again_reg->setValidator(validator_for_password);
    connect(this->ui->button_cancel_reg, &QPushButton::clicked, this, &AuthorizationDialog::reject);
    connect(this->ui->button_ok_reg, &QPushButton::clicked, this, &AuthorizationDialog::handle_register);

    this->read_database();
}

/**
 * @brief AuthorizationDialog::~AuthorizationDialog
 * Деструктор класса.
 */
AuthorizationDialog::~AuthorizationDialog() {
    delete this->ui;
}

/**
 * @brief AuthorizationDialog::get_player_name
 * Метод возвращает имя игрока, который авторизовался.
 * @return имя игрока.
 */
QString AuthorizationDialog::get_player_name() {
    QString name;
    if (this->ui->tab_widget->currentWidget() == this->ui->tab_auth) {
        name = this->ui->line_edit_name_auth->text();
    } else {
        name = this->ui->line_edit_name_reg->text();
    }
    qDebug() << "Имя авторизовавшегося игрока: " << name;
    return name;
}

/**
 * @brief AuthorizationDialog::handle_authorise
 * Метод обрабатывает сигнал, что нужно авторизовать игрока.
 */
void AuthorizationDialog::handle_authorise() {
    if (this->ui->line_edit_name_auth->hasAcceptableInput() &&
            this->ui->line_edit_password_auth->hasAcceptableInput()) {
        QString name = this->ui->line_edit_name_auth->text();
        QString password = this->ui->line_edit_password_auth->text();
        auto iterator = this->database.begin();
        while (iterator != this->database.end()) {
            if (name == iterator->name && password == iterator->password) {
                this->accept();
                return;
            } else if (name == iterator->name) {
                qDebug() << "В базе данных зарегистрирован игрок " << name << " с паролем " <<
                            iterator->password << " (попытка войти с паролем " << password <<")";
            }
            iterator++;
        }
        QMessageBox::information(this, "Информация", "Неверный логин или пароль");
    } else {
        QMessageBox::information(this, "Информация", "Введите логин и пароль");
    }
}

/**
 * @brief AuthorizationDialog::handle_register
 * Метод обрабатывает сигнал, что нужно зарегистрировать игрока.
 */
void AuthorizationDialog::handle_register() {
    if (this->ui->line_edit_name_reg->hasAcceptableInput() &&
            this->ui->line_edit_password_reg->hasAcceptableInput() &&
            this->ui->line_edit_password_again_reg->hasAcceptableInput()) {
        QString name = this->ui->line_edit_name_reg->text();
        QString password = this->ui->line_edit_password_reg->text();
        QString password_again = this->ui->line_edit_password_again_reg->text();
        auto iterator = this->database.begin();
        while (iterator != this->database.end()) {
            if (name == iterator->name) {
                QMessageBox::information(this, "Информация", "Игрок с указанным логином уже зарегистрирован. "
                                                             "Придумайте другой логин");
                return;
            }
            iterator++;
        }
        if (password != password_again) {
            qDebug() << "Игрок ввел разные пароли: " << password << " и " << password_again;
            QMessageBox::information(this, "Информация", "Введите одинаковые пароли");
            return;
        }
        PlayerData new_player_data = {name, password};
        this->database.append(new_player_data);
        qDebug() << "Игрок зарегистрирован под логином " << name << " и паролем " << password;
        QMessageBox::information(this, "Информация", "Вы зарегистрированы под логином " + name);
        this->write_database();
        this->accept();
    } else {
        QMessageBox::information(this, "Информация", "Введите логин и два раза пароль");
    }
}

/**
 * @brief AuthorizationDialog::read_database
 * Метод читает данные о зарегистрированных игроках из бинарного файла - базы данных.
 */
void AuthorizationDialog::read_database() {
    QFile database_file(this->DATABASE_NAME);
    if (database_file.open(QIODevice::ReadOnly)) {
        QDataStream stream(&database_file);
        stream.setVersion(QDataStream::Qt_4_6);
        PlayerData data;
        while (!stream.atEnd()) {
            stream >> data.name >> data.password;
            this->database.append(data);
        };
        database_file.close();
        qDebug() << "Из файла " << this->DATABASE_NAME << " получено " << this->database.length() << " записей";
    } else {
        qDebug() << "Не удалось открыть файл " << this->DATABASE_NAME << " с данными авторизации";
        this->database.clear();
    }
}

/**
 * @brief AuthorizationDialog::write_database
 * Метод записывает данные о зарегистрированных игроках в базу данных.
 */
void AuthorizationDialog::write_database() {
    QFile database_file(this->DATABASE_NAME);
    if(database_file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&database_file);
        stream.setVersion(QDataStream::Qt_4_6);
        auto iterator = database.begin();
        while (iterator != database.end()) {
            stream << iterator->name << iterator->password;
            iterator++;
        };
        database_file.close();
        qDebug() << "Успешно записаны данные авторизации в файл " << this->DATABASE_NAME;
    } else {
        qDebug() << "Не удалось открыть файл " << this->DATABASE_NAME << " с данными авторизации";
    }
}
