#ifndef BARTASCENECREATOR_H
#define BARTASCENECREATOR_H

#include <pch.h>
#include "QtComponents/StackElement/JsonStackElement.h"
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

private:
    Ui::BartaSceneCreator* ui;
    std::unique_ptr<Barta::Scene::SceneDocument> sceneDocument;
    std::vector<Barta::QtComponents::StackElement::JsonStackElement*> elementStack;
    std::vector<std::string> tagStack;
    std::unique_ptr<Barta::QtComponents::StackElement::JsonStackElement> sceneElement = nullptr;

    void loadPage2();
    void refreshMiddleColumn();
    void addElementOnStack(Barta::QtComponents::StackElement::JsonStackElement* element);
    void openObjectList(Barta::QtComponents::StackElement::JsonStackElement* element);
    void openForm(Barta::QtComponents::StackElement::JsonStackElement* element);
};
#endif // BARTASCENECREATOR_H
