#ifndef GENERATEGRAPHRUNNABLE_H
#define GENERATEGRAPHRUNNABLE_H

#include <QObject>
#include <QRunnable>

class GenerateGraphRunnable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    GenerateGraphRunnable(unsigned int numDataPoints,
                          unsigned int minDataValue,
                          unsigned int maxDataValue,
                          bool hasDataOutOfRange);

    void run() override;

signals:
    void generatedGraph(const QImage & out);

private:
    unsigned int mNumDataPoints;
    unsigned int mMinDataValue;
    unsigned int mMaxDataValue;
    bool mHasDataOutOfRange;
};

#endif // GENERATEGRAPHRUNNABLE_H
