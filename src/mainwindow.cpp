#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filterMatrix->hide();
    ui->filterButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//This function's purpose is to call the function that applies the filtering matrix's values to the loaded image,
//in other words filters the image, when the Filter button is clicked
void MainWindow::on_filterButton_clicked()
{
    if(ui->filterDropdown->isEnabled()) {
        switch(ui->filterDropdown->currentIndex()) {
            case 0:
                ImageSharpener::setFilterArray( 0,  0.2,  0,
                                               0.2, 0.2, 0.2,
                                                0,  0.2,  0);
                break;

            case 1:
                ImageSharpener::setFilterArray( 0.339, 0, 0,
                                                 0, 0.339, 0,
                                                 0, 0, 0.339);
                break;

            case 2:
                ImageSharpener::setFilterArray( -1, -1, 0,
                                                -1,  0, 1,
                                                 0,  1, 1);
                break;

            case 3:
                ImageSharpener::setFilterArray( -1, -1, -1,
                                                -1,  9, -1,
                                                -1, -1, -1);
                break;

            case 4:
                ImageSharpener::setFilterArray( 0, -2, 0,
                                                0,  2, 0,
                                                0,  0, 0);
                break;

            case 5:
                ImageSharpener::setFilterArray( 0, -1, 0,
                                                0,  2, 0,
                                                0, -1, 0);
                break;

            case 6:
                ImageSharpener::setFilterArray( -1,  0,  0,
                                                 0,  2,  0,
                                                 0,  0, -1);
                break;

            case 7:
                ImageSharpener::setFilterArray( -1, -1, -1,
                                                -1,  8, -1,
                                                -1, -1, -1);
        }
    }
    else {
        ImageSharpener::setFilterArray(ui->cell_y0_x0->text().toFloat(), ui->cell_y0_x1->text().toFloat(), ui->cell_y0_x2->text().toFloat(),
                                       ui->cell_y1_x0->text().toFloat(), ui->cell_y1_x1->text().toFloat(), ui->cell_y1_x2->text().toFloat(),
                                       ui->cell_y2_x0->text().toFloat(), ui->cell_y2_x1->text().toFloat(), ui->cell_y2_x2->text().toFloat());
    }
    ui->imageLabel->setPixmap(ImageSharpener::filterImage(ui->imageLabel->pixmap()));
}


//This function opens up a file dialog, which prompts the user to select an image from their disk space,
//and loads the chosen picture in the main window
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Choose An Image"),
                                                    ".",
                                                    tr("Image Files (*.png *.jpg)"));
    if(!fileName.isNull()) {
        ui->filterButton->setEnabled(true);
        QPixmap image(fileName);
        ui->imageLabel->setFixedHeight(image.height());
        ui->imageLabel->setFixedWidth(image.width());
        ui->imageLabel->setPixmap(image);
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "./untitled.png",
                               tr("PNG images (*.png);;JPEG/JPG images (*.jpg *.jpeg);;Any Files (*)"));
    QImage saveImage(ui->imageLabel->pixmap()->toImage());
    saveImage.save(fileName);
}

void MainWindow::on_changeFilteringButton_clicked()
{
    ui->filterDropdown->setEnabled(!ui->filterDropdown->isEnabled());
    if(ui->filterMatrix->isHidden()) {
        ui->filterMatrix->show();
        ui->changeFilteringButton->setText("Use predefined filters");
    }
    else {
        ui->filterMatrix->hide();
        ui->changeFilteringButton->setText("Use custom filters");
    }
}
