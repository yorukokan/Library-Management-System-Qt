/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#ifndef ISLEMLERKITAP_H
#define ISLEMLERKITAP_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class islemlerKitap;
}

class islemlerKitap : public QDialog
{
    Q_OBJECT

public:
    explicit islemlerKitap(QSqlDatabase database,QWidget *parent = nullptr);
    ~islemlerKitap();

    void listele();
    void odunc_listele();
    void eski_odunc_listele();

private slots:
    void on_tableView_islemlerkitap_clicked(const QModelIndex &index);

    void on_pushButton_yenikayit_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::islemlerKitap *ui;

    QSqlQuery *sorgu;
    QSqlQueryModel *model,*model1,*model2;


};

#endif // ISLEMLERKITAP_H
