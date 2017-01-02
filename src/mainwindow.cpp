#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//This function opens up a file dialog, which prompts the user to select an image from their disk space,
//and loads the chosen picture in the main window
void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Choose An Image"),
                                                    ".",
                                                    tr("Image Files (*.png *.jpg)"));
    QPixmap image(fileName);
    ui->imageLabel->setFixedHeight(image.height());
    ui->imageLabel->setFixedWidth(image.width());
    ui->imageLabel->setPixmap(image);
}

//This function's purpose is to call the function that applies the filtering matrix's values to the loaded image,
//in other words filters the image, when the Filter button is clicked
void MainWindow::on_filterButton_clicked()
{
    ImageSharpener::setFilterArray(ui->cell_y0_x0->value(), ui->cell_y0_x1->value(), ui->cell_y0_x2->value(),
                                   ui->cell_y1_x0->value(), ui->cell_y1_x1->value(), ui->cell_y1_x2->value(),
                                   ui->cell_y2_x0->value(), ui->cell_y2_x1->value(), ui->cell_y2_x2->value());
    ui->imageLabel->setPixmap(ImageSharpener::filterImage(ui->imageLabel->pixmap()));
}
