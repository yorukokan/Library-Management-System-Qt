/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#include "islemleroduncteslim.h"
#include "ui_islemleroduncteslim.h"

islemlerOduncteslim::islemlerOduncteslim(QSqlDatabase database,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::islemlerOduncteslim)
{
    ui->setupUi(this);
    ui->label_arkaplan->lower();

    sorgu=new QSqlQuery(database);
    odunckitap_listele();
    teslimedilenkitap_listele();
}

islemlerOduncteslim::~islemlerOduncteslim()
{
    delete ui;
}

// Borç hesaplama fonksiyonu
int islemlerOduncteslim::hesapla_borc(QDate oduncalmatarihi)
{
    int gun_sayisi;
    QDate oduncteslimtarihi;

    oduncteslimtarihi=ui->dateEdit_oduncvermetarihi->date();
    gun_sayisi=oduncalmatarihi.daysTo(oduncteslimtarihi);
    if(gun_sayisi>15)
    {
        return 4*(gun_sayisi-15);
    }
    else
    {
        return 0;
    }
}

// Ödünç alınan kitapları listeleme fonksiyonu
void islemlerOduncteslim::odunckitap_listele()
{
    sorgu->prepare("select * from odunc_alinan");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç Alınan tablosunda bir hata oluştu!");
        return;
    }
    model=new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView_oduncalinankitaplarlistesi->setModel(model);
}

// Ödünç Alınan Tablosundan bilgi alma fonksiyonu
void islemlerOduncteslim::on_tableView_oduncalinankitaplarlistesi_clicked(const QModelIndex &index)
{
    QString string_oduncalmatarihi;
    QDate oduncalma_tarihi,oduncteslim_tarihi;

    ui->ln_uyeno->setText((model->index(index.row(),0).data().toString()));
    ui->ln_kitapno->setText((model->index(index.row(),1).data().toString()));

    string_oduncalmatarihi=model->index(index.row(),2).data().toString();
    oduncalma_tarihi=QDate::fromString(string_oduncalmatarihi,"dd.MM.yyyy");
    oduncteslim_tarihi=ui->dateEdit_oduncvermetarihi->date();

    this->oduncalmatarihi=oduncalma_tarihi;
    this->borc_tutari=hesapla_borc(oduncalma_tarihi);
}

// Ödünç teslim edilen kitapları listeleme fonksiyonu
void islemlerOduncteslim::teslimedilenkitap_listele()
{
    sorgu->prepare("select * from odunc_teslim_edilen");
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç Teslim Edilen tablosunda bir hata oluştu!");
        return;
    }
    model1=new QSqlQueryModel();
    model1->setQuery(*sorgu);
    ui->tableView_teslimedilenkitaplarlistesi->setModel(model1);
}

// Ödünç teslim etme fonksiyonu
void islemlerOduncteslim::on_pushButton_oduncuver_clicked()
{
    QString oduncverme_tarihi,oduncalma_tarihi;
    QDate oduncteslim_tarihi;

    oduncteslim_tarihi=ui->dateEdit_oduncvermetarihi->date();
    sorgu->prepare("delete from odunc_alinan where uye_no=? and kitap_no=?");
    sorgu->addBindValue(ui->ln_uyeno->text().toInt());
    sorgu->addBindValue(ui->ln_kitapno->text().toInt());
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç verme işleminde bir hata oluştu!");
        return;
    }
    odunckitap_listele();

    oduncverme_tarihi=ui->dateEdit_oduncvermetarihi->date().toString("dd.MM.yyyy");
    oduncalma_tarihi=oduncalmatarihi.toString("dd.MM.yyyy");
    this->borc_tutari=hesapla_borc(oduncalmatarihi);

    sorgu->prepare("insert into odunc_teslim_edilen(uye_no,kitap_no,alma_tarihi,verme_tarihi,borc) values(?,?,?,?,?)");
    sorgu->addBindValue(ui->ln_uyeno->text().toInt());
    sorgu->addBindValue(ui->ln_kitapno->text().toInt());
    sorgu->addBindValue(oduncalma_tarihi);
    sorgu->addBindValue(oduncverme_tarihi);
    sorgu->addBindValue(borc_tutari);
    if(!sorgu->exec())
    {
        QMessageBox::critical(this,"Hata!","Ödünç verme işleminde bir hata oluştu!");
        return;
    }
    teslimedilenkitap_listele();
}

