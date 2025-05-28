#ifndef BARTASCENECREATOR_H
#define BARTASCENECREATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BartaSceneCreator;
}
QT_END_NAMESPACE

class BartaSceneCreator : public QMainWindow
{
    Q_OBJECT

public:
    BartaSceneCreator(QWidget *parent = nullptr);
    ~BartaSceneCreator();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BartaSceneCreator *ui;
};
#endif // BARTASCENECREATOR_H
