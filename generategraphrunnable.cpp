#include "generategraphrunnable.h"

#include <vector>
#include <QImage>
#include <QRandomGenerator>
#include <QLineSeries>
#include <QChart>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsLayout>
#include <QPen>
#include <QValueAxis>
#include <QMargins>
#include <QChartView>
#include <QScopedPointer>

#include <QDebug>

GenerateGraphRunnable::
GenerateGraphRunnable(unsigned int numDataPoints,
                      unsigned int minDataValue,
                      unsigned int maxDataValue)
    : mNumDataPoints(numDataPoints)
    , mMinDataValue(minDataValue)
    , mMaxDataValue(maxDataValue)
{
}

void GenerateGraphRunnable::run()
{
    using QtCharts::QChartView;
    using QtCharts::QChart;
    using QtCharts::QLineSeries;

    const unsigned int OUTPUT_WIDTH = 300;
    const unsigned int OUTPUT_HEIGHT = 200;

    QImage outImage (OUTPUT_WIDTH, OUTPUT_HEIGHT, QImage::Format_ARGB32);

    //QScopedPointer<QChart> chart(new QChart);
    QChart * chart = new QChart();
    chart->legend()->hide();
    chart->setMargins(QMargins(0, 0, 0, 0));
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);
    unsigned int dieX = 12;
    unsigned int dieY = 14;
    QString dieCode = "X346";
    double avg = 8665.5;
    double sd = 12.34;
    chart->setTitle(QStringLiteral("<b><u>VDD</u></b> "
                                   "(Avg: %4, SD: %5) - "
                                   "Die (%1,%2) [%3]")
                    .arg(dieX)
                    .arg(dieY)
                    .arg(dieCode)
                    .arg(avg, 0, 'f', 1)
                    .arg(sd, 0, 'f', 2));

    //QScopedPointer<QLineSeries> series(new QLineSeries);
    QLineSeries * series = new QLineSeries();
    series->setPen(QPen(QBrush(Qt::blue), 1));
    series->setPointsVisible(true);

    // generate data points here
    for (int i = 1; i <= mNumDataPoints-1; i++)
    {
        unsigned int value = QRandomGenerator::global()->bounded(mMinDataValue,
                                                                 mMaxDataValue);
        series->append(i, value);
        //axisY->setRange(6500, 10500);
    }
    series->append(mNumDataPoints, 16383);

    //chart->addSeries(series.get());
    chart->addSeries(series);
    chart->createDefaultAxes();

    auto axisX = qobject_cast<QtCharts::QValueAxis *>(
                /*chart->axes(Qt::Horizontal, series.get()).first());*/
                chart->axes(Qt::Horizontal, series).first());

    axisX->setLabelFormat(QStringLiteral("%d"));
    axisX->setRange(1, mNumDataPoints);

    auto axisY = qobject_cast<QtCharts::QValueAxis *>(
                /*chart->axes(Qt::Vertical, series.get()).first());*/
                chart->axes(Qt::Vertical, series).first());
    axisY->setLabelFormat(QStringLiteral("%d"));
    // axisY is autoranged
    axisY->setRange(6500, 10500);
    axisY->setMinorTickCount(1);

    chart->resize(outImage.size());

    QScopedPointer<QGraphicsScene> scene (new QGraphicsScene);
    //scene->addItem(chart.get());
    scene->addItem(chart);

    QPainter painter (&outImage);
    painter.setRenderHint(QPainter::TextAntialiasing);
    scene->render(&painter);
    painter.end();

    emit generatedGraph(outImage);
}
