#ifndef FRMPANELWIDGETX_H
#define FRMPANELWIDGETX_H

#include <QWidget>

namespace Ui {
class frmPanelWidgetX;
}

class frmPanelWidgetX : public QWidget
{
    Q_OBJECT

public:
    explicit frmPanelWidgetX(QWidget *parent = 0);
    ~frmPanelWidgetX();

private:
    Ui::frmPanelWidgetX *ui;
    int type;
    QString flag;

public:
    void setFlag(const QString &flag);
    QString getFlag() const;

    void setValue(int value);
    int getValue() const;

private slots:
    void initForm();
    void updateValue();
};

#endif // FRMPANELWIDGETX_H
