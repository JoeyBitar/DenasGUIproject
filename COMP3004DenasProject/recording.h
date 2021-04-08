#ifndef RECORDING_H
#define RECORDING_H

#include <QObject>
#include <QDateTime>

class Recording : public QObject
{
    Q_OBJECT
public:
    explicit Recording(QObject *parent = nullptr);
    Recording(QDateTime,std::string,int,std::string);
    ~Recording();
private:
    QDateTime dateTime;
    std::string program;
    int maxPower;
    std::string duration;

signals:

public slots:
};

#endif // RECORDING_H
