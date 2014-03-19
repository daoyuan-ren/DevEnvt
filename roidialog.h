#ifndef ROIDIALOG_H
#define ROIDIALOG_H

#include <QDialog>

namespace Ui {
class ROIDialog;
}

class ROIDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ROIDialog(QWidget *parent = 0);
    ~ROIDialog();
    Ui::ROIDialog* get_ui() { return ui;}

    void setImage(QImage image, int label_id);

    int labelWidth(int label_id);
    int labelHeight(int label_id);
private:
    Ui::ROIDialog *ui;
};

#endif // ROIDIALOG_H
