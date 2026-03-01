/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#ifndef ISLEMLERODUNCALMA_H
#define ISLEMLERODUNCALMA_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class islemlerOduncAlma;
}

class islemlerOduncAlma : public QDialog
{
    Q_OBJECT

public:
    explicit islemlerOduncAlma(QSqlDatabase database,QWidget *parent = nullptr);
    ~islemlerOduncAlma();

    void kitap_listele();
    void odunckitap_listele();
    void uye_listele();


private slots:
    void on_tableView_tumuyeler_clicked(const QModelIndex &index);

    void on_tableView_tumkitaplar_clicked(const QModelIndex &index);

    void on_pushButton_oduncal_clicked();

private:
    Ui::islemlerOduncAlma *ui;

    QSqlQuery *sorgu;
    QSqlQueryModel *model,*model1,*model2;
};

#endif // ISLEMLERODUNCALMA_H
