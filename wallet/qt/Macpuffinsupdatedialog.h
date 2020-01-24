#ifndef MACPUFFINSUPDATEDIALOG_H
#define MACPUFFINSUPDATEDIALOG_H

#include <QDialog>
#include <QTextBrowser>
#include <QGridLayout>
#include <QLabel>

#include "macpuffinsupdater.h"

class MacpuffinsUpdateDialog : public QDialog
{
    Q_OBJECT

    QLabel* currentVersionTitleLabel;
    QLabel* currentVersionContentLabel;
    QLabel* remoteVesionTitleLabel;
    QLabel* remoteVesionContentLabel;
    QTextBrowser* updateInfoText;
    QGridLayout*  mainLayout;
    QLabel* downloadLinkLabel;

    void setRemoteVersion(const QString& version);
    void setCurrentVersion(const QString& version);
    void setBodyText(const QString& bodyText);
    void setDownloadLink(const QString& link);

public:
    explicit MacpuffinsUpdateDialog(QWidget *parent = 0);

    void setUpdateRelease(const MacpuffinsReleaseInfo &rel);

signals:

public slots:
};

#endif // MACPUFFINSUPDATEDIALOG_H
