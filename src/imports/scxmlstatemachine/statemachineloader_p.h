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

#include <QtCore/qurl.h>
#include <QtScxml/qscxmlstatemachine.h>
#include <private/qqmlengine_p.h>

QT_BEGIN_NAMESPACE

class QScxmlStateMachineLoader: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QScxmlStateMachine *stateMachine READ stateMachine DESIGNABLE false NOTIFY stateMachineChanged)
    Q_PROPERTY(QVariantMap initialValues READ initialValues WRITE setInitialValues NOTIFY initialValuesChanged)
    Q_PROPERTY(QScxmlDataModel *dataModel READ dataModel WRITE setDataModel NOTIFY dataModelChanged)


public:
    explicit QScxmlStateMachineLoader(QObject *parent = nullptr);

    QScxmlStateMachine *stateMachine() const;

    QUrl source();
    void setSource(const QUrl &source);

    QVariantMap initialValues() const;
    void setInitialValues(const QVariantMap &initialValues);

    QScxmlDataModel *dataModel() const;
    void setDataModel(QScxmlDataModel *dataModel);

Q_SIGNALS:
    void sourceChanged();
    void initialValuesChanged();
    void stateMachineChanged();
    void dataModelChanged();

private:
    bool parse(const QUrl &source);

private:
    QUrl m_source;
    QVariantMap m_initialValues;
    QScxmlDataModel *m_dataModel;
    QScxmlDataModel *m_implicitDataModel;
    QScxmlStateMachine *m_stateMachine;
};

QT_END_NAMESPACE

#endif // STATEMACHINELOADER_P_H
