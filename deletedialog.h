#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    bool ifDeleted();
    ~DeleteDialog();

private slots:
    void on_Delete_clicked();

    void on_Cancel_clicked();

public slots:
    void setUser(QString username, QString password);

private:
    Ui::DeleteDialog *ui;
    QString username;
    QString password;
    bool check;
};

#endif // DELETEDIALOG_H
