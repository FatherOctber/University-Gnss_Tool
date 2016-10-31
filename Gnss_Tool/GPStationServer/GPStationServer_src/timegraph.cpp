#include "timegraph.h"
#include "ui_timegraph.h"

TimeGraph::TimeGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeGraph)
{
    ui->setupUi(this);
    plot = ui->timePlot;
    curveTime = new QwtPlotCurve();
    curveTime->setPen( Qt::red, 2 );
    curveTime->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    symbolT = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 2, 2 ) );
    curveTime->setSymbol( symbolT );
    curveTime->attach(plot);

    curveFrecuency = new QwtPlotCurve();
    curveFrecuency->setPen( Qt::green, 2 );
    curveFrecuency->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    symbolF = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::green, 2 ), QSize( 2, 2 ) );
    curveFrecuency->setSymbol( symbolF );
    curveFrecuency->attach(plot);
    plot_paint();
}

TimeGraph::~TimeGraph()
{
    delete ui;
}

void TimeGraph::plot_paint()
{
    plot->setTitle( "Данные смещения" ); // заголовок
    plot->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    plot->setAxisTitle(QwtPlot::yLeft, "Y");
    plot->setAxisTitle(QwtPlot::xBottom, "X");
    plot->insertLegend( new QwtLegend() );

    // Включить сетку
    grid = new QwtPlotGrid(); //
    grid->setMajorPen(QPen( Qt::gray, 1 )); // цвет линий и толщина
    grid->attach( plot ); // добавить сетку к полю графика
}


void TimeGraph::dataset(std::vector<double> dataT, std::vector<double> dataF, const StandardTime &startTime, const StandardTime &stopTime)
{
    curveTime->setTitle("Смещение времени");
    QPolygonF markPointT, markPointF;
    if(dataT.size()==0 || dataF.size()==0) {
        qDebug() << "No data";
        return;
    }
    double valueMax = -DBL_MAX;
    double valueMin = DBL_MAX;
    for(int i=0; i<dataT.size(); i++)
    {
        if(valueMax < dataT[i])
            valueMax = dataT[i];
        if(valueMin > dataT[i])
            valueMin = dataT[i];
        markPointT << QPointF( i, dataT[i]);
     }
    curveTime->setSamples(markPointT);
    curveTime->setPen( QColor::fromRgb(123,123,123), 2 ); // цвет и толщина кривой
    curveTime->setRenderHint( QwtPlotItem::RenderAntialiased, true );
    plot->setTitle("Смещение времени приемника");
    plot->setAxisTitle(QwtPlot::yLeft, "Смещение");
    plot->setAxisTitle(QwtPlot::xBottom, "T (дискретное)");
    plot->setAxisScale(QwtPlot::xBottom,0,dataT.size());
    plot->setAxisScale(QwtPlot::yLeft,valueMin,valueMax);
    plot->replot();
    ui->startTime_line->setText(QString::fromStdString(startTime.date+" "+startTime.time));
    ui->stopTime_line->setText(QString::fromStdString(stopTime.date+" "+stopTime.time));
    ui->maxBias_line->setText(QString::number(valueMax));
    ui->minBias_line->setText(QString::number(valueMin));

    this->show();
}
