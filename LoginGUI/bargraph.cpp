#include "bargraph.h"
#include "ui_bargraph.h"

BarGraph::BarGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BarGraph)
{
    ui->setupUi(this);
}

BarGraph::~BarGraph()
{
    delete ui;
}
