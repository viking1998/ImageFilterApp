#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include "imagesharpener.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_filterButton_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_changeFilteringButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
