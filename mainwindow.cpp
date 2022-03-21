#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(showColor()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(refillColumns()));

    ui->tableWidget->setColumnCount(6);
    const QList<QString> headers = {"Color", "Color name", "HEX", "R", "G", "B"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 220);
    ui->tableWidget->setColumnWidth(2, 100);
    ui->tableWidget->setColumnWidth(3, 70);
    ui->tableWidget->setColumnWidth(4, 70);
    ui->tableWidget->setColumnWidth(5, 70);



    fill_columns();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::findColorPosition()
{

    try
    {
        userRed = (ui->lineEdit_red->text()).toInt();
        userGreen = (ui->lineEdit_green->text()).toInt();
        userBlue = (ui->lineEdit_blue->text()).toInt();
        if(userRed < 0 || userRed > 255)
        {
            throw std::range_error("Incorrect number in RED field");

        }
        if(userGreen < 0 || userGreen > 255)
        {
            throw std::range_error("Incorrect number in GREEN field");

        }
        if(userBlue < 0 || userBlue > 255)
        {
            throw std::range_error("Incorrect number in BLUE field");

        }

        for(auto x : rgbp)
        {
            if(x[0] == userRed && x[1] == userGreen && x[2] == userBlue)
                return x[3];

        }

    }  catch (const std::range_error ex) {

        QMessageBox::information(this, "Range error", ex.what());

    }
    return -1;
}

void MainWindow::showColor()
{
    int pos = findColorPosition();
    try
    {
        if(pos == -1)
        {
            throw std::runtime_error("Color was not found");
        }

        else
        {
            for(int i = 0; i < rowsInFile; ++i)
            {
                if(i != pos)
                {
                    if(!ui->tableWidget->isRowHidden(i))
                        ui->tableWidget->hideRow(i);
                }
                else
                {
                    if(ui->tableWidget->isRowHidden(i))
                        ui->tableWidget->showRow(i);
                }
            }
        }

    }
    catch (const std::runtime_error &ex)
    {
        QMessageBox::information(this, "Does not exist", ex.what());
        return;
    }
}

void MainWindow::refillColumns()
{
    for(int i = 0; i < rowsInFile; i++)
        ui->tableWidget->showRow(i);
    ui->lineEdit_red->clear();
    ui->lineEdit_green->clear();
    ui->lineEdit_blue->clear();
}



void MainWindow::fillRow(int row, QString &line)
{
    QChar symb;
    int counter = 0;
    for(auto x : line)
    {
        symb = x;
        if(symb == ':')
        {

            counter++;
            continue;
        }
        switch (counter)
        {
            case 0:
            {
                color_name.append(symb);
                symb = x;
                break;
            }
            case 1:
            {
                hex.append(symb);
                symb = x;
                break;
            }
            case 2:
            {
                red.append(symb);
                symb = x;
                break;
            }
            case 3:
            {
                green.append(symb);
                symb = x;
                break;
            }
            case 4:
            {
                blue.append(symb);
                symb = x;
                break;
            }
            default: break;
        }
    }

    rgbpPart.push_front(row);
    rgbpPart.push_front(blue.toInt());
    rgbpPart.push_front(green.toInt());
    rgbpPart.push_front(red.toInt());
    rgbp.push_front(rgbpPart);
    rgbpPart.clear();

    color.setRgb(red.toInt(), green.toInt(), blue.toInt());
    QTableWidgetItem *itm_color = new QTableWidgetItem();
    QTableWidgetItem *color_name = new QTableWidgetItem();
    QTableWidgetItem *hex = new QTableWidgetItem();
    QTableWidgetItem *red = new QTableWidgetItem();
    QTableWidgetItem *green = new QTableWidgetItem();
    QTableWidgetItem *blue = new QTableWidgetItem();

    itm_color->setBackground(color);
    color_name->setText(this->color_name);
    hex->setText(this->hex);
    red->setText(this->red);
    green->setText(this->green);
    blue->setText(this->blue);

    ui->tableWidget->setItem(row, 0,itm_color);
    ui->tableWidget->setItem(row, 1, color_name);
    ui->tableWidget->setItem(row, 2, hex);
    ui->tableWidget->setItem(row, 3, red);
    ui->tableWidget->setItem(row, 4, green);
    ui->tableWidget->setItem(row, 5, blue);

    this->color_name.clear();
    this->hex.clear();
    this->red.clear();
    this->green.clear();
    this->blue.clear();

}

void MainWindow::fill_columns()
{
    QFile myFile(path);
    if(!myFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this, "Error...", "the file was not opened");
        return;
    }

    QTextStream stream(&myFile); //если файл открыт, нужно его прочесть. Qtextstream может читать и писать в файл. Теперь данный текстовый поток будет направлен на данный файл.

    while(!stream.atEnd())
    {
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        QString line = stream.readLine();
        fillRow(ui->tableWidget->rowCount() - 1, line);
        myFile.flush();
        rowsInFile++;
    }

    myFile.close();

}





