#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFont>
#include <QFontDatabase>
#include <QDir>
#include <QQuickStyle>
#include "src/backendconnection.h"
#include "src/configmanager.h"
#include "src/markdownfilemanager.h"
#include "src/tabmanager.h"
#include "src/tab.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    for (auto &font : QDir(":/assets/fonts/Poppins").entryList(QStringList{"*.ttf"}, QDir::Files))
    {
        QFontDatabase::addApplicationFont(":/assets/fonts/Poppins/" + font);
    }

    QQuickStyle::setStyle("Basic");

    app.setApplicationDisplayName("Mark It Down");
    app.setApplicationName("Mark It Down");
    app.setOrganizationName("polsl");
    app.setDesktopFileName("markitdown");
    app.setFont(QFont("Poppins"));

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<Tab*>("pb.pk.markitdown", 1, 0, "Tab", "Tab is creatable by backend only");

    qmlRegisterSingletonInstance<ConfigManager>("pb.pk.markitdown", 1, 0, "ConfigManager", &ConfigManager::GetInstance());
    qmlRegisterSingletonInstance<TabManager>("pb.pk.markitdown", 1, 0, "TabManager", &TabManager::GetInstance());
    qmlRegisterSingletonInstance<MarkdownFileManager>("pb.pk.markitdown", 1, 0, "MarkdownFileManager", &MarkdownFileManager::GetInstance());

    qRegisterMetaType<unsigned short>("unsigned short");

    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl)
        {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
