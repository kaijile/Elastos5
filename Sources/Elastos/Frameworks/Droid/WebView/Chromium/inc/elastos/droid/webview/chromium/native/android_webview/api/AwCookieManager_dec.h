//This file is autogenerated for
//    AwCookieManager.java
//put this file at the end of the include list
//so the type definition used in this file will be found
#ifndef ELASTOS_AWCOOKIEMANAGER_CALLBACK_DEC_HH
#define ELASTOS_AWCOOKIEMANAGER_CALLBACK_DEC_HH


#ifdef __cplusplus
extern "C"
{
#endif
    extern void Elastos_AwCookieManager_nativeSetShouldAcceptCookies(IInterface* caller,Boolean accept);
    extern Boolean Elastos_AwCookieManager_nativeGetShouldAcceptCookies(IInterface* caller);
    extern void Elastos_AwCookieManager_nativeSetCookie(IInterface* caller,const String& url,const String& value,IInterface* callback);
    extern void Elastos_AwCookieManager_nativeSetCookieSync(IInterface* caller,const String& url,const String& value);
    extern String Elastos_AwCookieManager_nativeGetCookie(IInterface* caller,const String& url);
    extern void Elastos_AwCookieManager_nativeRemoveSessionCookies(IInterface* caller,IInterface* callback);
    extern void Elastos_AwCookieManager_nativeRemoveSessionCookiesSync(IInterface* caller);
    extern void Elastos_AwCookieManager_nativeRemoveAllCookies(IInterface* caller,IInterface* callback);
    extern void Elastos_AwCookieManager_nativeRemoveAllCookiesSync(IInterface* caller);
    extern void Elastos_AwCookieManager_nativeRemoveExpiredCookies(IInterface* caller);
    extern void Elastos_AwCookieManager_nativeFlushCookieStore(IInterface* caller);
    extern Boolean Elastos_AwCookieManager_nativeHasCookies(IInterface* caller);
    extern Boolean Elastos_AwCookieManager_nativeAllowFileSchemeCookies(IInterface* caller);
    extern void Elastos_AwCookieManager_nativeSetAcceptFileSchemeCookies(IInterface* caller,Boolean accept);
    extern void Elastos_AwCookieManager_InitCallback(Handle32 cb);
#ifdef __cplusplus
}
#endif


namespace Elastos {
namespace Droid {
namespace Webkit {
namespace Webview {
namespace Chromium {
namespace AndroidWebview {

struct ElaAwCookieManagerCallback
{
    void (*elastos_AwCookieManager_invokeBooleanCookieCallback)(IInterface* callback, Boolean result);
};

void* AwCookieManager::ElaAwCookieManagerCallback_Init()
{
    static ElaAwCookieManagerCallback sElaAwCookieManagerCallback;

    sElaAwCookieManagerCallback.elastos_AwCookieManager_invokeBooleanCookieCallback = &AwCookieManager::InvokeBooleanCookieCallback;

    Elastos_AwCookieManager_InitCallback((Handle32)&sElaAwCookieManagerCallback);
    return &sElaAwCookieManagerCallback;
}

static void* sPElaAwCookieManagerCallback = AwCookieManager::ElaAwCookieManagerCallback_Init();

} // namespace AndroidWebview
} // namespace Chromium
} // namespace Webview
} // namespace Webkit
} // namespace Droid
} // namespace Elastos

#endif //ELASTOS_AWCOOKIEMANAGER_CALLBACK_DEC_HH