/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#include "islemlerkitap.h"
#include "ui_islemlerkitap.h"

islemlerKitap::islemlerKitap(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::islemlerKitap)
{
    ui->setupUi(this);
    ui->label_arkaplan->lower();

    sorgu=new QSqlQuery(database);
    listele();
}

islemlerKitap::~islemlerKitap()
{
    delete ui;
}

// Kitap Tablosundan bilgi alma fonksiyonu
void islemlerKitap::on_tableView_islemlerkitap_clicked(const QModelIndex &index)
{
    ui->ln_kitapno->setText((model->index(index.row(),0)).data().toString());
    ui->ln_kitapad->setText((model->index(index.row(),1)).data().toString());
    ui->ln_stok->setText((model->index(index.row(),2)).data().toString());
    odunc_listele();
    eski_odunc_listele();
}

// Kitap bilgisi silme fonksiyonu
void islemlerKitap::on_pushButton_sil_clicked()
{
    int teslimKontrol;
    teslimKontrol=ui->ln_kitapno->text().toInt();

    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(teslimKontrol);
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitap silme işleminde bir hata oluştu!");
        return;
    }
    if(sorgu->next())
    {
        QMessageBox::critical(this,"Hata!","Kitap silinemez!\nKitap bir üyeye ödünç verilmiş!");
    }
    else
    {
        sorgu->prepare("delete from kitap where kitap_no=?");
        sorgu->addBindValue(ui->ln_kitapno->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Kitap silme işleminde bir hata oluştu!");
            return;
        }
        ui->ln_kitapno->clear();
        ui->ln_kitapad->clear();
        ui->ln_stok->clear();
    }
    listele();
}

// Yeni kitap ekleme fonksiyonu
void islemlerKitap::on_pushButton_yenikayit_clicked()
{
    sorgu->prepare("insert into kitap(kitap_ad,kitap_sayisi) values(?,?)");
    if(ui->ln_kitapad->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Kitap adı boş bırakılamaz!");
    }
    else if(ui->ln_stok->text().isEmpty())
    {
        QMessageBox::critical(this,"Hata!","Kitap sayısı boş bırakılamaz!");
    }
    else
    {
        sorgu->addBindValue(ui->ln_kitapad->text());
        sorgu->addBindValue(ui->ln_stok->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Kitap kayıt ekleme işleminde bir hata oluştu!");
            return;
        }
    }
    listele();
}

// Kitap bilgisi güncelleme fonksiyonu
void islemlerKitap::on_pushButton_guncelle_clicked()
{
    sorgu->prepare("update kitap set kitap_ad=?, kitap_sayisi=? where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitapad->text());
    sorgu->addBindValue(ui->ln_stok->text().toInt());
    sorgu->addBindValue(ui->ln_kitapno->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitap güncelleme işleminde bir hata oluştu!");
        return;
    }
    listele();
}

// Kitap listeleme fonksiyonu
void islemlerKitap::listele()
{
    sorgu->prepare("select * from kitap");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Kitap tablosunda bir hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_islemlerkitap->setModel(model);
}

// Ödünç alınan kitapları listeleme fonksiyonu (Güncel Ödünç)
void islemlerKitap::odunc_listele()
{
    sorgu->prepare("select * from odunc_alinan where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitapno->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç alınan tablosunda bir hata oluştu!");
        return;
    }
    model1=new QSqlQueryModel();
    model1->setQuery(*sorgu);
    ui->tableView_oduncalinmadurumu->setModel(model1);
}

// Ödünç alınan kitapları listeleme fonksiyonu (Eski Ödünç)
void islemlerKitap::eski_odunc_listele()
{
    sorgu->prepare("select * from odunc_teslim_edilen where kitap_no=?");
    sorgu->addBindValue(ui->ln_kitapno->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç teslim tablosunda bir hata oluştu!");
        return;
    }
    model2=new QSqlQueryModel();
    model2->setQuery(*sorgu);
    ui->tableView_dahaoncedenoduncalinmadurumu->setModel(model2);
}
