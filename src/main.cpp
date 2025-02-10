#include <QCoreApplication>
#include <Akonadi/Collection>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>
#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <Akonadi/Item>
#include <KContacts/Addressee>
#include <QTextStream>
// #include <iostream>

namespace Akonadi {
    class Session;
}

void displayContacts(const Akonadi::Collection &collection) {
    Akonadi::ItemFetchJob *itemFetchJob = new Akonadi::ItemFetchJob(collection);
    itemFetchJob->fetchScope().fetchFullPayload();
    QObject::connect(itemFetchJob, &Akonadi::ItemFetchJob::result, [](KJob *job) {
        if (job->error()) {
            qCritical() << "Error fetching items:" << job->errorString();
            QCoreApplication::quit();
            return;
        }

        Akonadi::ItemFetchJob *fetchJob = qobject_cast<Akonadi::ItemFetchJob *>(job);
        const Akonadi::Item::List items = fetchJob->items();
        for (const Akonadi::Item &item : items) {
            if (item.hasPayload<KContacts::Addressee>()) {
                KContacts::Addressee contact = item.payload<KContacts::Addressee>();
                qDebug() << "Name:" << contact.formattedName();
                qDebug() << "Phone:" << contact.phoneNumbers().value(0).number();
                qDebug() << "Email:" << contact.emails().value(0);
            }
        }

        QCoreApplication::quit();
    });
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Create a fetch job to list all collections
    Akonadi::CollectionFetchJob *fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(),
                                                                            Akonadi::CollectionFetchJob::Recursive);

    QObject::connect(fetchJob, &Akonadi::CollectionFetchJob::result, [](KJob *job) {
        if (job->error()) {
            qCritical() << "Error fetching collections:" << job->errorString();
            QCoreApplication::quit();
            return;
        }

        Akonadi::CollectionFetchJob *fetchJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
        const Akonadi::Collection::List collections = fetchJob->collections();
        QList<Akonadi::Collection> contactCollections;
        for (const Akonadi::Collection &collection : collections) {
            if (collection.contentMimeTypes().contains(QString::fromUtf8("text/directory"))) {
                contactCollections.append(collection);
                qDebug() << "Collection:" << collection.name();
            }
        }

        if (contactCollections.isEmpty()) {
            qCritical() << "No collections with contacts found.";
            QCoreApplication::quit();
            return;
        }

        QTextStream qin(stdin);
        qDebug() << "Enter the number of the collection you want to view:";
        for (int i = 0; i < contactCollections.size(); ++i) {
            qDebug() << i << ":" << contactCollections.at(i).name();
        }

        int index;
        qin >> index;
        if (index < 0 || index >= contactCollections.size()) {
            qCritical() << "Invalid selection.";
            QCoreApplication::quit();
            return;
        }
	qDebug() << index;

        displayContacts(contactCollections.at(index));
    });

    return app.exec();
}
