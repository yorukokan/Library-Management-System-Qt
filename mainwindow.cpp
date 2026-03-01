/*    Ad: Okan
   Soyad: Yörük
      No: 22100011067    */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_arkaplan->lower();

    database.setDatabaseName("22100011067_database.db");
    if(!database.open())
    {
        ui->statusbar->showMessage("Veri tabanı bağlantısı kurulamadı!");
    }
    else
    {
        ui->statusbar->showMessage("Veri tabanı bağlantısı kuruldu.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Üye İşlemleri penceresi
void MainWindow::on_pushButton_uyeislemleri_clicked()
{
    islemlerUye *uye_ekrani=new islemlerUye(database,this);
    uye_ekrani->show();
}

// Kitap İşlemleri penceresi
void MainWindow::on_pushButton_kitapislemleri_clicked()
{
    islemlerKitap *kitap_ekrani=new islemlerKitap(database,this);
    kitap_ekrani->show();
}

// Ödünç Alma İşlemleri penceresi
void MainWindow::on_pushButton_oduncalmaislemleri_clicked()
{
    islemlerOduncAlma *oduncalma_ekrani=new islemlerOduncAlma(database,this);
    oduncalma_ekrani->show();
}

// Ödünç Teslim İşlemleri penceresi
void MainWindow::on_pushButton_oduncteslimetmeislemleri_clicked()
{
    islemlerOduncteslim *oduncteslimetme_ekrani=new islemlerOduncteslim(database,this);
    oduncteslimetme_ekrani->show();
}

