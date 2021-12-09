#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H
#include <QSystemTrayIcon>
#include<QString>
class Notifications
{
public:
    Notifications();
    void show_notif(QString,QString);
};

#endif // NOTIFICATIONS_H
