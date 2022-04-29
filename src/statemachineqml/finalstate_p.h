/****************************************************************************
**
** Copyright (C) 2016 Ford Motor Company
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
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

#ifndef QQMLFINALSTATE_H
#define QQMLFINALSTATE_H

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

#include "qstatemachineqmlglobals_p.h"
#include "childrenprivate_p.h"
#include "statemachine_p.h"

#include <QtCore/private/qproperty_p.h>
#include <QtStateMachine/QFinalState>
#include <QtQml/QQmlListProperty>
#include <QtQml/qqml.h>


QT_BEGIN_NAMESPACE

class Q_STATEMACHINEQML_PRIVATE_EXPORT FinalState : public QFinalState
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> children READ children
               NOTIFY childrenChanged BINDABLE bindableChildren)
    Q_CLASSINFO("DefaultProperty", "children")
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 0)

public:
    explicit FinalState(QState *parent = 0);

    QQmlListProperty<QObject> children();
    QBindable<QQmlListProperty<QObject>> bindableChildren() const;

Q_SIGNALS:
    void childrenChanged();

private:
    // See the childrenActualCalculation for the mutable explanation
    mutable ChildrenPrivate<FinalState, ChildrenMode::State> m_children;
    friend ChildrenPrivate<FinalState, ChildrenMode::State>;
    void childrenContentChanged();
    QQmlListProperty<QObject> childrenActualCalculation() const;
    Q_OBJECT_COMPUTED_PROPERTY(FinalState, QQmlListProperty<QObject>, m_childrenComputedProperty,
                               &FinalState::childrenActualCalculation);
};

QT_END_NAMESPACE
#endif
