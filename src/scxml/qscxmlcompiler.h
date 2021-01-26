/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#ifndef QSCXMLCOMPILER_H
#define QSCXMLCOMPILER_H

#include <QtScxml/qscxmlerror.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE
class QXmlStreamReader;
class QScxmlStateMachine;

class QScxmlCompilerPrivate;
class Q_SCXML_EXPORT QScxmlCompiler
{
public:
    class Q_SCXML_EXPORT Loader
    {
    public:
        Loader();
        virtual ~Loader();
        virtual QByteArray load(const QString &name,
                                const QString &baseDir,
                                QStringList *errors) = 0;
    };

public:
    QScxmlCompiler(QXmlStreamReader *xmlReader);
    ~QScxmlCompiler();

    QString fileName() const;
    void setFileName(const QString &fileName);

    Loader *loader() const;
    void setLoader(Loader *newLoader);

    QScxmlStateMachine *compile();
    QVector<QScxmlError> errors() const;

private:
    friend class QScxmlCompilerPrivate;
    QScxmlCompilerPrivate *d;
};

QT_END_NAMESPACE

#endif // QSCXMLCOMPILER_H
