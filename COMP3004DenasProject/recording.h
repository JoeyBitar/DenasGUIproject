#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>
#include <QDateTime>

class Recording : public QObject
{
    Q_OBJECT
public:
    explicit Recording(QObject *parent = nullptr);
    Recording(QDateTime,std::string,int,QString);
private:
    QDateTime dateTime;
    std::string program;
    int maxPower;
    QString duration;

signals:

public slots:
};

#endif // RECORDING_H
