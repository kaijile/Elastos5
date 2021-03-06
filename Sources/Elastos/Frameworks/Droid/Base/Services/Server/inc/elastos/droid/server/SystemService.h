//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#ifndef __ELASTOS_DROID_SERVER_SYSTEM_SERVICE_H__
#define __ELASTOS_DROID_SERVER_SYSTEM_SERVICE_H__

#include "_Elastos.Droid.Server.h"
#include <elastos/core/Object.h>
#include <elastos/droid/ext/frameworkext.h>

using Elastos::Droid::Os::IBinder;
using Elastos::Droid::Content::IContext;

namespace Elastos {
namespace Droid {
namespace Server {

/**
 * The base class for services running in the system process. Override and implement
 * the lifecycle event callback methods as needed.
 * <p>
 * The lifecycle of a SystemService:
 * </p><ul>
 * <li>The constructor is called and provided with the system {@link Context}
 * to initialize the system service.
 * <li>{@link #onStart()} is called to get the service running.  The service should
 * publish its binder interface at this point using
 * {@link #PublishBinderService(String, IBinder)}.  It may also publish additional
 * local interfaces that other services within the system server may use to access
 * privileged internal functions.
 * <li>Then {@link #onBootPhase(int)} is called as many times as there are boot phases
 * until {@link #PHASE_BOOT_COMPLETE} is sent, which is the last boot phase. Each phase
 * is an opportunity to do special work, like acquiring optional service dependencies,
 * waiting to see if SafeMode is enabled, or registering with a service that gets
 * started after this one.
 * </ul><p>
 * NOTE: All lifecycle methods are called from the system server's main looper thread.
 * </p>
 *
 * {@hide}
 */
class SystemService
    : public Object
    , public ISystemService
{
public:
    CAR_INTERFACE_DECL()

    SystemService();

    virtual ~SystemService();

    /**
     * Initializes the system service.
     * <p>
     * Subclasses must define a single argument constructor that accepts the context
     * and passes it to super.
     * </p>
     *
     * @param context The system server context.
     */
    CARAPI constructor(
        /* [in] */ IContext* context);

    /**
     * Gets the system context.
     */
    CARAPI GetContext(
        /* [out] */ IContext** ctx);

    /**
     * Returns true if the system is running in safe mode.
     * TODO: we should define in which phase this becomes valid
     */
    CARAPI IsSafeMode(
        /* [out] */  Boolean* safeMode);

    /**
     * Called when the dependencies listed in the @Service class-annotation are available
     * and after the chosen start phase.
     * When this method returns, the service should be published.
     */
    virtual CARAPI OnStart() = 0;

    /**
     * Called on each phase of the boot process. Phases before the service's start phase
     * (as defined in the @Service annotation) are never received.
     *
     * @param phase The current boot phase.
     */
    CARAPI OnBootPhase(
        /* [in] */ Int32 phase);

    /**
     * Called when a new user is starting, for system services to initialize any per-user
     * state they maintain for running users.
     * @param userHandle The identifier of the user.
     */
    CARAPI OnStartUser(
        /* [in] */ Int32 userHandle);

    /**
     * Called when switching to a different foreground user, for system services that have
     * special behavior for whichever user is currently in the foreground.  This is called
     * before any application processes are aware of the new user.
     * @param userHandle The identifier of the user.
     */
    CARAPI OnSwitchUser(
        /* [in] */ Int32 userHandle);

    /**
     * Called when an existing user is stopping, for system services to finalize any per-user
     * state they maintain for running users.  This is called prior to sending the SHUTDOWN
     * broadcast to the user; it is a good place to stop making use of any resources of that
     * user (such as binding to a service running in the user).
     * @param userHandle The identifier of the user.
     */
    CARAPI OnStopUser(
        /* [in] */ Int32 userHandle);

    /**
     * Called when an existing user is stopping, for system services to finalize any per-user
     * state they maintain for running users.  This is called after all application process
     * teardown of the user is complete.
     * @param userHandle The identifier of the user.
     */
    CARAPI OnCleanupUser(
        /* [in] */ Int32 userHandle);

protected:
    /**
     * Publish the service so it is accessible to other services and apps.
     */
    CARAPI_(void) PublishBinderService(
        /* [in] */ const String& name,
        /* [in] */ IBinder* service);

    /**
     * Publish the service so it is accessible to other services and apps.
     */
    CARAPI_(void) PublishBinderService(
        /* [in] */ const String& name,
        /* [in] */ IBinder* service,
        /* [in] */ Boolean allowIsolated);

    /**
     * Get a binder service by its name.
     */
    CARAPI_(AutoPtr<IBinder>) GetBinderService(
        /* [in] */ const String& name);

    /**
     * Publish the service so it is only accessible to the system process.
     */
    CARAPI_(void) PublishLocalService(
        /* [in] */ const InterfaceID& type,
        /* [in] */ IInterface* service);

    /**
     * Get a local service by interface.
     */
    CARAPI_(AutoPtr<IInterface>) GetLocalService(
        /* [in] */const InterfaceID& type);

private:
    CARAPI_(AutoPtr<ISystemServiceManager>) GetManager();

protected:
    AutoPtr<IContext> mContext;
};

} // namespace Server
} // namepsace Droid
} // namespace Elastos

#endif //__ELASTOS_DROID_SERVER_SYSTEM_SERVICE_H__
