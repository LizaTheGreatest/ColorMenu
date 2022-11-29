#include "searchfilter.h"
#include "ui_searchfilter.h"

SearchFilter::SearchFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFilter)
{
    ui->setupUi(this);
    connect(ui->HEXRadioButton, &QRadioButton::clicked, [this]
    {
        setNegotiability(true);

    });
    connect(ui->RGBRadioButton, &QRadioButton::clicked, [this]{ setNegotiability(false); });
    ui->HEXRadioButton->click();
}

SearchFilter::~SearchFilter()
{
    delete ui;
}

void SearchFilter::setNegotiability(bool disable)
{
    ui->redLineEdit->setDisabled(disable);
    ui->greenLineEdit->setDisabled(disable);
    ui->blueLineEdit->setDisabled(disable);
    ui->hexLineEdit->setDisabled(!disable);
}

