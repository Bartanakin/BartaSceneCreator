#ifndef BARTASCENECREATOR_H
#define BARTASCENECREATOR_H

#include <pch.h>
#include "include/CustomWidgets/JsonStackElement.h"
#include "Scene/SceneDocument.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class BartaSceneCreator;
}

QT_END_NAMESPACE

class BartaSceneCreator: public QMainWindow {
    Q_OBJECT

public:
    BartaSceneCreator(QWidget* parent = nullptr);
    ~BartaSceneCreator();

private slots:
    void on_add_scene_button_clicked();
    void on_save_button_clicked();
    void on_edit_scene_button_clicked();

signals:
    void refreshForm();

private:
    Ui::BartaSceneCreator* ui;
    std::unique_ptr<Barta::Scene::SceneDocument> sceneDocument;
    std::vector<Barta::QtComponents::StackElement::JsonStackElement*> elementStack;
    std::vector<std::string> hashStack;
    std::unique_ptr<Barta::QtComponents::StackElement::JsonStackElement> sceneElement = nullptr;
    Barta::QtComponents::Form::FormInterface* currentForm = nullptr;
    QVBoxLayout* formLayout = nullptr;
    bool isListOpen = false;

    void loadPage2();
    void refreshMiddleColumn();
    void addElementOnStack(Barta::QtComponents::StackElement::JsonStackElement* element);
    void openObjectList(Barta::QtComponents::StackElement::JsonStackElement* element);
    void openForm(Barta::QtComponents::StackElement::JsonStackElement* element);
};
#endif // BARTASCENECREATOR_H
