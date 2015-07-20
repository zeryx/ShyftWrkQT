#ifndef REST_H
#define REST_H

#include <QObject>
#include <QNetworkReply>
#include <QJsonObject>
class Rest : public QObject //abstract Rest interface, its inherited classes are used as composite objects in other classes.
{
    Q_OBJECT

public:
    Rest(QObject *parent); //is never called, this is strictly an abstract class

    virtual bool checkQueryCode();
signals:
    void responseCompleted();


private slots: // standard response handler for signal information
    virtual void genericResponse(QNetworkReply *reply);

   virtual  void errorResponse(QNetworkReply::NetworkError);


protected:

    QJsonObject *_responseStream;


};

#endif // REST_H
