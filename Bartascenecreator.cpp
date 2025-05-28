#include "Bartascenecreator.h"
#include "./ui_bartascenecreator.h"
#include <QMessageBox>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

BartaSceneCreator::BartaSceneCreator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BartaSceneCreator)
{
    ui->setupUi(this);
}

BartaSceneCreator::~BartaSceneCreator()
{
    delete ui;
}

void BartaSceneCreator::on_pushButton_clicked()
{
    QMessageBox::information(this, "Hello", QString("Hello" + ui->lineEdit->text()));
}

