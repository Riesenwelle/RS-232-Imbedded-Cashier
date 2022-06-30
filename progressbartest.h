#ifndef PROGRESSBARTEST_H
#define PROGRESSBARTEST_H

#include <QWidget>
#include "dbconnect.h"

namespace Ui {
class ProgressBarTest;
}

class ProgressBarTest : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressBarTest(QWidget *parent = 0);
    ~ProgressBarTest();

signals:
    void signalpbtb();

private slots:
    void on_pbDown_clicked();

    void on_pbUp_clicked();

    void on_pbBack_clicked();

private:
    Ui::ProgressBarTest *ui;
    int progressBarValue;
};

#endif // PROGRESSBARTEST_H
