/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#include "islemleruye.h"
#include "ui_islemleruye.h"

islemlerUye::islemlerUye(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::islemlerUye)
{
    ui->setupUi(this);
    ui->label_arkaplan->lower();

    sorgu=new QSqlQuery(database);
    listele();
}

islemlerUye::~islemlerUye()
{
    delete ui;
}

// Üye Listeleme fonksiyonu
void islemlerUye::listele()
{
    sorgu->prepare("select * from üye");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye tablosunda bir hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_islemleruye->setModel(model);
}

// Üye Tablosundan bilgi alma fonksiyonu
void islemlerUye::on_tableView_islemleruye_clicked(const QModelIndex &index)
{
    ui->ln_uyeno->setText((model->index(index.row(),0)).data().toString());
    ui->ln_uyead->setText((model->index(index.row(),1)).data().toString());
    ui->ln_uyesoyad->setText((model->index(index.row(),2)).data().toString());
}

// Üye bilgisi güncelleme fonksiyonu
void islemlerUye::on_pushButton_guncelleuye_clicked()
{
    sorgu->prepare("update üye set uye_ad=?, uye_soyad=? where uye_no=?");
    sorgu->addBindValue(ui->ln_uyead->text());
    sorgu->addBindValue(ui->ln_uyesoyad->text());
    sorgu->addBindValue(ui->ln_uyeno->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye güncelleme işleminde bir hata oluştu!");
        return;
    }
    listele();
}

// Yeni üye ekleme fonksiyonu
void islemlerUye::on_pushButton_yenikayituye_clicked()
{
    sorgu->prepare("insert into üye(uye_ad,uye_soyad) values(?,?)");
    if(ui->ln_uyead->text().isEmpty())
    {
        QMessageBox::warning(this,"Hata!","Üye adı boş bırakılamaz!");
    }
    else if(ui->ln_uyesoyad->text().isEmpty())
    {
        QMessageBox::warning(this,"Hata!","Üye soyadı boş bırakılamaz!");
    }
    else
    {
        sorgu->addBindValue(ui->ln_uyead->text());
        sorgu->addBindValue(ui->ln_uyesoyad->text());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Üye kayıt ekleme işleminde bir hata oluştu!");
            return;
        }
    }
    listele();
}

// Üye bilgisi silme fonksiyonu
void islemlerUye::on_pushButton_siluye_clicked()
{
    int teslimKontrol;
    teslimKontrol=ui->ln_uyeno->text().toInt();

    sorgu->prepare("select * from odunc_alinan where uye_no=?");
    sorgu->addBindValue(teslimKontrol);
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Üye silme işleminde bir hata oluştu!");
        return;
    }

    if(sorgu->next())
    {
        QMessageBox::warning(this,"Hata!","Üye silinemez!\nÜyenin teslim edilmeyen kitabı var!");
    }
    else
    {
        sorgu->prepare("delete from üye where uye_no=?");
        sorgu->addBindValue(ui->ln_uyeno->text().toInt());
        if(!sorgu->exec())
        {
            QMessageBox::critical(this,"Hata!","Üye silme işleminde bir hata oluştu!");
            return;
        }
        ui->ln_uyeno->clear();
        ui->ln_uyead->clear();
        ui->ln_uyesoyad->clear();
    }
    listele();
}

