#include "plugin.h"
#include <QLabel>
#include <QRegularExpression>
#include <albert/logging.h>
#include <albert/standarditem.h>
#include <albert/util.h>
#include <ServerManager>
#include <Session>
#include <Akonadi/Collection>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/Item>
#include <KContacts/Addressee>
#include <QTextStream>
// #include <iostream>

ALBERT_LOGGING_CATEGORY("contacts")
using namespace albert;
using namespace Akonadi;
using namespace std;


vector<RankItem> Plugin::handleGlobalQuery(const Query *query)
{
  vector<RankItem> results;
    QObject::connect(fetchJob, &Akonadi::CollectionFetchJob::result, [](KJob *job) {
        if (job->error()) {
            qCritical() << "Error fetching collections:" << job->errorString();
            QCoreApplication::quit();
            return;
        }



  return results;
}


QWidget *Plugin::buildConfigWidget()
{
    auto l = new QLabel(tr("KDE Akonadi contacts prototype. For now only phone and mail."));
    l->setWordWrap(true);
    l->setAlignment(Qt::AlignTop);
    return l;
}

