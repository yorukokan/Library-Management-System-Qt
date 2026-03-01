/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#include "islemleroduncalma.h"
#include "ui_islemleroduncalma.h"

islemlerOduncAlma::islemlerOduncAlma(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::islemlerOduncAlma)
{
    ui->setupUi(this);
    ui->label_arkaplan->lower();

    sorgu=new QSqlQuery(database);
    kitap_listele();
    odunckitap_listele();
    uye_listele();
}

islemlerOduncAlma::~islemlerOduncAlma()
{
    delete ui;
}

// Kitapları listeleme fonksiyonu
void islemlerOduncAlma::kitap_listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitap tablosunda bir hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_tumkitaplar->setModel(model);
}

// Ödünç kitapları listeleme fonksiyonu
void islemlerOduncAlma::odunckitap_listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç Alınan tablosunda bir hata oluştu!");
        return;
    }
    model1=new QSqlQueryModel();
    model1->setQuery(*sorgu);
    ui->tableView_oduncalinankitaplar->setModel(model1);
}

// Üye listeleme fonksiyonu
void islemlerOduncAlma::uye_listele()
{
    sorgu->prepare("select * from üye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye tablosunda bir hata oluştu!");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_tumuyeler->setModel(model2);
}

// Üye Tablosundan bilgi alma fonksiyonu
void islemlerOduncAlma::on_tableView_tumuyeler_clicked(const QModelIndex &index)
{
    ui->ln_uyeno->setText((model2->index(index.row(),0).data().toString()));
}

// Kitap Tablosundan bilgi alma fonksiyonuT
void islemlerOduncAlma::on_tableView_tumkitaplar_clicked(const QModelIndex &index)
{
    ui->ln_kitapno->setText((model->index(index.row(),0).data().toString()));

}

// Ödünç Alma fonksiyonu
void islemlerOduncAlma::on_pushButton_oduncal_clicked()
{
    if(ui->ln_uyeno->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Üye no boş bırakılamaz!");
    }
    else if(ui->ln_kitapno->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Kitap no boş bırakılamaz!");
    }
    else
    {
        sorgu->prepare("select * from odunc_alinan where uye_no=? and kitap_no=?");
        sorgu->addBindValue(ui->ln_uyeno->text().toInt());
        sorgu->addBindValue(ui->ln_kitapno->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Ödünç Alma tablosunda bir hata oluştu!");
        }
        else if(sorgu->next())
        {
            QMessageBox::information(this,"Hata!","Bu kitap daha önce ödünç alınmış.\nTekrar ödünç alınamaz!");
        }
        else
        {
            sorgu->prepare("insert into odunc_alinan(uye_no,kitap_no,odunc_alma_tarihi) values(?,?,?)");
            sorgu->addBindValue(ui->ln_uyeno->text().toInt());
            sorgu->addBindValue(ui->ln_kitapno->text().toInt());
            sorgu->addBindValue(ui->dateEdit_oduncalma->text());
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata!","Ödünç Alma tablosunda bir hata oluştu!");
                return;
            }
            sorgu->prepare("update kitap set kitap_sayisi=kitap_sayisi-1 where kitap_no=?");
            sorgu->addBindValue(ui->ln_kitapno->text().toInt());
            if(!sorgu->exec())
            {
                QMessageBox::critical(this,"Hata!","Kitap tablosunda bir hata oluştu!");
                return;
            }
        }
    }
    odunckitap_listele();
    kitap_listele();
}

