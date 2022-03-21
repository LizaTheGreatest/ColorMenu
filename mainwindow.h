#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTableWidget>
#include <QList>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showColor();
    void refillColumns();

private:
    QList<QList<int>> rgbp;
    QList<int> rgbpPart;

    int userRed;
    int userGreen;
    int userBlue;


    int rowsInFile = 0;

    Ui::MainWindow *ui;
    QColor color;
    QString color_name;
    QString hex;
    QString red;
    QString green;
    QString blue;

    int findColorPosition();
    void fillRow(int row, QString &line);
    void fill_columns();
    int countRows();
    const QString path = "C:\\Users\\User\\Documents\\Qt\\ColorMenu\\colors.txt";
};
#endif // MAINWINDOW_H
