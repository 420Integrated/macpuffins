#include "macpuffinsupdatedialog.h"

MacpuffinsUpdateDialog::MacpuffinsUpdateDialog(QWidget *parent) : QDialog(parent)
{
    mainLayout = new QGridLayout(this);
    updateInfoText = new QTextBrowser(this);

    currentVersionTitleLabel = new QLabel(this);
    currentVersionContentLabel = new QLabel(this);
    remoteVesionTitleLabel = new QLabel(this);
    remoteVesionContentLabel = new QLabel(this);
    downloadLinkLabel = new QLabel(this);

    currentVersionTitleLabel->setText("Current version: ");
    remoteVesionTitleLabel->setText("Available version: ");

    currentVersionTitleLabel->setAlignment(Qt::AlignRight);
    remoteVesionTitleLabel->setAlignment(Qt::AlignRight);
    currentVersionContentLabel->setAlignment(Qt::AlignLeft);
    remoteVesionContentLabel->setAlignment(Qt::AlignLeft);
    downloadLinkLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(currentVersionTitleLabel, 0, 0, 1, 1);
    mainLayout->addWidget(currentVersionContentLabel, 0, 1, 1, 1);
    mainLayout->addWidget(remoteVesionTitleLabel, 1, 0, 1, 1);
    mainLayout->addWidget(remoteVesionContentLabel, 1, 1, 1, 1);
    mainLayout->addWidget(updateInfoText, 2, 0, 1, 2);
    mainLayout->addWidget(downloadLinkLabel, 3, 0, 1, 2);
    this->setModal(true);

    this->setWindowTitle("Update available!");
    this->setStyleSheet("QDialog { background-color: white;border:none; font-family:'Open Sans,sans-serif'; }");
}

void MacpuffinsUpdateDialog::setRemoteVersion(const QString &version)
{
    remoteVesionContentLabel->setText(version);
}

void MacpuffinsUpdateDialog::setCurrentVersion(const QString &version)
{
    currentVersionContentLabel->setText(version);
}

void MacpuffinsUpdateDialog::setBodyText(const QString &bodyText)
{
    updateInfoText->setText(bodyText);
}

void MacpuffinsUpdateDialog::setDownloadLink(const QString &link)
{
    QString text = QString("<a href=\"") + link + "/\">Click Here to go visit the download page</a>";
    downloadLinkLabel->setText(text);
    downloadLinkLabel->setTextFormat(Qt::RichText);
    downloadLinkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    downloadLinkLabel->setOpenExternalLinks(true);
}

void MacpuffinsUpdateDialog::setUpdateRelease(const NeblioReleaseInfo& rel)
{
    this->setCurrentVersion(QString::fromStdString(NeblioVersion::GetCurrentNeblioVersion().toString()));
    this->setRemoteVersion(QString::fromStdString(rel.getVersion().toString()));
    this->setBodyText(QString::fromStdString(rel.getUpdateDescription()));
    this->setDownloadLink(QString::fromStdString(NeblioUpdater::LatestReleaseURL));
}
