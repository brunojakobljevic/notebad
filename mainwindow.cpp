#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    setWindowTitle("Untitled - Notebad");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
    // brute forcing the color because for some reason it would go back to white
    ui->textEdit->setStyleSheet("background-color:#ffff95"); 
    setWindowTitle("Untitled - Notebad");
}


void MainWindow::on_actionNew_Window_triggered()
{
    QWidget *newWindow = new MainWindow();
    newWindow->move(419,70);
    setWindowTitle("Untitled - Notebad");
    newWindow->show();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", "C:\\Users\\jakob\\Documents\\Notebad text documents"); // opening the file
    QFile file(fileName); // object for reading and writing files
    currentFile = fileName;

    if(!file.open(QIODevice::ReadOnly | QFile::Text)) // opening as read-only and text
    {
        QMessageBox::warning(this, "Warning!", "Cannot open file : " + file.errorString());
        return;
    }

    std::string justName = fileName.toStdString();
    justName = justName.substr(justName.find_last_of("/\\") + 1); // removing the path
    justName = justName + " - Notebad";

    QString qstr = QString::fromStdString(justName);
    setWindowTitle(qstr); // setting the title

    QTextStream input(&file); // interface for text reading
    QString text = input.readAll(); // copying text to string

    ui->textEdit->setText(text); // pasting the text
    // brute forcing the color because for some reason it would go back to white
    ui->textEdit->setStyleSheet("background-color:#ffff95");

    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "C:\\Users\\jakob\\Documents\\Notebad text documents");
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)) // opening as write-only and text
    {
        QMessageBox::warning(this, "Warning!", "Cannot save file : " + file.errorString());
        return;
    }

    std::string justName = fileName.toStdString();
    justName = justName.substr(justName.find_last_of("/\\") + 1); // removing the path
    justName = justName + " - Notebad";

    QString qstr = QString::fromStdString(justName);
    setWindowTitle(qstr);

    currentFile = fileName;

    QTextStream output(&file); // interface for text reading

    QString text = ui->textEdit->toPlainText(); // copying text from text widget
    output << text; // output to file
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_2_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->cut();
}



void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSend_Feedback_triggered()
{
    QString link = "https://github.com/brunojakobljevic";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionAbout_Notebad_triggered()
{
    QMessageBox::about(this, "About Notebad", "Notebad 1.0, 2022.\n\nMade in Qt Creator.\n\nAll rights reserved.");
}



