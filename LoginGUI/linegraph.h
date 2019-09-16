#ifndef LINEGRAPH_H
#define LINEGRAPH_H

#include <QDialog>

namespace Ui {
class LineGraph;
}

class LineGraph : public QDialog
{
    Q_OBJECT

public:
    explicit LineGraph(QWidget *parent = nullptr);
    ~LineGraph();

private:
    Ui::LineGraph *ui;
};

#endif // LINEGRAPH_H
