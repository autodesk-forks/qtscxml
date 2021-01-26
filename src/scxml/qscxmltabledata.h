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

#ifndef QSCXMLTABLEDATA_H
#define QSCXMLTABLEDATA_H

#include <QtScxml/qscxmlexecutablecontent.h>
#include <QtCore/qstring.h>

#ifndef Q_QSCXMLC_OUTPUT_REVISION
#define Q_QSCXMLC_OUTPUT_REVISION 1
#endif

QT_BEGIN_NAMESPACE

class QScxmlInvokableServiceFactory;

class Q_SCXML_EXPORT QScxmlTableData
{
public:
    virtual ~QScxmlTableData();

    virtual QString string(QScxmlExecutableContent::StringId id) const = 0;
    virtual QScxmlExecutableContent::InstructionId *instructions() const = 0;
    virtual QScxmlExecutableContent::EvaluatorInfo evaluatorInfo(QScxmlExecutableContent::EvaluatorId evaluatorId) const = 0;
    virtual QScxmlExecutableContent::AssignmentInfo assignmentInfo(QScxmlExecutableContent::EvaluatorId assignmentId) const = 0;
    virtual QScxmlExecutableContent::ForeachInfo foreachInfo(QScxmlExecutableContent::EvaluatorId foreachId) const = 0;
    virtual QScxmlExecutableContent::StringId *dataNames(int *count) const = 0;

    virtual QScxmlExecutableContent::ContainerId initialSetup() const = 0;
    virtual QString name() const = 0;

    virtual const qint32 *stateMachineTable() const = 0;
    virtual QScxmlInvokableServiceFactory *serviceFactory(int id) const = 0;
};

QT_END_NAMESPACE

#endif // QSCXMLTABLEDATA_H
