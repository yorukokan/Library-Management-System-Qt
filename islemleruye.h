/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#ifndef ISLEMLERUYE_H
#define ISLEMLERUYE_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class islemlerUye;
}

class islemlerUye : public QDialog
{
    Q_OBJECT

public:
    explicit islemlerUye(QSqlDatabase database,QWidget *parent = nullptr);
    ~islemlerUye();

    void listele();

private slots:
    void on_pushButton_yenikayituye_clicked();

    void on_tableView_islemleruye_clicked(const QModelIndex &index);

    void on_pushButton_guncelleuye_clicked();

    void on_pushButton_siluye_clicked();

private:
    Ui::islemlerUye *ui;

    QSqlQuery *sorgu;
    QSqlQueryModel *model;
};

#endif // ISLEMLERUYE_H
