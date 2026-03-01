/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <islemleruye.h>
#include <islemlerkitap.h>
#include <islemleroduncalma.h>
#include <islemleroduncteslim.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_uyeislemleri_clicked();

    void on_pushButton_kitapislemleri_clicked();

    void on_pushButton_oduncalmaislemleri_clicked();

    void on_pushButton_oduncteslimetmeislemleri_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase database=QSqlDatabase::addDatabase("QSQLITE");
};
#endif // MAINWINDOW_H
