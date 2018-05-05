#include <QCoreApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
#ifndef _WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
#endif

    QCoreApplication a(argc, argv);
    QString program = "taskkill";
    QProcess process;
    for (int i = 1; i < argc; ++i) {
        QStringList arguments;
        QString arg = QString::fromLatin1(argv[i]);
        if (arg.contains("edge")) {
            arg = QString("MicrosoftEdge.exe");
        }

        if (!arg.contains(".exe"))
            arg.append(".exe");
        arguments << "/im" << arg << "/t" << "/f";
        process.start(program, arguments);
        process.waitForFinished(5000);
    }
    exit(0);

    return a.exec();
}

