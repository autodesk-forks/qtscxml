/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QSIGNALTRANSITION_H
#define QSIGNALTRANSITION_H

#include <QtCore/qmetaobject.h>
#include <QtStateMachine/qabstracttransition.h>

QT_REQUIRE_CONFIG(statemachine);

QT_BEGIN_NAMESPACE

class QSignalTransitionPrivate;
class Q_STATEMACHINE_EXPORT QSignalTransition : public QAbstractTransition
{
    Q_OBJECT
    Q_PROPERTY(const QObject* senderObject READ senderObject WRITE setSenderObject
               NOTIFY senderObjectChanged BINDABLE bindableSenderObject)
    Q_PROPERTY(QByteArray signal READ signal WRITE setSignal
               NOTIFY signalChanged BINDABLE bindableSignal)

public:
    QSignalTransition(QState *sourceState = nullptr);
    QSignalTransition(const QObject *sender, const char *signal,
                      QState *sourceState = nullptr);
#ifdef Q_QDOC
    template<typename PointerToMemberFunction>
    QSignalTransition(const QObject *object, PointerToMemberFunction signal,
                      QState *sourceState = nullptr);
#elif defined(Q_COMPILER_DELEGATING_CONSTRUCTORS)
    template <typename Func>
    QSignalTransition(const typename QtPrivate::FunctionPointer<Func>::Object *obj,
                      Func sig, QState *srcState = nullptr)
    : QSignalTransition(obj, QMetaMethod::fromSignal(sig).methodSignature().constData(), srcState)
    {
    }
#endif

    ~QSignalTransition();

    const QObject *senderObject() const;
    void setSenderObject(const QObject *sender);
    QBindable<const QObject*> bindableSenderObject();

    QByteArray signal() const;
    void setSignal(const QByteArray &signal);
    QBindable<QByteArray> bindableSignal();

protected:
    bool eventTest(QEvent *event) override;
    void onTransition(QEvent *event) override;

    bool event(QEvent *e) override;

Q_SIGNALS:
    void senderObjectChanged(QPrivateSignal);
    void signalChanged(QPrivateSignal);

private:
    Q_DISABLE_COPY(QSignalTransition)
    Q_DECLARE_PRIVATE(QSignalTransition)
};

QT_END_NAMESPACE

#endif
