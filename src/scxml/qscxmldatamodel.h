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

#ifndef QSCXMLDATAMODEL_H
#define QSCXMLDATAMODEL_H

#include <QtScxml/qscxmlexecutablecontent.h>

#include <QtCore/qvariant.h>
#include <QtCore/qvector.h>

QT_BEGIN_NAMESPACE

class QScxmlEvent;

class QScxmlStateMachine;
class QScxmlTableData;

class QScxmlDataModelPrivate;
class Q_SCXML_EXPORT QScxmlDataModel : public QObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlDataModel)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine WRITE setStateMachine NOTIFY stateMachineChanged)

public:
    class Q_SCXML_EXPORT ForeachLoopBody
    {
        Q_DISABLE_COPY(ForeachLoopBody)
    public:
        ForeachLoopBody();
        virtual ~ForeachLoopBody();
        virtual void run(bool *ok) = 0;
    };

public:
    explicit QScxmlDataModel(QObject *parent = nullptr);

    void setStateMachine(QScxmlStateMachine *stateMachine);
    QScxmlStateMachine *stateMachine() const;

    Q_INVOKABLE virtual bool setup(const QVariantMap &initialDataValues) = 0;

    virtual QString evaluateToString(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual bool evaluateToBool(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual QVariant evaluateToVariant(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual void evaluateToVoid(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual void evaluateAssignment(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual void evaluateInitialization(QScxmlExecutableContent::EvaluatorId id, bool *ok) = 0;
    virtual void evaluateForeach(QScxmlExecutableContent::EvaluatorId id, bool *ok, ForeachLoopBody *body) = 0;

    virtual void setScxmlEvent(const QScxmlEvent &event) = 0;

    virtual QVariant scxmlProperty(const QString &name) const = 0;
    virtual bool hasScxmlProperty(const QString &name) const = 0;
    virtual bool setScxmlProperty(const QString &name, const QVariant &value, const QString &context) = 0;

Q_SIGNALS:
    void stateMachineChanged(QScxmlStateMachine *stateMachine);

protected:
    explicit QScxmlDataModel(QScxmlDataModelPrivate &dd, QObject *parent = nullptr);
};

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QScxmlDataModel *)

#endif // QSCXMLDATAMODEL_H
