/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

#include "invokedservices_p.h"
#include <QtScxml/qscxmlinvokableservice.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype InvokedServices
    \instantiates QScxmlInvokedServices
    \inqmlmodule QtScxml
    \since QtScxml 5.8

    \brief Provices access to the services invoked by state machines.

    Makes the invoked services easily accessible by their names, without
    constantly iterating through QScxmlStateMachine::invokedServices.

    The services are called from state machines via the mechanism described in
    \l{SCXML Specification - 6.4 <invoke>}.
*/

QScxmlInvokedServices::QScxmlInvokedServices(QObject *parent) : QObject(parent)
{
}

/*!
    \qmlproperty var InvokedServices::children

    The services invoked by the state machine.
*/

QVariantMap QScxmlInvokedServices::children()
{
    return m_children.value();
}

QVariantMap QScxmlInvokedServices::childrenActualCalculation() const
{
    QVariantMap ret;
    if (m_stateMachine.value()) {
        const QList<QScxmlInvokableService *> children = m_stateMachine->invokedServices();
        for (QScxmlInvokableService *service : children)
            ret.insert(service->name(), QVariant::fromValue(service));
    }
    return ret;
}

QBindable<QVariantMap> QScxmlInvokedServices::bindableChildren()
{
    return &m_children;
}

void QScxmlInvokedServices::classBegin()
{
}

/*!
    \qmlproperty ScxmlStateMachine InvokedServices::stateMachine

    The state machine that invoked the services.
*/

QScxmlStateMachine *QScxmlInvokedServices::stateMachine() const
{
    return m_stateMachine;
}

void QScxmlInvokedServices::setStateMachine(QScxmlStateMachine *stateMachine)
{
    if (stateMachine == m_stateMachine.value()) {
        m_stateMachine.removeBindingUnlessInWrapper();
        return;
    }

    QObject::disconnect(m_serviceConnection);
    m_stateMachine = stateMachine;

    if (m_stateMachine.value()) {
        m_serviceConnection = QObject::connect(
                    m_stateMachine.value(), &QScxmlStateMachine::invokedServicesChanged,
                    [this](){
            m_children.notify();
            emit childrenChanged();
        });
    }
    m_stateMachine.notify();
    m_children.notify();
    emit childrenChanged();
}

QBindable<QScxmlStateMachine*> QScxmlInvokedServices::bindableStateMachine()
{
    return &m_stateMachine;
}

/*!
    \qmlproperty list<QtObject> InvokedServices::qmlChildren

    A list of additional QtObject types nested in this type.
*/

QQmlListProperty<QObject> QScxmlInvokedServices::qmlChildren()
{
    return QQmlListProperty<QObject>(this, &m_qmlChildren);
}

void QScxmlInvokedServices::componentComplete()
{
    if (!m_stateMachine.value())
        setStateMachine(qobject_cast<QScxmlStateMachine *>(parent()));
}

QT_END_NAMESPACE
