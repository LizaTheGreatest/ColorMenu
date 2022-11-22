#include "searchfilter.h"
#include "ui_searchfilter.h"

SearchFilter::SearchFilter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchFilter)
{
    ui->setupUi(this);
    connect(ui->HEXRadioButton, SIGNAL(clicked()), this, SLOT(setNegotiability(true)));
    connect(ui->RGBRadioButton, SIGNAL(clicked()), this, SLOT(setNegotiability(false)));
    ui->HEXRadioButton->click();
}

SearchFilter::~SearchFilter()
{
    delete ui;
}

void SearchFilter::setNegotiability(const bool condition)
{
    ui->redLineEdit->setDisabled(condition);
    ui->greenLineEdit->setDisabled(condition);
    ui->blueLineEdit->setDisabled(condition);
    ui->hexLineEdit->setDisabled(!condition);
}

