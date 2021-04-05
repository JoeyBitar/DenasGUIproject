#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>
#include <QDateTime>

class Recording : public QObject
{
    Q_OBJECT
public:
    explicit Recording(QObject *parent = nullptr);

private:
    QDateTime dateTime;
    std::string program;
    int maxPower;
    int duration;
    int frequency;
signals:

public slots:
};

#endif // RECORDING_H
