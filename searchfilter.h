#ifndef SEARCHFILTER_H
#define SEARCHFILTER_H

#include <QWidget>

namespace Ui {
class SearchFilter;
}

class SearchFilter : public QWidget
{
    Q_OBJECT

public:
    explicit SearchFilter(QWidget *parent = nullptr);
    ~SearchFilter();

private slots:
    void setNegotiability(const bool condition);
private:
    Ui::SearchFilter *ui;
};

#endif // SEARCHFILTER_H
