#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "huffman.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rawText_textChanged()
{
    ui->codeText->setText(QString::fromStdString(HuffmanTree::encode(ui->rawText->toPlainText().toStdString().c_str())));
}

void MainWindow::on_codeText_textChanged()
{
    ui->backText->setText(QString::fromStdString(HuffmanTree::decode(ui->codeText->toPlainText().toStdString().c_str())));
}
