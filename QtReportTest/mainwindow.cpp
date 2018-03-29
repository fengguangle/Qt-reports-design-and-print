#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEngine>
#include <QPrintEngine>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ted = new QTextDocument;
    printer=new QPrinter();
    printer->setOutputFormat(QPrinter::NativeFormat);
    printer->setPaperSize(QPrinter::A4);
    ted->setPageSize(printer->pageSizeMM());

    printDlg=new QPrintDialog(printer);
    pageDlg=new QPageSetupDialog(printer);

    preview = new QPrintPreviewWidget (printer,this);

    this->ui->verticalLayout_preview->addWidget(preview);
    preview->setZoomMode(QPrintPreviewWidget::FitInView);
    connect(preview, SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview2(QPrinter *)));//关联打印预览的内容
    preview->show();

    UpdateDoc();
}

MainWindow::~MainWindow()
{
    delete ui;   
}

void MainWindow::UpdateDoc()
{
    ui->textBrowser->clear();
    ted->setHtml(getHtmlStr());
    ui->textBrowser->setDocument(ted);
    preview->updatePreview();
}

void MainWindow::on_lineEdit_id_textChanged(const QString &arg1)
{
    UpdateDoc();
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    UpdateDoc();
}

void MainWindow::on_lineEdit_gender_textChanged(const QString &arg1)
{
    UpdateDoc();
}

void MainWindow::on_lineEdit_age_textChanged(const QString &arg1)
{
    UpdateDoc();
}

void MainWindow::on_lineEdit_mobile_textChanged(const QString &arg1)
{
    UpdateDoc();
}

void MainWindow::on_textEdit_conclusion_textChanged()
{
    UpdateDoc();
}

void MainWindow::on_pushButton_priview_clicked()
{
    pd = new QPrintPreviewDialog(printer);
    connect(pd,SIGNAL(paintRequested(QPrinter*)),this,SLOT(printPreview(QPrinter*)));
    pd->resize(600,800);
    pd->exec();
    delete pd;
}


void MainWindow::printPreview(QPrinter *p)
{
    ted->setHtml(getHtmlStr());
    ted->print(p);
}

void MainWindow::on_pushButton_pagesetup_clicked()
{
    pageDlg->exec();
    preview->updatePreview();
}

void MainWindow::on_pushButton_printsetup_clicked()
{
    printDlg->exec();
}

QString MainWindow::getHtmlStr()
{
    QFile x(":/report_template.html");
    x.open(QIODevice::ReadOnly);
    QTextStream in(&x);
    in.setCodec("UTF-8"); //注意编码
    QString html = in.readAll();
    m_strPeintHtml=QString(html)
            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(ui->lineEdit_id->text())
            .arg(ui->lineEdit_name->text())
            .arg(ui->lineEdit_gender->text())
            .arg(ui->lineEdit_age->text())
            .arg(ui->lineEdit_mobile->text())
            .arg(ui->textEdit_conclusion->toPlainText())
            .arg(ui->lineEdit_pic1->text())
            .arg(ui->lineEdit_pic2->text());

    return m_strPeintHtml;
}

void MainWindow::printPainter(bool isPDF,QString id,QString name,QString gender, QString age,QString mobile,QString con,QString spic1,QString spic2)
{
    QPrinter printer_report;
    QPainter painter_text;
    QString fileName;
    if(isPDF){
        fileName = QCoreApplication::applicationDirPath()+"/report.pdf";
        qDebug()<<fileName;
        printer_report.setOutputFormat(QPrinter::PdfFormat);
        printer_report.setOutputFileName(fileName);
        painter_text.begin(&printer_report);
    }
    else{
        painter_text.begin(printer);
    }

    QPoint point(150,50);
    // 报告名字字体
    QFont reportNameFont;
    reportNameFont.setFamily("微软雅黑");
    reportNameFont.setBold(true);
    reportNameFont.setPixelSize(20);
    reportNameFont.setPointSize(30);
    painter_text.setFont(reportNameFont);
    QString message = "报表标题";
    painter_text.drawText(point,message);

    // 正文字体
    int leftBlank = 40;
    int deltaY  = 40;
    int marginX = 120;
    int deltaX  = 300;
    int valueWide = 40;
    QFont mainFont;
    mainFont.setFamily("微软雅黑");
    mainFont.setBold(false);
    mainFont.setPixelSize(10);
    mainFont.setPointSize(15);
    painter_text.setFont(mainFont);

    message = "ID :";
    // 打印“id”
    point = QPoint(leftBlank,140);
    painter_text.drawText(point,message);
    // 从标签左移
    // 打印id号
    point = QPoint(leftBlank+marginX,point.y());
    painter_text.drawText(point,id);
    // 打印姓名标签
    point = QPoint(leftBlank,point.y()+deltaY);
    painter_text.drawText(point,"姓名 :");
    // 打印姓名
    point = QPoint(point.x()+marginX,point.y());
    painter_text.drawText(point,name);
    // 打印性别标签
    point = QPoint(leftBlank+deltaX,point.y());
    painter_text.drawText(point,"性别 :");
    // 打印性别
    point = QPoint(point.x()+marginX,point.y());
    painter_text.drawText(point,gender);
    // 打印年龄标签
    point = QPoint(leftBlank,point.y()+deltaY);
    painter_text.drawText(point,"年龄 :");
    // 打印年龄
    point = QPoint(point.x()+marginX,point.y());
    painter_text.drawText(point,age);
    // 打印岁
    point = QPoint(point.x()+valueWide,point.y());
    painter_text.drawText(point,"岁");
    // 打印联系电话标签
    point = QPoint(leftBlank+deltaX,point.y());
    painter_text.drawText(point,"联系电话 :");
    // 打印联系电话
    point = QPoint(point.x()+marginX,point.y());
    painter_text.drawText(point,mobile);

    // 标题字体
    QFont titleFont;
    titleFont.setFamily("微软雅黑");
    titleFont.setBold(true);
    titleFont.setPixelSize(15);
    titleFont.setPointSize(20);
    painter_text.setFont(titleFont);
    // 打印备注标签
    point = QPoint(leftBlank,point.y()+deltaY);
    painter_text.drawText(point,"备注 :");
    // 打印备注
    point = QPoint(leftBlank,point.y()+deltaY);
    painter_text.setFont(mainFont);
    painter_text.drawText(point,con);

    // 打印图像
    int imageBlank  = 30;
    int imageWide   = 220;
    int imageHeight = 220;
    point = QPoint(leftBlank,point.y()+deltaY);
    QPixmap map = QPixmap::fromImage(QImage(spic1));
    if(!map.isNull())
    {
        map=map.scaled(200,150);
        painter_text.drawPixmap(point,map);
    }

    point = QPoint(point.x()+imageWide,point.y());
    map = QPixmap::fromImage(QImage(spic2));
    if(!map.isNull())
    {
        map=map.scaled(200,150);
        painter_text.drawPixmap(point,map);
    }

    // 打印图像标题
    point = QPoint(leftBlank+imageBlank,point.y()+imageHeight);
    painter_text.drawText(point,"图1");
    point = QPoint(point.x()+imageWide,point.y());
    painter_text.drawText(point,"图2");

    painter_text.end();

    if(isPDF)
    {
        QMessageBox::information(this,"提示","打印成功。保存在\n"+fileName);
    }
}


void MainWindow::on_pushButton_print_clicked()
{
    //ted->print(printer);
    preview->print();
}

void MainWindow::on_pushButton_paintprint_clicked()
{
    printPainter(false,ui->lineEdit_id->text(),ui->lineEdit_name->text(),ui->lineEdit_gender->text()
                 ,ui->lineEdit_age->text(),ui->lineEdit_mobile->text(),ui->textEdit_conclusion->toPlainText()
                 ,ui->lineEdit_pic1->text(),ui->lineEdit_pic2->text());
}

void MainWindow::on_pushButton_paintprint_pdf_clicked()
{
    printPainter(true,ui->lineEdit_id->text(),ui->lineEdit_name->text(),ui->lineEdit_gender->text()
                 ,ui->lineEdit_age->text(),ui->lineEdit_mobile->text(),ui->textEdit_conclusion->toPlainText()
                 ,ui->lineEdit_pic1->text(),ui->lineEdit_pic2->text());
}
//widget 预览
void MainWindow::printPreview2(QPrinter *p)
{
//    QTextDocument *ted = new QTextDocument;
//    //ted->setPageSize(QSizeF(400,800));
//    ted->setHtml(getHtmlStr());
    ted->print(p);
//    ui->textBrowser->print(p);
//    ui->textBrowser->print(p);
//    qDebug()<<p->paintEngine()->type();
   // delete ted;
}

QString MainWindow::getPicFile()
{
    QString path="";
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open Image"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images (*.png *.jpg *.bmp)"));
    if(fileDialog->exec() == QDialog::Accepted) {
        path = fileDialog->selectedFiles()[0];
        //QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
    }
    return path;
}

void MainWindow::on_pushButton_selPic1_clicked()
{
    ui->lineEdit_pic1->setText(getPicFile());
    UpdateDoc();
}

void MainWindow::on_pushButton_selPic2_clicked()
{
    ui->lineEdit_pic2->setText(getPicFile());
    UpdateDoc();
}


