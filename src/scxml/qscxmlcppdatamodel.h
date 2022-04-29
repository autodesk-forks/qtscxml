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

#ifndef QSCXMLCPPDATAMODEL_H
#define QSCXMLCPPDATAMODEL_H

#include <QtScxml/qscxmldatamodel.h>

#define Q_SCXML_DATAMODEL \
    public: \
        QString evaluateToString(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final; \
        bool evaluateToBool(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final; \
        QVariant evaluateToVariant(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final; \
        void evaluateToVoid(QScxmlExecutableContent::EvaluatorId id, bool *ok) override final; \
    private:

QT_BEGIN_NAMESPACE

class QScxmlCppDataModelPrivate;
class Q_SCXML_EXPORT QScxmlCppDataModel: public QScxmlDataModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QScxmlCppDataModel)
public:
    explicit QScxmlCppDataModel(QObject *parent = nullptr);

    Q_INVOKABLE bool setup(const QVariantMap &initialDataValues) override;

    void evaluateAssignment(QScxmlExecutableContent::EvaluatorId id, bool *ok) override;
    void evaluateInitialization(QScxmlExecutableContent::EvaluatorId id, bool *ok) override;
    void evaluateForeach(QScxmlExecutableContent::EvaluatorId id, bool *ok, ForeachLoopBody *body) override;

    void setScxmlEvent(const QScxmlEvent &scxmlEvent) override final;
    const QScxmlEvent &scxmlEvent() const;

    QVariant scxmlProperty(const QString &name) const override;
    bool hasScxmlProperty(const QString &name) const override;
    bool setScxmlProperty(const QString &name, const QVariant &value, const QString &context) override;

    bool inState(const QString &stateName) const;
};

QT_END_NAMESPACE

#endif // QSCXMLCPPDATAMODEL_H
