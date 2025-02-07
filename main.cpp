#include <QCoreApplication>
#include <Akonadi/Collection>
#include <Akonadi/CollectionFetchJob>
#include <Akonadi/CollectionFetchScope>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Create a fetch job to list all collections
    Akonadi::CollectionFetchJob *fetchJob = new Akonadi::CollectionFetchJob(Akonadi::Collection::root(),
                                                                            Akonadi::CollectionFetchJob::Recursive);
    fetchJob->fetchScope().setResource("akonadi_maildir_resource");

    QObject::connect(fetchJob, &Akonadi::CollectionFetchJob::result, [](KJob *job) {
        if (job->error()) {
            qCritical() << "Error fetching collections:" << job->errorString();
            return;
        }

        Akonadi::CollectionFetchJob *fetchJob = qobject_cast<Akonadi::CollectionFetchJob *>(job);
        const Akonadi::Collection::List collections = fetchJob->collections();
        for (const Akonadi::Collection &collection : collections) {
            qDebug() << "Collection:" << collection.name();
        }

        QCoreApplication::quit();
    });

    return app.exec();
}
