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

#ifndef QSCXMLECMASCRIPTDATAMODEL_P_H
#define QSCXMLECMASCRIPTDATAMODEL_P_H

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

#include <QObject>
#include <QtScxml/qscxmlglobals.h>
#include <QtScxml/qscxmldatamodel.h>

QT_BEGIN_NAMESPACE


class QScxmlEcmaScriptDataModelPrivate;
class QScxmlEcmaScriptDataModel: public QScxmlDataModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlEcmaScriptDataModel)
public:
    explicit QScxmlEcmaScriptDataModel(QObject *parent = nullptr);

    Q_INVOKABLE bool setup(const QVariantMap &initialDataValues) override;

    QString evaluateToString(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    bool evaluateToBool(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    QVariant evaluateToVariant(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    void evaluateToVoid(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    void evaluateAssignment(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    void evaluateInitialization(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final;
    void evaluateForeach(QScxmlExecutableContent::EvaluatorId id, bool *ok, ForeachLoopBody *body) override final;

    void setScxmlEvent(const QScxmlEvent &event) override;

    QVariant scxmlProperty(const QString &name) const override;
    bool hasScxmlProperty(const QString &name) const override;
    bool setScxmlProperty(const QString &name, const QVariant &value, const QString &context) override;
};

QT_END_NAMESPACE

#endif // QSCXMLECMASCRIPTDATAMODEL_P_H
