#include "roidialog.h"
#include "ui_roidialog.h"

ROIDialog::ROIDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ROIDialog)
{
    ui->setupUi(this);
}

ROIDialog::~ROIDialog()
{
    delete ui;
}

int ROIDialog::labelWidth(int label_id){
    int width = 0;
    switch(label_id){
    case 0:
        width = ui->label_0->width();
        break;
    case 1:
        width = ui->label_1->width();
        break;
    case 2:
        width = ui->label_2->width();
        break;
    case 3:
        width = ui->label_3->width();
        break;
    default:
        break;
    }
    return width;
}

int ROIDialog::labelHeight(int label_id){
    int height = 0;
    switch(label_id){
    case 0:
        height = ui->label_0->height();
        break;
    case 1:
        height = ui->label_1->height();
        break;
    case 2:
        height = ui->label_2->height();
        break;
    case 3:
        height = ui->label_3->height();
        break;
    default:
        break;
    }
    return height;
}

void ROIDialog::setImage(QImage image, int label_id){
    image = image.scaledToHeight(ui->label_0->height());
    switch(label_id){
    case 0:
        ui->label_0->setPixmap(QPixmap::fromImage(image));
        break;
    case 1:
        ui->label_1->setPixmap(QPixmap::fromImage(image));
        break;
    case 2:
        ui->label_2->setPixmap(QPixmap::fromImage(image));
        break;
    case 3:
        ui->label_3->setPixmap(QPixmap::fromImage(image));
        break;
    default:
        break;
    }
}
