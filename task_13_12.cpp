#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>

#include "CircleMark.h"


class MainWindow : public QMainWindow
{
private:
    CircleMark* cm1;
    CircleMark* cm2;

private:
    bool eventFilter(QObject* object, QEvent* event) override
    {
        if(event->type() == QEvent::KeyPress)
        {
            return object->event(event);
        }

        return false;
    }

public:
    MainWindow()
    {
        cm1 = new CircleMark(/*radius*/50, this);
        cm2 = new CircleMark(/*radius*/50, this);

        auto* mainPage = new QWidget(this);
        auto* VBox = new QVBoxLayout(mainPage);
        VBox->setSpacing(2);

        VBox->addWidget(cm1);
        VBox->addWidget(cm2);

        setMinimumSize(300,300);
        setCentralWidget(mainPage);
        qApp->installEventFilter(this);
    }

};



int main(int argc, char *argv[])
{
    QApplication qApplication(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(300, 300);

    mainWindow.show();
    return QApplication::exec();
}
