// **********************************************************************
//
// Copyright (c) 2001
// MutableRealms, Inc.
// Huntsville, AL, USA
//
// All Rights Reserved
//
// **********************************************************************

#ifndef ICE_PROXY_H
#define ICE_PROXY_H

#include <IceUtil/Shared.h>
#include <Ice/ProxyF.h>
#include <Ice/ProxyFactoryF.h>
#include <Ice/EmitterF.h>
#include <Ice/ObjectF.h>
#include <Ice/ObjectAdapterF.h>
#include <Ice/ReferenceF.h>

namespace Ice
{

class LocalException;
class LocationForward;

class ICE_API ObjectPrxE
{
public:

    ObjectPrxE() { }
    ObjectPrxE(const ObjectPrxE&);
    explicit ObjectPrxE(const ObjectPrx&);
    operator ObjectPrx() const;
    ::IceProxy::Ice::Object* operator->() const;
    operator bool() const;

protected:

    ObjectPrx _prx;
};

};

namespace IceProxy { namespace Ice
{

class ICE_API Object : public ::IceUtil::Shared, JTCMutex
{
public:

    virtual void _throw();
    bool _isA(const std::string&);
    void _ping();

    bool operator==(const Object&) const;
    bool operator<(const Object&) const;

    std::string _getIdentity() const;
    ::Ice::ObjectPrx _newIdentity(const std::string&) const;

    ::Ice::ObjectPrx _twoway() const;
    ::Ice::ObjectPrx _oneway() const;
    ::Ice::ObjectPrx _batchOneway() const;
    ::Ice::ObjectPrx _datagram() const;
    ::Ice::ObjectPrx _batchDatagram() const;
    ::Ice::ObjectPrx _secure(bool) const;
    ::Ice::ObjectPrx _timeout(int) const;

    void _flush(); // Flush batch messages

    ::IceInternal::ReferencePtr __reference() const;
    void __copyTo(::IceProxy::Ice::Object*) const;
    void __handleException(const ::Ice::LocalException&, int&);
    void __rethrowException(const ::Ice::LocalException&);
    void __locationForward(const ::Ice::LocationForward&);

protected:

    Object();
    virtual ~Object();
    friend class ::IceInternal::ProxyFactory;

    ::IceInternal::Handle< ::IceDelegate::Ice::Object> __getDelegate();
    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();

private:

    void setup(const ::IceInternal::ReferencePtr&);

    ::IceInternal::ReferencePtr _reference;
    ::IceInternal::Handle< ::IceDelegate::Ice::Object> _delegate;
};

} }

namespace IceDelegate { namespace Ice
{

class ICE_API Object : public ::IceUtil::Shared
{
public:

    virtual bool _isA(const std::string&) = 0;
    virtual void _ping() = 0;
    virtual void _flush() = 0;

protected:

    Object();
    virtual ~Object();
    friend class ::IceProxy::Ice::Object;

private:

    virtual void setup(const ::IceInternal::ReferencePtr&) = 0;
};

} }

namespace IceDelegateM { namespace Ice
{

class ICE_API Object : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool _isA(const std::string&);
    virtual void _ping();
    virtual void _flush();

protected:

    Object();
    virtual ~Object();
    friend class ::IceProxy::Ice::Object;

    ::IceInternal::EmitterPtr __emitter;
    ::IceInternal::ReferencePtr __reference;

private:

    virtual void setup(const ::IceInternal::ReferencePtr&);
};

} }

namespace IceDelegateD { namespace Ice
{

class ICE_API Object : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual bool _isA(const std::string&);
    virtual void _ping();
    virtual void _flush();

protected:

    Object();
    virtual ~Object();
    friend class ::IceProxy::Ice::Object;

    ::Ice::ObjectAdapterPtr __adapter;
    ::IceInternal::ReferencePtr __reference;

private:

    virtual void setup(const ::IceInternal::ReferencePtr&);
};

} }

#endif
