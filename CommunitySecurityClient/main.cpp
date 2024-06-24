#include "communitysecurityclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CommunitySecurityClient w;
    w.show();
    return a.exec();
}
