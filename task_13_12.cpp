#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>

#include "CircleMark.h"

class MainWindow final : public QMainWindow
{
public:
    MainWindow()
    {
        cm1 = new CircleMark<double>(/*radius*/50, this);
        cm2 = new CircleMark<long>(/*radius*/50, this);

        cm1->setLimits(/*min*/-100, /*max*/100, /*divider*/10);

        auto* mainPage = new QWidget(this);
        auto* VBox = new QVBoxLayout(mainPage);
        VBox->setSpacing(2);

        VBox->addWidget(cm1);
        VBox->addWidget(cm2);

        setMinimumSize(300,300);
        setCentralWidget(mainPage);
        qApp->installEventFilter(this);
    }

private:
    bool eventFilter(QObject* object, QEvent* event) override
    {
        if(event->type() == QEvent::KeyPress)
        {
            return object->event(event);
        }
        return false;
    }

private:
    CircleMark<double>* cm1;
    CircleMark<long>* cm2;
};



int main(int argc, char *argv[])
{
    QApplication qApplication(argc, argv);

    MainWindow mainWindow;
    mainWindow.resize(500, 500);

    mainWindow.show();
    return QApplication::exec();
}
