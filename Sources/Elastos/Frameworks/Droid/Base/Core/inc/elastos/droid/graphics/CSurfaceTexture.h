
#ifndef __ELASTOS_DROID_GRAPHICS_CSURFACETEXTURE_H__
#define __ELASTOS_DROID_GRAPHICS_CSURFACETEXTURE_H__

#include "_Elastos_Droid_Graphics_CSurfaceTexture.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/os/Handler.h"

using Elastos::Droid::Os::Handler;
using Elastos::Droid::Os::IHandler;
using Elastos::Droid::Os::ILooper;

namespace Elastos {
namespace Droid {
namespace Graphics {

/**
 * Captures frames from an image stream as an OpenGL ES texture.
 *
 * <p>The image stream may come from either camera preview or video decode.  A SurfaceTexture
 * may be used in place of a SurfaceHolder when specifying the output destination of a
 * {@link android.hardware.Camera} or {@link android.media.MediaPlayer}
 * object.  Doing so will cause all the frames from the image stream to be sent to the
 * SurfaceTexture object rather than to the device's display.  When {@link #updateTexImage} is
 * called, the contents of the texture object specified when the SurfaceTexture was created are
 * updated to contain the most recent image from the image stream.  This may cause some frames of
 * the stream to be skipped.
 *
 * <p>When sampling from the texture one should first transform the texture coordinates using the
 * matrix queried via {@link #getTransformMatrix(float[])}.  The transform matrix may change each
 * time {@link #updateTexImage} is called, so it should be re-queried each time the texture image
 * is updated.
 * This matrix transforms traditional 2D OpenGL ES texture coordinate column vectors of the form (s,
 * t, 0, 1) where s and t are on the inclusive interval [0, 1] to the proper sampling location in
 * the streamed texture.  This transform compensates for any properties of the image stream source
 * that cause it to appear different from a traditional OpenGL ES texture.  For example, sampling
 * from the bottom left corner of the image can be accomplished by transforming the column vector
 * (0, 0, 0, 1) using the queried matrix, while sampling from the top right corner of the image can
 * be done by transforming (1, 1, 0, 1).
 *
 * <p>The texture object uses the GL_TEXTURE_EXTERNAL_OES texture target, which is defined by the
 * <a href="http://www.khronos.org/registry/gles/extensions/OES/OES_EGL_image_external.txt">
 * GL_OES_EGL_image_external</a> OpenGL ES extension.  This limits how the texture may be used.
 * Each time the texture is bound it must be bound to the GL_TEXTURE_EXTERNAL_OES target rather than
 * the GL_TEXTURE_2D target.  Additionally, any OpenGL ES 2.0 shader that samples from the texture
 * must declare its use of this extension using, for example, an "#extension
 * GL_OES_EGL_image_external : require" directive.  Such shaders must also access the texture using
 * the samplerExternalOES GLSL sampler type.
 *
 * <p>SurfaceTexture objects may be created on any thread.  {@link #updateTexImage} may only be
 * called on the thread with the OpenGL ES context that contains the texture object.  The
 * frame-available callback is called on an arbitrary thread, so unless special care is taken {@link
 * #updateTexImage} should not be called directly from the callback.
 */
CarClass(CSurfaceTexture)
    , public Object
    , public ISurfaceTexture
{
private:
    class AvailableHandler: public Handler
    {
    public:
        TO_STRING_IMPL("CSurfaceTexture::AvailableHandler")

        AvailableHandler(
            /* [in] */ IOnFrameAvailableListener* listener,
            /* [in] */ CSurfaceTexture* host);

        CARAPI HandleMessage(
            /* [in] */ IMessage* msg);

    private:
        CSurfaceTexture* mHost;
        AutoPtr<IOnFrameAvailableListener> mListener;
    };

public:
    CAR_INTERFACE_DECL();

    CAR_OBJECT_DECL();

    CSurfaceTexture();

    ~CSurfaceTexture();

    /**
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     * @param texName the OpenGL texture object name (e.g. generated via glGenTextures)
     */
    CARAPI constructor(
        /* [in] */ Int32 texName);

    /**
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     * In single buffered mode the application is responsible for serializing access to the image
     * content buffer. Each time the image content is to be updated, the
     * {@link #releaseTexImage()} method must be called before the image content producer takes
     * ownership of the buffer. For example, when producing image content with the NDK
     * ANativeWindow_lock and ANativeWindow_unlockAndPost functions, {@link #releaseTexImage()}
     * must be called before each ANativeWindow_lock, or that call will fail. When producing
     * image content with OpenGL ES, {@link #releaseTexImage()} must be called before the first
     * OpenGL ES function call each frame.
     *
     * @param texName the OpenGL texture object name (e.g. generated via glGenTextures)
     * @param singleBufferMode whether the SurfaceTexture will be in single buffered mode.
     *
     * @throws Surface.OutOfResourcesException If the SurfaceTexture cannot be created.
     */
    CARAPI constructor(
        /* [in] */ Int32 texName,
        /* [in] */ Boolean singleBufferMode);

    /**
     * Construct a new SurfaceTexture to stream images to a given OpenGL texture.
     *
     * In single buffered mode the application is responsible for serializing access to the image
     * content buffer. Each time the image content is to be updated, the
     * {@link #releaseTexImage()} method must be called before the image content producer takes
     * ownership of the buffer. For example, when producing image content with the NDK
     * ANativeWindow_lock and ANativeWindow_unlockAndPost functions, {@link #releaseTexImage()}
     * must be called before each ANativeWindow_lock, or that call will fail. When producing
     * image content with OpenGL ES, {@link #releaseTexImage()} must be called before the first
     * OpenGL ES function call each frame.
     *
     * Unlike {@link #SurfaceTexture(int, boolean)}, which takes an OpenGL texture object name,
     * this constructor creates the SurfaceTexture in detached mode. A texture name must be passed
     * in using {@link #attachToGLContext} before calling {@link #releaseTexImage()} and producing
     * image content using OpenGL ES.
     *
     * @param singleBufferMode whether the SurfaceTexture will be in single buffered mode.
     *
     * @throws Surface.OutOfResourcesException If the SurfaceTexture cannot be created.
     * @hide
     */
    CARAPI constructor(
        /* [in] */ Boolean singleBufferMode);

    /**
     * Register a callback to be invoked when a new image frame becomes available to the
     * SurfaceTexture.  Note that this callback may be called on an arbitrary thread, so it is not
     * safe to call {@link #updateTexImage} without first binding the OpenGL ES context to the
     * thread invoking the callback.
     */
    CARAPI SetOnFrameAvailableListener(
        /* [in] */ IOnFrameAvailableListener* listener);

    /**
     * Register a callback to be invoked when a new image frame becomes available to the
     * SurfaceTexture.
     * <p>
     * If a handler is specified, the callback will be invoked on that handler's thread.
     * If no handler is specified, then the callback may be called on an arbitrary thread,
     * so it is not safe to call {@link #updateTexImage} without first binding the OpenGL ES
     * context to the thread invoking the callback.
     * </p>
     *
     * @param listener The listener to use, or null to remove the listener.
     * @param handler The handler on which the listener should be invoked, or null
     * to use an arbitrary thread.
     */
    CARAPI SetOnFrameAvailableListener(
        /* [in] */ /*@Nullable*/ IOnFrameAvailableListener* listener,
        /* [in] */ /*@Nullable*/ IHandler* handler);

    /**
     * Set the default size of the image buffers.  The image producer may override the buffer size,
     * in which case the producer-set buffer size will be used, not the default size set by this
     * method.  Both video and camera based image producers do override the size.  This method may
     * be used to set the image size when producing images with {@link android.graphics.Canvas} (via
     * {@link android.view.Surface#lockCanvas}), or OpenGL ES (via an EGLSurface).
     *
     * The new default buffer size will take effect the next time the image producer requests a
     * buffer to fill.  For {@link android.graphics.Canvas} this will be the next time {@link
     * android.view.Surface#lockCanvas} is called.  For OpenGL ES, the EGLSurface should be
     * destroyed (via eglDestroySurface), made not-current (via eglMakeCurrent), and then recreated
     * (via eglCreateWindowSurface) to ensure that the new default size has taken effect.
     *
     * The width and height parameters must be no greater than the minimum of
     * GL_MAX_VIEWPORT_DIMS and GL_MAX_TEXTURE_SIZE (see
     * {@link javax.microedition.khronos.opengles.GL10#glGetIntegerv glGetIntegerv}).
     * An error due to invalid dimensions might not be reported until
     * updateTexImage() is called.
     */
    CARAPI SetDefaultBufferSize(
        /* [in] */ Int32 width,
        /* [in] */ Int32 height);

    /**
     * Update the texture image to the most recent frame from the image stream.  This may only be
     * called while the OpenGL ES context that owns the texture is current on the calling thread.
     * It will implicitly bind its texture to the GL_TEXTURE_EXTERNAL_OES texture target.
     */
    CARAPI UpdateTexImage();

    /**
     * Releases the the texture content. This is needed in single buffered mode to allow the image
     * content producer to take ownership of the image buffer.
     * For more information see {@link #SurfaceTexture(int, boolean)}.
     */
    CARAPI ReleaseTexImage();

    /**
     * Detach the SurfaceTexture from the OpenGL ES context that owns the OpenGL ES texture object.
     * This call must be made with the OpenGL ES context current on the calling thread.  The OpenGL
     * ES texture object will be deleted as a result of this call.  After calling this method all
     * calls to {@link #updateTexImage} will throw an {@link java.lang.IllegalStateException} until
     * a successful call to {@link #attachToGLContext} is made.
     *
     * This can be used to access the SurfaceTexture image contents from multiple OpenGL ES
     * contexts.  Note, however, that the image contents are only accessible from one OpenGL ES
     * context at a time.
     */
    CARAPI DetachFromGLContext();

    /**
     * Attach the SurfaceTexture to the OpenGL ES context that is current on the calling thread.  A
     * new OpenGL ES texture object is created and populated with the SurfaceTexture image frame
     * that was current at the time of the last call to {@link #detachFromGLContext}.  This new
     * texture is bound to the GL_TEXTURE_EXTERNAL_OES texture target.
     *
     * This can be used to access the SurfaceTexture image contents from multiple OpenGL ES
     * contexts.  Note, however, that the image contents are only accessible from one OpenGL ES
     * context at a time.
     *
     * @param texName The name of the OpenGL ES texture that will be created.  This texture name
     * must be unusued in the OpenGL ES context that is current on the calling thread.
     */
    CARAPI AttachToGLContext(
        /* [in] */ Int32 texName);

    /**
     * Retrieve the 4x4 texture coordinate transform matrix associated with the texture image set by
     * the most recent call to updateTexImage.
     *
     * This transform matrix maps 2D homogeneous texture coordinates of the form (s, t, 0, 1) with s
     * and t in the inclusive range [0, 1] to the texture coordinate that should be used to sample
     * that location from the texture.  Sampling the texture outside of the range of this transform
     * is undefined.
     *
     * The matrix is stored in column-major order so that it may be passed directly to OpenGL ES via
     * the glLoadMatrixf or glUniformMatrix4fv functions.
     *
     * @param mtx the array into which the 4x4 matrix will be stored.  The array must have exactly
     *     16 elements.
     */
    CARAPI GetTransformMatrix(
        /* [in] */ ArrayOf<Float>* mtx);

    /**
     * Retrieve the timestamp associated with the texture image set by the most recent call to
     * updateTexImage.
     *
     * This timestamp is in nanoseconds, and is normally monotonically increasing. The timestamp
     * should be unaffected by time-of-day adjustments, and for a camera should be strictly
     * monotonic but for a MediaPlayer may be reset when the position is set.  The
     * specific meaning and zero point of the timestamp depends on the source providing images to
     * the SurfaceTexture. Unless otherwise specified by the image source, timestamps cannot
     * generally be compared across SurfaceTexture instances, or across multiple program
     * invocations. It is mostly useful for determining time offsets between subsequent frames.
     */
    CARAPI GetTimestamp(
        /* [out] */ Int64* timestamp);

    /**
     * release() frees all the buffers and puts the SurfaceTexture into the
     * 'abandoned' state. Once put in this state the SurfaceTexture can never
     * leave it. When in the 'abandoned' state, all methods of the
     * ISurfaceTexture interface will fail with the NO_INIT error.
     *
     * Note that while calling this method causes all the buffers to be freed
     * from the perspective of the the SurfaceTexture, if there are additional
     * references on the buffers (e.g. if a buffer is referenced by a client or
     * by OpenGL ES as a texture) then those buffer will remain allocated.
     *
     * Always call this method when you are done with SurfaceTexture. Failing
     * to do so may delay resource deallocation for a significant amount of
     * time.
     */
    CARAPI ReleaseBuffers();

    static CARAPI_(void) PostEventFromNative(
            /* [in] */ IWeakReference/*<SurfaceTexture>*/* weakSelf);

    CARAPI GetSurfaceTexture(
        /* [out] */ Int32* texture);

private:
    CARAPI NativeInit(
        /* [in] */ Boolean isDetached,
        /* [in] */ Int32 texName,
        /* [in] */ Boolean singleBufferMode,
        /* [in] */ IWeakReference/*<SurfaceTexture>*/* weakSelf) /*throws Surface.OutOfResourcesException*/;

    CARAPI NativeReleaseTexImage();

    CARAPI_(void) NativeFinalize();

    CARAPI_(void) NativeGetTransformMatrix(
        /* [in] */ ArrayOf<Float>* mtx);

    CARAPI_(Int64) NativeGetTimestamp();

    CARAPI_(void) NativeSetDefaultBufferSize(
        /* [in] */ Int32 width,
        /* [in] */ Int32 height);

    CARAPI NativeUpdateTexImage();

    CARAPI_(Int32) NativeDetachFromGLContext();

    CARAPI_(Int32) NativeAttachToGLContext(
        /* [in] */ Int32 texName);

    CARAPI_(Int32) NativeGetQueuedCount();

    CARAPI_(void) NativeRelease();

public:
    /**
     * This field is used by native code, do not access or modify.
     */
    Int64 mSurfaceTexture;
    Int64  mProducer;
    Int64  mFrameAvailableListener;

private:
    AutoPtr<ILooper> mCreatorLooper;
    AutoPtr<AvailableHandler> mOnFrameAvailableHandler;
};

} // namespace Graphics
} // namepsace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_GRAPHICS_CSURFACETEXTURE_H__
