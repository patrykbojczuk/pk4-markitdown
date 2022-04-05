#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QFontDatabase>
#include <QDir>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    for(auto& font: QDir(":/assets/fonts/Poppins").entryList(QStringList{"*.ttf"}, QDir::Files)){
        QFontDatabase::addApplicationFont(":/assets/fonts/Poppins/" + font);
    }

    app.setApplicationDisplayName("Mark It Down");
    app.setApplicationName("Mark It Down");
    app.setOrganizationName("polsl");
    app.setDesktopFileName("markitdown");
    app.setFont(QFont("Poppins"));

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
