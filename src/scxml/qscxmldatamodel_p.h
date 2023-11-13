// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial

#ifndef QSCXMLDATAMODEL_P_H
#define QSCXMLDATAMODEL_P_H

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

#include "qscxmldatamodel.h"
#include "qscxmlcompiler_p.h"
#include <private/qobject_p.h>
#include <private/qproperty_p.h>

QT_BEGIN_NAMESPACE

class QScxmlDataModelPrivate : public QObjectPrivate
{
    Q_DECLARE_PUBLIC(QScxmlDataModel)
public:
    QScxmlDataModelPrivate() = default;

    static QScxmlDataModel *instantiateDataModel(DocumentModel::Scxml::DataModelType type);

    void setStateMachine(QScxmlStateMachine* stateMachine)
    {
        q_func()->setStateMachine(stateMachine);
    }

    void emitStateMachineChanged(QScxmlStateMachine* newValue)
    {
        emit q_func()->stateMachineChanged(newValue);
    }

    Q_OBJECT_COMPAT_PROPERTY_WITH_ARGS(QScxmlDataModelPrivate, QScxmlStateMachine*, m_stateMachine,
                                       &QScxmlDataModelPrivate::setStateMachine,
                                       &QScxmlDataModelPrivate::emitStateMachineChanged, nullptr)
};

QT_END_NAMESPACE

#endif // QSCXMLDATAMODEL_P_H
