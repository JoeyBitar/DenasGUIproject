#ifndef TREATMENT_H
#define TREATMENT_H

#include <QObject>

class Treatment : public QObject
{
    Q_OBJECT
public:
    explicit Treatment(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TREATMENT_H
