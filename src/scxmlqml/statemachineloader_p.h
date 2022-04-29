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

#ifndef STATEMACHINELOADER_P_H
#define STATEMACHINELOADER_P_H

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

#include <QtCore/qurl.h>
#include <QtScxml/qscxmlstatemachine.h>

#include <QtCore/private/qproperty_p.h>
#include <QtQml/qqml.h>

QT_BEGIN_NAMESPACE

class Q_SCXMLQML_PRIVATE_EXPORT QScxmlStateMachineLoader: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource
               NOTIFY sourceChanged BINDABLE bindableSource)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine DESIGNABLE false
               NOTIFY stateMachineChanged BINDABLE bindableStateMachine)
    Q_PROPERTY(QVariantMap initialValues READ initialValues WRITE setInitialValues
               NOTIFY initialValuesChanged BINDABLE bindableInitialValues)
    Q_PROPERTY(QScxmlDataModel *dataModel READ dataModel
               WRITE setDataModel NOTIFY dataModelChanged BINDABLE bindableDataModel)
    QML_NAMED_ELEMENT(StateMachineLoader)
    QML_ADDED_IN_VERSION(5,8)

public:
    explicit QScxmlStateMachineLoader(QObject *parent = nullptr);

    QScxmlStateMachine *stateMachine() const;
    QBindable<QScxmlStateMachine*> bindableStateMachine();

    QUrl source();
    void setSource(const QUrl &source);
    QBindable<QUrl> bindableSource();

    QVariantMap initialValues() const;
    void setInitialValues(const QVariantMap &initialValues);
    QBindable<QVariantMap> bindableInitialValues();

    QScxmlDataModel *dataModel() const;
    void setDataModel(QScxmlDataModel *dataModel);
    QBindable<QScxmlDataModel*> bindableDataModel();

Q_SIGNALS:
    void sourceChanged();
    void initialValuesChanged();
    void stateMachineChanged();
    void dataModelChanged();

private:
    bool parse(const QUrl &source);
    void setStateMachine(QScxmlStateMachine* stateMachine);

private:
    Q_OBJECT_COMPAT_PROPERTY(QScxmlStateMachineLoader, QUrl,
                             m_source, &QScxmlStateMachineLoader::setSource,
                             &QScxmlStateMachineLoader::sourceChanged);
    Q_OBJECT_COMPAT_PROPERTY(QScxmlStateMachineLoader, QVariantMap,
                             m_initialValues, &QScxmlStateMachineLoader::setInitialValues,
                             &QScxmlStateMachineLoader::initialValuesChanged);
    Q_OBJECT_COMPAT_PROPERTY_WITH_ARGS(QScxmlStateMachineLoader, QScxmlDataModel*,
                             m_dataModel, &QScxmlStateMachineLoader::setDataModel,
                             &QScxmlStateMachineLoader::dataModelChanged, nullptr);
    Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(QScxmlStateMachineLoader, QScxmlStateMachine*,
                             m_stateMachine, nullptr, &QScxmlStateMachineLoader::stateMachineChanged);
    QScxmlDataModel *m_implicitDataModel;
};

QT_END_NAMESPACE

#endif // STATEMACHINELOADER_P_H
