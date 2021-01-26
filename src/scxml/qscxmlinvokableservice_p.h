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

#ifndef QSCXMLINVOKABLESERVICE_P_H
#define QSCXMLINVOKABLESERVICE_P_H

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

#include "qscxmlinvokableservice.h"
#include <QtCore/private/qobject_p.h>

QT_BEGIN_NAMESPACE

class QScxmlInvokableServicePrivate : public QObjectPrivate
{
public:
    QScxmlInvokableServicePrivate(QScxmlStateMachine *parentStateMachine);

    QString calculateId(QScxmlStateMachine *parent,
                        const QScxmlExecutableContent::InvokeInfo &invokeInfo, bool *ok) const;
    QVariantMap calculateData(QScxmlStateMachine *parent,
                              const QVector<QScxmlExecutableContent::ParameterInfo> &parameters,
                              const QVector<QScxmlExecutableContent::StringId> &names,
                              bool *ok) const;

    QScxmlStateMachine *parentStateMachine;
};

class QScxmlInvokableServiceFactoryPrivate : public QObjectPrivate
{
public:
    QScxmlInvokableServiceFactoryPrivate(
            const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QVector<QScxmlExecutableContent::StringId> &names,
            const QVector<QScxmlExecutableContent::ParameterInfo> &parameters);

    QScxmlExecutableContent::InvokeInfo invokeInfo;
    QVector<QScxmlExecutableContent::StringId> names;
    QVector<QScxmlExecutableContent::ParameterInfo> parameters;
};

class Q_SCXML_EXPORT QScxmlScxmlService: public QScxmlInvokableService
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlInvokableService)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine CONSTANT)
public:
    QScxmlScxmlService(QScxmlStateMachine *stateMachine,
                       QScxmlStateMachine *parentStateMachine,
                       QScxmlInvokableServiceFactory *parent);
    ~QScxmlScxmlService();

    bool start() override;
    QString id() const override;
    QString name() const override;
    void postEvent(QScxmlEvent *event) override;
    QScxmlStateMachine *stateMachine() const;

private:
    QScxmlStateMachine *m_stateMachine;
};

class QScxmlStaticScxmlServiceFactoryPrivate : public QScxmlInvokableServiceFactoryPrivate
{
public:
    QScxmlStaticScxmlServiceFactoryPrivate(
            const QMetaObject *metaObject,
            const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QVector<QScxmlExecutableContent::StringId> &names,
            const QVector<QScxmlExecutableContent::ParameterInfo> &parameters);

    const QMetaObject *metaObject;
};

QScxmlScxmlService *invokeDynamicScxmlService(const QString &sourceUrl,
                                              QScxmlStateMachine *parentStateMachine,
                                              QScxmlInvokableServiceFactory *factory);
QScxmlScxmlService *invokeStaticScxmlService(QScxmlStateMachine *childStateMachine,
                                             QScxmlStateMachine *parentStateMachine,
                                             QScxmlInvokableServiceFactory *factory);
QString calculateSrcexpr(QScxmlStateMachine *parent, QScxmlExecutableContent::EvaluatorId srcexpr,
                         bool *ok);

QT_END_NAMESPACE

#endif // QSCXMLINVOKABLESERVICE_P_H
