#include "mainwindow.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    QScreen *screen = QApplication::primaryScreen();

    if(screen){
        QSize screen_size = screen->size();

        int width = screen_size.width() * 0.9;
        int height = screen_size.height() * 0.9;

        window.resize(width, height);

        window.move(
            (screen_size.width() - width) / 2,
            (screen_size.height() - height) / 2
        );
    }

    window.setWindowTitle("Bodybuilder's Diary");

    window.show();

    return app.exec();
}
