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

#ifndef EVENTCONNECTION_P_H
#define EVENTCONNECTION_P_H

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

#include <QtScxml/qscxmlstatemachine.h>
#include <QtCore/qobject.h>
#include <QtQml/qqmlparserstatus.h>

QT_BEGIN_NAMESPACE

class QScxmlEventConnection : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QStringList events READ events WRITE setEvents NOTIFY eventsChanged)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine WRITE setStateMachine
               NOTIFY stateMachineChanged)
    Q_INTERFACES(QQmlParserStatus)

public:
    QScxmlEventConnection(QObject *parent = nullptr);

    QStringList events() const;
    void setEvents(const QStringList &events);

    QScxmlStateMachine *stateMachine() const;
    void setStateMachine(QScxmlStateMachine *stateMachine);

Q_SIGNALS:
    void eventsChanged();
    void stateMachineChanged();

    void occurred(const QScxmlEvent &event);

private:
    QScxmlStateMachine *m_stateMachine;
    QStringList m_events;

    QList<QMetaObject::Connection> m_connections;

    void doConnect();
    void classBegin() override;
    void componentComplete() override;
};

QT_END_NAMESPACE

#endif // EVENTCONNECTION_P_H
