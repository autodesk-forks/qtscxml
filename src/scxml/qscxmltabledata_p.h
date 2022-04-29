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

#ifndef QSCXMLTABLEDATA_P_H
#define QSCXMLTABLEDATA_P_H

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

#include <QtScxml/qscxmltabledata.h>
#include <QtCore/qhash.h>
#include <QtCore/qlist.h>
#include <QtCore/qsharedpointer.h>

#include <functional>

QT_BEGIN_NAMESPACE
class QTextStream;
class QScxmlInvokableServiceFactory;

namespace DocumentModel {
struct ScxmlDocument;
}

namespace QScxmlInternal {
class Q_SCXML_EXPORT GeneratedTableData: public QScxmlTableData
{
public:
    typedef std::function<
        int(const QScxmlExecutableContent::InvokeInfo &invokeInfo,
            const QList<QScxmlExecutableContent::StringId> &namelist,
            const QList<QScxmlExecutableContent::ParameterInfo> &params,
            QSharedPointer<DocumentModel::ScxmlDocument> content)
    > CreateFactoryId;

    struct MetaDataInfo {
        QStringList stateNames;
    };

    struct DataModelInfo {
        QHash<QScxmlExecutableContent::EvaluatorId, QString> stringEvaluators;
        QHash<QScxmlExecutableContent::EvaluatorId, QString> boolEvaluators;
        QHash<QScxmlExecutableContent::EvaluatorId, QString> variantEvaluators;
        QHash<QScxmlExecutableContent::EvaluatorId, QString> voidEvaluators;
    };

public:
    static void build(DocumentModel::ScxmlDocument *doc, GeneratedTableData *table,
                      MetaDataInfo *metaDataInfo, DataModelInfo *dataModelInfo,
                      CreateFactoryId func);
    static QString toString(const int *stateMachineTable);

public:
    QString string(QScxmlExecutableContent::StringId id) const override final;
    QScxmlExecutableContent::InstructionId *instructions() const override final;
    QScxmlExecutableContent::EvaluatorInfo evaluatorInfo(
            QScxmlExecutableContent::EvaluatorId evaluatorId) const override final;
    QScxmlExecutableContent::AssignmentInfo assignmentInfo(
            QScxmlExecutableContent::EvaluatorId assignmentId) const override final;
    QScxmlExecutableContent::ForeachInfo foreachInfo(
            QScxmlExecutableContent::EvaluatorId foreachId) const override final;
    QScxmlExecutableContent::StringId *dataNames(int *count) const override final;
    QScxmlExecutableContent::ContainerId initialSetup() const override final;
    QString name() const override final;
    const qint32 *stateMachineTable() const override final;
    QScxmlInvokableServiceFactory *serviceFactory(int id) const override;

public:
    QList<qint32> theStateMachineTable;
    QStringList theStrings;
    QList<qint32> theInstructions;
    QList<QScxmlExecutableContent::EvaluatorInfo> theEvaluators;
    QList<QScxmlExecutableContent::AssignmentInfo> theAssignments;
    QList<QScxmlExecutableContent::ForeachInfo> theForeaches;
    QList<QScxmlExecutableContent::StringId> theDataNameIds;
    QScxmlExecutableContent::ContainerId theInitialSetup;
    int theName;
};
} // QScxmlInternal namespace

QT_END_NAMESPACE

#endif // QSCXMLTABLEDATA_P_H
