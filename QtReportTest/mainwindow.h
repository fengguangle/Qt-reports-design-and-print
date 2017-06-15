#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QTime>
#include <QtPrintSupport/qprinter.h>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QTextEdit>
#include <QTextDocument>
#include <QPrintPreviewWidget>
#include <QLayout>
#include <QPrintDialog>
#include <QPageSetupDialog>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
    void on_lineEdit_id_textChanged(const QString &arg1);

    void on_lineEdit_name_textChanged(const QString &arg1);

    void on_lineEdit_gender_textChanged(const QString &arg1);

    void on_lineEdit_age_textChanged(const QString &arg1);

    void on_lineEdit_mobile_textChanged(const QString &arg1);

    void on_textEdit_conclusion_textChanged();

    void printPreview(QPrinter *p);

    void on_pushButton_priview_clicked();

    void on_pushButton_pagesetup_clicked();

    void on_pushButton_printsetup_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_paintprint_clicked();

    void on_pushButton_selPic1_clicked();

    void on_pushButton_selPic2_clicked();

    void on_pushButton_paintprint_pdf_clicked();

private:
    Ui::MainWindow *ui;

    QString m_strPeintHtml;
    QString getHtmlStr();
    QPrinter *printer;
    QTextDocument *ted;
    QPrintDialog *printDlg;
    QPageSetupDialog *pageDlg;
    QPrintPreviewDialog *pd;
    void UpdateDoc();
    void printPainter(bool isPDF,QString id,QString name,QString gender, QString age,QString mobile,QString con,QString spic1,QString spic2);
    QString getPicFile();
};

#endif // MAINWINDOW_H
