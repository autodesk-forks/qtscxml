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

#ifndef QSCXMLINVOKABLESERVICE_H
#define QSCXMLINVOKABLESERVICE_H

#include <QtScxml/qscxmldatamodel.h>
#include <QtCore/qstring.h>

QT_BEGIN_NAMESPACE

class QScxmlEvent;
class QScxmlStateMachine;

class QScxmlInvokableServiceFactory;
class QScxmlInvokableServicePrivate;
class Q_SCXML_EXPORT QScxmlInvokableService : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlInvokableService)
    Q_PROPERTY(QScxmlStateMachine *parentStateMachine READ parentStateMachine CONSTANT)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)

public:
    QScxmlInvokableService(QScxmlStateMachine *parentStateMachine,
                           QScxmlInvokableServiceFactory *parent);

    QScxmlStateMachine *parentStateMachine() const;

    virtual bool start() = 0;
    virtual QString id() const = 0;
    virtual QString name() const = 0;
    virtual void postEvent(QScxmlEvent *event) = 0;
};

class QScxmlInvokableServiceFactoryPrivate;
class Q_SCXML_EXPORT QScxmlInvokableServiceFactory : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlInvokableServiceFactory)
    Q_PROPERTY(QScxmlExecutableContent::InvokeInfo invokeInfo READ invokeInfo CONSTANT)
    Q_PROPERTY(QVector<QScxmlExecutableContent::ParameterInfo> parameters READ parameters CONSTANT)
    Q_PROPERTY(QVector<QScxmlExecutableContent::StringId> names READ names CONSTANT)

public:
    QScxmlInvokableServiceFactory(
            const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QVector<QScxmlExecutableContent::StringId> &names,
            const QVector<QScxmlExecutableContent::ParameterInfo> &parameters,
            QObject *parent = nullptr);

    virtual QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) = 0;
    const QScxmlExecutableContent::InvokeInfo &invokeInfo() const;
    const QVector<QScxmlExecutableContent::ParameterInfo> &parameters() const;
    const QVector<QScxmlExecutableContent::StringId> &names() const;

protected:
    QScxmlInvokableServiceFactory(QScxmlInvokableServiceFactoryPrivate &dd, QObject *parent);
};

class QScxmlStaticScxmlServiceFactoryPrivate;
class Q_SCXML_EXPORT QScxmlStaticScxmlServiceFactory: public QScxmlInvokableServiceFactory
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlStaticScxmlServiceFactory)
public:
    QScxmlStaticScxmlServiceFactory(
            const QMetaObject *metaObject,
            const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QVector<QScxmlExecutableContent::StringId> &nameList,
            const QVector<QScxmlExecutableContent::ParameterInfo> &parameters,
            QObject *parent = nullptr);

    QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) override;
};

class Q_SCXML_EXPORT QScxmlDynamicScxmlServiceFactory: public QScxmlInvokableServiceFactory
{
    Q_OBJECT
public:
    QScxmlDynamicScxmlServiceFactory(
            const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QVector<QScxmlExecutableContent::StringId> &names,
            const QVector<QScxmlExecutableContent::ParameterInfo> &parameters,
            QObject *parent = nullptr);

    QScxmlInvokableService *invoke(QScxmlStateMachine *parentStateMachine) override;
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QScxmlInvokableService *)

#endif // QSCXMLINVOKABLESERVICE_H
