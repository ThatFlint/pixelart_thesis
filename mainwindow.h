#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>

class DrawSpace;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;


protected slots:
    void open();
    void save();
    void penColor1();
    void penColor2();
    void penSize();

//    void drawTool();
//    void lineTool();
//    void gradientTool();

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);
    DrawSpace *drawSpace;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QMenu *saveAsMenu;
    QMenu *optionMenu;
    QAction *openAct;
    QList<QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColor1Act;
    QAction *penColor2Act;
    QAction *penSizeAct;
    QAction *clearSpaceAct;

    QActionGroup *toolGroup;
    QAction *drawToolAct;
    QAction *lineToolAct;
    QAction *gradientToolAct;

};

#endif // MAINWINDOW_H
