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

#include "qscxmlecmascriptplatformproperties_p.h"
#include "qscxmlstatemachine.h"

#include <qjsengine.h>

QT_BEGIN_NAMESPACE
class QScxmlPlatformProperties::Data
{
public:
    Data()
        : m_stateMachine(nullptr)
    {}

    QScxmlStateMachine *m_stateMachine;
    QJSValue m_jsValue;
};

QScxmlPlatformProperties::QScxmlPlatformProperties(QObject *parent)
    : QObject(parent)
    , data(new Data)
{}

QScxmlPlatformProperties *QScxmlPlatformProperties::create(QJSEngine *engine, QScxmlStateMachine *stateMachine)
{
    QScxmlPlatformProperties *pp = new QScxmlPlatformProperties(engine);
    pp->data->m_stateMachine = stateMachine;
    pp->data->m_jsValue = engine->newQObject(pp);
    return pp;
}

QScxmlPlatformProperties::~QScxmlPlatformProperties()
{
    delete data;
}

QJSEngine *QScxmlPlatformProperties::engine() const
{
    return qobject_cast<QJSEngine *>(parent());
}

QScxmlStateMachine *QScxmlPlatformProperties::stateMachine() const
{
    return data->m_stateMachine;
}

QJSValue QScxmlPlatformProperties::jsValue() const
{
    return data->m_jsValue;
}

/// _x.marks === "the spot"
QString QScxmlPlatformProperties::marks() const
{
    return QStringLiteral("the spot");
}

bool QScxmlPlatformProperties::inState(const QString &stateName)
{
    return stateMachine()->isActive(stateName);
}

QT_END_NAMESPACE
