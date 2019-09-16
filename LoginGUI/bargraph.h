#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QDialog>

namespace Ui {
class BarGraph;
}

class BarGraph : public QDialog
{
    Q_OBJECT

public:
    explicit BarGraph(QWidget *parent = nullptr);
    ~BarGraph();

private:
    Ui::BarGraph *ui;
};

#endif // BARGRAPH_H
