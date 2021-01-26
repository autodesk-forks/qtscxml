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

#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqmllist.h>
#include <QtScxml/qscxmlstatemachine.h>

QT_BEGIN_NAMESPACE

class QScxmlInvokedServices : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine WRITE setStateMachine
               NOTIFY stateMachineChanged)
    Q_PROPERTY(QVariantMap children READ children NOTIFY childrenChanged)
    Q_PROPERTY(QQmlListProperty<QObject> qmlChildren READ qmlChildren)
    Q_INTERFACES(QQmlParserStatus)
    Q_CLASSINFO("DefaultProperty", "qmlChildren")
public:
    QScxmlInvokedServices(QObject *parent = nullptr);
    QVariantMap children();

    QScxmlStateMachine *stateMachine() const;
    void setStateMachine(QScxmlStateMachine *stateMachine);

    QQmlListProperty<QObject> qmlChildren();

Q_SIGNALS:
    void childrenChanged();
    void stateMachineChanged();

private:
    void classBegin() override;
    void componentComplete() override;

    QScxmlStateMachine *m_stateMachine = nullptr;
    QList<QObject *> m_qmlChildren;
};

QT_END_NAMESPACE

#endif // INVOKEDSERVICES_P_H
