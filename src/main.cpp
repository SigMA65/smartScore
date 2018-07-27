#include "smartScoreWindow/smartScorewindow.h"
#include "common/connection.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
//    char *codecName = "Windows-1251";
    const char *codecName = "UTF-8";

    QTextCodec *codec = QTextCodec::codecForName(codecName);
//    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);

    if (!createConnection())
        return 1;

    MainWindow w;
    w.show();
    
    return a.exec();
}
