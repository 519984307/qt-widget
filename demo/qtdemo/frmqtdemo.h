#ifndef FRMQTDEMO_H
#define FRMQTDEMO_H

#include <QWidget>

namespace Ui {
class frmQtDemo;
}

class frmQtDemo : public QWidget
{
    Q_OBJECT

public:
    explicit frmQtDemo(QWidget *parent = 0);
    ~frmQtDemo();

private:
    Ui::frmQtDemo *ui;

private slots:
    void initForm();

public slots:
    void setIndex(int index);
};

#endif // FRMQTDEMO_H
