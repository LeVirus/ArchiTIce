// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.6.1
//
// <auto-generated>
//
// Generated from file `Communicator.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#ifndef __Ice_Communicator_h__
#define __Ice_Communicator_h__

#include <IceUtil/PushDisableWarnings.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/StreamHelpers.h>
#include <Ice/Proxy.h>
#include <Ice/GCObject.h>
#include <Ice/AsyncResult.h>
#include <Ice/Incoming.h>
#include <Ice/IncomingAsync.h>
#include <IceUtil/ScopedArray.h>
#include <IceUtil/Optional.h>
#include <Ice/StreamF.h>
#include <Ice/LoggerF.h>
#include <Ice/InstrumentationF.h>
#include <Ice/ObjectAdapterF.h>
#include <Ice/ObjectFactoryF.h>
#include <Ice/RouterF.h>
#include <Ice/LocatorF.h>
#include <Ice/PluginF.h>
#include <Ice/ImplicitContextF.h>
#include <Ice/Current.h>
#include <Ice/Properties.h>
#include <Ice/FacetMap.h>
#include <IceUtil/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 306
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

#ifndef ICE_API
#   ifdef ICE_API_EXPORTS
#       define ICE_API ICE_DECLSPEC_EXPORT
#   elif defined(ICE_STATIC_LIBS)
#       define ICE_API /**/
#   else
#       define ICE_API ICE_DECLSPEC_IMPORT
#   endif
#endif

namespace IceProxy
{

}

namespace Ice
{

class Communicator;
bool operator==(const Communicator&, const Communicator&);
bool operator<(const Communicator&, const Communicator&);
ICE_API ::Ice::LocalObject* upCast(::Ice::Communicator*);
typedef ::IceInternal::Handle< ::Ice::Communicator> CommunicatorPtr;

}

namespace IceAsync
{

}

namespace Ice
{

class Callback_Communicator_flushBatchRequests_Base : virtual public ::IceInternal::CallbackBase { };
typedef ::IceUtil::Handle< Callback_Communicator_flushBatchRequests_Base> Callback_Communicator_flushBatchRequestsPtr;

}

namespace IceProxy
{

}

namespace Ice
{

class ICE_API Communicator : virtual public ::Ice::LocalObject
{
public:

    typedef CommunicatorPtr PointerType;

    virtual void destroy() = 0;

    virtual void shutdown() = 0;

    virtual void waitForShutdown() = 0;

    virtual bool isShutdown() const = 0;

    virtual ::Ice::ObjectPrx stringToProxy(const ::std::string&) const = 0;

    virtual ::std::string proxyToString(const ::Ice::ObjectPrx&) const = 0;

    virtual ::Ice::ObjectPrx propertyToProxy(const ::std::string&) const = 0;

    virtual ::Ice::PropertyDict proxyToProperty(const ::Ice::ObjectPrx&, const ::std::string&) const = 0;

    virtual ::Ice::Identity stringToIdentity(const ::std::string&) const = 0;

    virtual ::std::string identityToString(const ::Ice::Identity&) const = 0;

    virtual ::Ice::ObjectAdapterPtr createObjectAdapter(const ::std::string&) = 0;

    virtual ::Ice::ObjectAdapterPtr createObjectAdapterWithEndpoints(const ::std::string&, const ::std::string&) = 0;

    virtual ::Ice::ObjectAdapterPtr createObjectAdapterWithRouter(const ::std::string&, const ::Ice::RouterPrx&) = 0;

    virtual void addObjectFactory(const ::Ice::ObjectFactoryPtr&, const ::std::string&) = 0;

    virtual ::Ice::ObjectFactoryPtr findObjectFactory(const ::std::string&) const = 0;

    virtual ::Ice::ImplicitContextPtr getImplicitContext() const = 0;

    virtual ::Ice::PropertiesPtr getProperties() const = 0;

    virtual ::Ice::LoggerPtr getLogger() const = 0;

    virtual ::Ice::Instrumentation::CommunicatorObserverPtr getObserver() const = 0;

    virtual ::Ice::RouterPrx getDefaultRouter() const = 0;

    virtual void setDefaultRouter(const ::Ice::RouterPrx&) = 0;

    virtual ::Ice::LocatorPrx getDefaultLocator() const = 0;

    virtual void setDefaultLocator(const ::Ice::LocatorPrx&) = 0;

    virtual ::Ice::PluginManagerPtr getPluginManager() const = 0;

    virtual void flushBatchRequests() = 0;
    // Only supported with C++ 11 support enabled
    virtual ::Ice::AsyncResultPtr begin_flushBatchRequests(const ::IceInternal::Function<void (const ::Ice::Exception&)>& exception, const ::IceInternal::Function<void (bool)>& sent = ::IceInternal::Function<void (bool)>()) = 0;

    virtual ::Ice::AsyncResultPtr begin_flushBatchRequests() = 0;

    virtual ::Ice::AsyncResultPtr begin_flushBatchRequests(const ::Ice::CallbackPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0) = 0;

    virtual ::Ice::AsyncResultPtr begin_flushBatchRequests(const ::Ice::Callback_Communicator_flushBatchRequestsPtr& __del, const ::Ice::LocalObjectPtr& __cookie = 0) = 0;

    virtual void end_flushBatchRequests(const ::Ice::AsyncResultPtr&) = 0;

    virtual ::Ice::ObjectPrx createAdmin(const ::Ice::ObjectAdapterPtr&, const ::Ice::Identity&) = 0;

    virtual ::Ice::ObjectPrx getAdmin() const = 0;

    virtual void addAdminFacet(const ::Ice::ObjectPtr&, const ::std::string&) = 0;

    virtual ::Ice::ObjectPtr removeAdminFacet(const ::std::string&) = 0;

    virtual ::Ice::ObjectPtr findAdminFacet(const ::std::string&) = 0;

    virtual ::Ice::FacetMap findAllAdminFacets() = 0;
};

inline bool operator==(const Communicator& l, const Communicator& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) == static_cast<const ::Ice::LocalObject&>(r);
}

inline bool operator<(const Communicator& l, const Communicator& r)
{
    return static_cast<const ::Ice::LocalObject&>(l) < static_cast<const ::Ice::LocalObject&>(r);
}

}

#include <IceUtil/PopDisableWarnings.h>
#endif
