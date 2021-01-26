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

#ifndef QSCXMLECMASCRIPTPLATFORMPROPERTIES_P_H
#define QSCXMLECMASCRIPTPLATFORMPROPERTIES_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qscxmlglobals.h"

#include <QtCore/qobject.h>

QT_FORWARD_DECLARE_CLASS(QJSEngine)
QT_FORWARD_DECLARE_CLASS(QJSValue)

QT_REQUIRE_CONFIG(scxml_ecmascriptdatamodel);

QT_BEGIN_NAMESPACE

class QScxmlStateMachine;
class QScxmlPlatformProperties: public QObject
{
    Q_OBJECT

    QScxmlPlatformProperties(QObject *parent);

    Q_PROPERTY(QString marks READ marks CONSTANT)

public:
    static QScxmlPlatformProperties *create(QJSEngine *engine, QScxmlStateMachine *stateMachine);
    ~QScxmlPlatformProperties();

    QJSEngine *engine() const;
    QScxmlStateMachine *stateMachine() const;
    QJSValue jsValue() const;

    QString marks() const;

    Q_INVOKABLE bool inState(const QString &stateName);

private:
    class Data;
    Data *data;
};

QT_END_NAMESPACE

#endif // QSCXMLECMASCRIPTPLATFORMPROPERTIES_P_H
