#ifndef CONNECTION_H
#define CONNECTION_H

#include "common.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QApplication>
#include <QDir>

void showError(const QString &text)
{
    QMessageBox::critical(0, qApp->tr("Ошибка открытия базы данных"),
                          text, QMessageBox::Cancel);
}

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = dbDir + QDir::separator() + dbName;

    QFileInfo checkFile(dbPath);

    if (!checkFile.isFile()) {
        QString err =
                qApp->tr("Ошибка открытия базы данных.\n"
                         "Файл базы данных \'%1\' не существует").arg(dbPath);
        showError(err);
        return false;
    }

    db.setDatabaseName(dbPath);

    if (!db.open()) {
        QString err =
                qApp->tr("Ошибка открытия базы данных \'%1\'\n%2").
                arg(dbPath).arg(db.lastError());
        showError(err);
        return false;
    }
    return true;
}



#endif // CONNECTION_H
