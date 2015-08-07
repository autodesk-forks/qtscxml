/****************************************************************************
 **
 ** Copyright (c) 2015 Digia Plc
 ** For any questions to Digia, please use contact form at http://qt.digia.com/
 **
 ** All Rights Reserved.
 **
 ** NOTICE: All information contained herein is, and remains
 ** the property of Digia Plc and its suppliers,
 ** if any. The intellectual and technical concepts contained
 ** herein are proprietary to Digia Plc
 ** and its suppliers and may be covered by Finnish and Foreign Patents,
 ** patents in process, and are protected by trade secret or copyright law.
 ** Dissemination of this information or reproduction of this material
 ** is strictly forbidden unless prior written permission is obtained
 ** from Digia Plc.
 ****************************************************************************/

#include <QScxml/scxmlparser.h>
#include "scxmlcppdumper.h"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>

enum {
    NoError = 0,
    CommandLineArgumentsError = -1,
    NoInputFilesError = -2,
    CannotOpenInputFileError = -3,
    ParseError = -4,
    CannotOpenOutputHeaderFileError = -5,
    CannotOpenOutputCppFileError = -6,
    ScxmlVerificationError = -7
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    QString usage = QStringLiteral("\nUsage: %1 [-no-c++11] [-namespace <namespace>] [-o <base/out/name>] [-oh <header/out>] [-ocpp <cpp/out>] [-use-private-api]\n").arg(QFileInfo(args.value(0)).baseName());
           usage += QStringLiteral("         [-classname <stateMachineClassName>] [-name-qobjects] <input.scxml>\n\n");
           usage += QStringLiteral("compiles the given input.scxml file to a header and cpp file\n");

    QTextStream errs(stderr, QIODevice::WriteOnly);

    Scxml::CppDumpOptions options;
    QString scxmlFileName;
    QString outFileName;
    QString outHFileName;
    QString outCppFileName;
    for (int iarg = 1; iarg < args.size(); ++iarg) {
        QString arg = args.at(iarg);
        if (arg == QStringLiteral("-no-c++11")) {
            options.useCxx11 = false;
        } else if (arg == QLatin1String("-namespace")) {
            options.namespaceName = args.value(++iarg);
        } else if (arg == QLatin1String("-o")) {
            outFileName = args.value(++iarg);
        } else if (arg == QLatin1String("-oh")) {
            outHFileName = args.value(++iarg);
        } else if (arg == QLatin1String("-ocpp")) {
            outCppFileName = args.value(++iarg);
        } else if (arg == QLatin1String("-use-private-api")) {
            options.usePrivateApi = true;
        } else if (arg == QLatin1String("-classname")) {
            options.classname = args.value(++iarg);
        } else if (arg == QLatin1String("-name-qobjects")) {
            options.nameQObjects = true;
        } else if (scxmlFileName.isEmpty()) {
            scxmlFileName = arg;
        } else {
            errs << QStringLiteral("Unexpected argument: %1").arg(arg) << endl;
            errs << usage;
            exit(CommandLineArgumentsError);
        }
    }
    if (scxmlFileName.isEmpty()) {
        errs << QStringLiteral("Error: no input files.") << endl;
        exit(NoInputFilesError);
    }
    QFile file(scxmlFileName);
    if (!file.open(QFile::ReadOnly)) {
        errs << QStringLiteral("Error: cannot open input file %1").arg(scxmlFileName);
        exit(CannotOpenInputFileError);
    }
    if (outFileName.isEmpty())
        outFileName = QFileInfo(scxmlFileName).baseName();
    if (outHFileName.isEmpty())
        outHFileName = outFileName + QLatin1String(".h");
    if (outCppFileName.isEmpty())
        outCppFileName = outFileName + QLatin1String(".cpp");

    QXmlStreamReader reader(&file);
    Scxml::ScxmlParser parser(&reader,
                              Scxml::ScxmlParser::loaderForDir(QFileInfo(file.fileName()).absolutePath()));
    parser.setFileName(file.fileName());
    parser.parse();
    if (!parser.errors().isEmpty()) {
        foreach (const Scxml::ScxmlError &error, parser.errors()) {
            errs << error.toString() << endl;
        }
        return ParseError;
    }

    auto doc = Scxml::ScxmlParserPrivate::get(&parser)->scxmlDocument();
    if (doc == nullptr) {
        Q_ASSERT(!parser.errors().isEmpty());
        foreach (const Scxml::ScxmlError &error, parser.errors()) {
            errs << error.toString() << endl;
        }
        return ScxmlVerificationError;
    }

    QFile outH(outHFileName);
    if (!outH.open(QFile::WriteOnly)) {
        errs << QStringLiteral("Error: cannot open '%1': %2").arg(outH.fileName(), outH.errorString()) << endl;
        exit(CannotOpenOutputHeaderFileError);
    }

    QFile outCpp(outCppFileName);
    if (!outCpp.open(QFile::WriteOnly)) {
        errs << QStringLiteral("Error: cannot open '%1': %2").arg(outCpp.fileName(), outCpp.errorString()) << endl;
        exit(CannotOpenOutputCppFileError);
    }

    QTextStream h(&outH);
    QTextStream c(&outCpp);
    Scxml::CppDumper dumper(h, c, QFileInfo(outH).fileName(), options);
    dumper.dump(doc);
    outH.close();
    outCpp.close();
    return NoError;
}
