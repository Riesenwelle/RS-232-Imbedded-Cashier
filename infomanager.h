#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include <QWidget>
#include "dbconnect.h"

namespace Ui {
class InfoManager;
}

class InfoManager : public QWidget
{
    Q_OBJECT

signals:
    void signalinmb();

public:
    explicit InfoManager(QWidget *parent = 0);
    ~InfoManager();

private slots:
    void on_pbBack_clicked();
    void on_pbSubmit_clicked();
    void on_tv_clicked(const QModelIndex &index);
    void on_pbDele_clicked();
    void on_pbClean_clicked();

    // a-z + 0
    void on_pbkeya_clicked();
    void on_pbkeyb_clicked();
    void on_pbkeyc_clicked();
    void on_pbkeyd_clicked();
    void on_pbkeye_clicked();
    void on_pbkeyf_clicked();
    void on_pbkeyg_clicked();
    void on_pbkeyh_clicked();
    void on_pbkeyi_clicked();
    void on_pbkeyj_clicked();
    void on_pbkeyk_clicked();
    void on_pbkeyl_clicked();
    void on_pbkeym_clicked();
    void on_pbkeyn_clicked();
    void on_pbkeyo_clicked();
    void on_pbkeyp_clicked();
    void on_pbkeyq_clicked();
    void on_pbkeyr_clicked();
    void on_pbkeys_clicked();
    void on_pbkeyt_clicked();
    void on_pbkeyu_clicked();
    void on_pbkeyv_clicked();
    void on_pbkeyw_clicked();
    void on_pbkeyx_clicked();
    void on_pbkeyy_clicked();
    void on_pbkeyz_clicked();
    void on_pbkey0_clicked();

    void on_pbRefr_clicked();

    void on_pbkeyBS_clicked();

private:
    Ui::InfoManager *ui;
    QString gid,gname,gnum,gprice;
    void refresh();
    bool isSelected;
    int selectedColumn; // gid : 0, gname : 1, gprice : 2, gnum : 3
    QString qschange;
};

#endif // INFOMANAGER_H
