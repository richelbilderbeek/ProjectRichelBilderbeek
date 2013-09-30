#include "dialog.h"
#include "ui_dialog.h"
#include <QFileDialog>
#include "fstream"


#include "cs2_encrypt.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_pbSelIF_clicked()
{
    ui->lineSelIF->setText(QFileDialog::getOpenFileName());
}

void Dialog::on_pbSelOF_clicked()
{
    ui->lineSelOF->setText(QFileDialog::getOpenFileName());
}

void Dialog::on_pbEncrypt_clicked()
{
    cerr << "Button pressed \n";
    // open files
    ifstream iFile; ofstream oFile;
    iFile.open(ui->lineSelIF->text().toStdString().c_str(),ios::binary);
    oFile.open(ui->lineSelOF->text().toStdString().c_str(),ios::binary);

    if (!iFile.is_open()||!oFile.is_open()){
        cerr << "Unable to open files.\n";
        return;
    }

    // Lookup file size
    iFile.seekg(0, std::ios_base::end);
    int fileSize = iFile.tellg();
    iFile.seekg(0, std::ios_base::beg);

    // Encrypt inputfile
    cs2_encrypt(iFile,
                oFile,
                (unsigned char*)(ui->lineUserkey->text().toStdString().c_str()),
                ui->lineUserkey->text().toStdString().length(),
                ui->spinN->value(),
                fileSize);
}

void Dialog::on_pbDecrypt_clicked()
{
    // open files
    ifstream iFile; ofstream oFile;
    iFile.open(ui->lineSelIF->text().toStdString().c_str(),ios::binary);
    oFile.open(ui->lineSelOF->text().toStdString().c_str(),ios::binary);

    if (!iFile.is_open()||!oFile.is_open()){
        cerr << "Unable to open files.\n";
        return;
    }

    // Lookup file size
    iFile.seekg(0, std::ios_base::end);
    int fileSize = iFile.tellg();
    iFile.seekg(0, std::ios_base::beg);

    // Decrypt outputfile
    cs2_decrypt(iFile,
                oFile,
                (unsigned char*)(ui->lineUserkey->text().toStdString().c_str()),
                ui->lineUserkey->text().toStdString().length(),
                ui->spinN->value(),
                fileSize);
}
