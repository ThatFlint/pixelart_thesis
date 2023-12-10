#include <QtWidgets>

#include "mainwindow.h"
#include "drawspace.h"

// MainWindow constructor
MainWindow::MainWindow()
{
    drawSpace = new DrawSpace;
    setCentralWidget(drawSpace);
    createActions();
    createMenus();
    setWindowTitle(tr("Super Cool Pixel Art Tool"));

    resize(500, 500);
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(maybeSave()){
        event -> accept();
    } else {
        event -> ignore();
    }
}

void MainWindow::open(){
    if(maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open File"), QDir::currentPath());
        if(!fileName.isEmpty()){
            drawSpace->openImage(fileName);
        }
    }
}

void MainWindow::save(){
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor1(){
    QColor newColor = QColorDialog::getColor(drawSpace->penColor1());
    if(newColor.isValid()){
        drawSpace->setPenColor1(newColor);
    }
}

void MainWindow::penColor2(){
    QColor newColor = QColorDialog::getColor(drawSpace->penColor2());
    if(newColor.isValid()){
        drawSpace->setPenColor2(newColor);
    }
}

void MainWindow::penSize() {
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Super Cool Pixel Art Tool"),
                                        tr("Select pen size: "),
                                        drawSpace->penSize(),
                                        1,20,1, &ok);
    if(ok){
        drawSpace->setPenSize(newWidth);
    }
}

void MainWindow::drawTool() {
    QString newTool = "drawing";
    drawSpace->setTool(newTool);
}
void MainWindow::lineTool() {
    QString newTool = "line";
    drawSpace->setTool(newTool);
}
void MainWindow::gradientTool() {
    QString newTool = "gradient";
    drawSpace->setTool(newTool);
}

void MainWindow::createActions(){
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    foreach(QByteArray format, QImageWriter::supportedImageFormats()){
        QString text = tr("%1...").arg(QString(format).toUpper());
        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("E%xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));


    QActionGroup *toolGroup = new QActionGroup(this);
    toolGroup->setExclusive(true);

    drawToolAct = new QAction(tr("Draw Tool"), this);
    drawToolAct->setCheckable(true);
    drawToolAct->setChecked(true);
    toolGroup->addAction(drawToolAct);
    connect(drawToolAct, SIGNAL(triggered()), this, SLOT(drawTool()));
    lineToolAct = new QAction(tr("Line Tool"), this);
    lineToolAct->setCheckable(true);
    toolGroup->addAction(lineToolAct);
    connect(lineToolAct, SIGNAL(triggered()), this, SLOT(lineTool()));
    gradientToolAct = new QAction(tr("Gradient Tool"), this);
    gradientToolAct->setCheckable(true);
    toolGroup->addAction(gradientToolAct);
    connect(gradientToolAct, SIGNAL(triggered()), this, SLOT(gradientTool()));

    penColor1Act = new QAction(tr("Pen %Color..."), this);
    connect(penColor1Act, SIGNAL(triggered()), this, SLOT(penColor1()));
    penColor2Act = new QAction(tr("Pen Color %Two..."), this);
    connect(penColor2Act, SIGNAL(triggered()), this, SLOT(penColor2()));
    penSizeAct = new QAction(tr("Pen %Size..."), this);
    connect(penSizeAct, SIGNAL(triggered()), this, SLOT(penSize()));

    clearSpaceAct = new QAction(tr("C%lear Screen"), this);
    clearSpaceAct->setShortcut(tr("Ctrl+L"));
    connect(clearSpaceAct, SIGNAL(triggered()), drawSpace, SLOT(clearImage()));
}

void MainWindow::createMenus(){

    saveAsMenu = new QMenu(tr("%Save As"), this);
    foreach(QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("%File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(exitAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    toolMenu = new QMenu(tr("%Tool"), this);
    toolMenu->addAction(drawToolAct);
    toolMenu->addAction(lineToolAct);
    toolMenu->addAction(gradientToolAct);

    optionMenu = new QMenu(tr("%Options"), this);
    optionMenu->addAction(penColor1Act);
    optionMenu->addAction(penColor2Act);
    optionMenu->addAction(penSizeAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearSpaceAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(toolMenu);
    menuBar()->addMenu(optionMenu);

}

bool MainWindow::maybeSave(){
    if(drawSpace->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Super Cool Pixel Art Tool"),
                                   tr("The image has been modified.\n"
                                      "Save your changes?"),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if(ret == QMessageBox::Save){
            return saveFile("png");
        } else if (ret==QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray &fileFormat){
    QString initialPath = QDir::currentPath() + "/image." + fileFormat;
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                        initialPath,
                                                        tr("%1 Files (*.%2);; All Files(*)")
                                                        .arg(QString::fromLatin1(fileFormat.toUpper()))
                                                        .arg(QString::fromLatin1(fileFormat)));
    if(fileName.isEmpty()){
        return false;
    } else {
        return drawSpace->saveImage(fileName, fileFormat.constData());
    }
}
