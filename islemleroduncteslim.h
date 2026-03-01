/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#ifndef ISLEMLERODUNCTESLIM_H
#define ISLEMLERODUNCTESLIM_H

#include <QDialog>
#include <QMessageBox>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class islemlerOduncteslim;
}

class islemlerOduncteslim : public QDialog
{
    Q_OBJECT

public:
    explicit islemlerOduncteslim(QSqlDatabase database,QWidget *parent = nullptr);
    ~islemlerOduncteslim();

    int hesapla_borc(QDate oduncalmatarihi);
    void odunckitap_listele();
    void teslimedilenkitap_listele();

private slots:
    void on_tableView_oduncalinankitaplarlistesi_clicked(const QModelIndex &index);

    void on_pushButton_oduncuver_clicked();

private:
    Ui::islemlerOduncteslim *ui;

    QDate oduncalmatarihi;
    int borc_tutari;
    QSqlQuery *sorgu;
    QSqlQueryModel *model,*model1;
};

#endif // ISLEMLERODUNCTESLIM_H
