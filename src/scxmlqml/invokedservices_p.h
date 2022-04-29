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

#ifndef INVOKEDSERVICES_P_H
#define INVOKEDSERVICES_P_H

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

#include "qscxmlqmlglobals_p.h"

#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmllist.h>
#include <QtQml/qqml.h>
#include <QtScxml/qscxmlstatemachine.h>
#include <QtCore/qproperty.h>
#include <private/qproperty_p.h>

QT_BEGIN_NAMESPACE

class Q_SCXMLQML_PRIVATE_EXPORT QScxmlInvokedServices : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine WRITE setStateMachine
               NOTIFY stateMachineChanged BINDABLE bindableStateMachine)
    Q_PROPERTY(QVariantMap children READ children NOTIFY childrenChanged BINDABLE bindableChildren)
    Q_PROPERTY(QQmlListProperty<QObject> qmlChildren READ qmlChildren)
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "qmlChildren")
    QML_NAMED_ELEMENT(InvokedServices)
    QML_ADDED_IN_VERSION(5,8)

public:
    QScxmlInvokedServices(QObject *parent = nullptr);

    QVariantMap children();
    QBindable<QVariantMap> bindableChildren();

    QScxmlStateMachine *stateMachine() const;
    void setStateMachine(QScxmlStateMachine *stateMachine);
    QBindable<QScxmlStateMachine*> bindableStateMachine();

    QQmlListProperty<QObject> qmlChildren();

Q_SIGNALS:
    void childrenChanged();
    void stateMachineChanged();

private:
    void classBegin() override;
    void componentComplete() override;
    QVariantMap childrenActualCalculation() const;

    Q_OBJECT_COMPAT_PROPERTY_WITH_ARGS(QScxmlInvokedServices, QScxmlStateMachine*, m_stateMachine,
                                      &QScxmlInvokedServices::setStateMachine,
                                      &QScxmlInvokedServices::stateMachineChanged, nullptr);
    Q_OBJECT_COMPUTED_PROPERTY(QScxmlInvokedServices, QVariantMap,
                               m_children, &QScxmlInvokedServices::childrenActualCalculation);
    QMetaObject::Connection m_serviceConnection;
    QList<QObject *> m_qmlChildren;
};

QT_END_NAMESPACE

#endif // INVOKEDSERVICES_P_H
