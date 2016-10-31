#ifndef TIMEGRAPH_H
#define TIMEGRAPH_H

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include "gnssdata.h"

namespace Ui {
class TimeGraph;
}

class TimeGraph : public QWidget
{
    Q_OBJECT

public:
    explicit TimeGraph(QWidget *parent = 0);
    ~TimeGraph();

public slots:
    void dataset(std::vector<double> dataT, std::vector<double> dataF, const StandardTime& startTime, const StandardTime& stopTime);

private:
    Ui::TimeGraph *ui;
    QwtPlot *plot;
    QwtSymbol *symbolT;
    QwtSymbol *symbolF;
    QwtPlotCurve *curveTime;
    QwtPlotCurve *curveFrecuency;
    QwtPlotGrid *grid ;

    void plot_paint();
};

#endif // TIMEGRAPH_H
