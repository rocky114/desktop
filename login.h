#ifndef LOGIN_H
#define LOGIN_H

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include "filesystem.h"
#include "mysql.h"

class Login : public QObject
{
    Q_OBJECT

public:
    explicit Login(QObject *parent = nullptr);
    ~Login();
    QWidget *setLoginUi();
    QWidget *setListWidget();

    QLineEdit *name;
    QLineEdit *host;
    QLineEdit *port;
    QLineEdit *username;
    QLineEdit *password;
    QLineEdit *database;
    QPushButton *buttonConnect;
    FileSystem *fileHandle;

signals:
    void reloadCentralWidget();

public slots:
    void acceptLogin();
    void singleClicked(QListWidgetItem *item);
    void doubleClicked(QListWidgetItem *item);
};

#endif // LOGIN_H
