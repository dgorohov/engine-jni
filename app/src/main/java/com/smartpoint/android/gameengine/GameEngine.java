package com.smartpoint.android.gameengine;

import android.content.res.AssetManager;
import android.content.res.Resources;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by <a href="mailto:Dmitry.Gorohov@ebuilder.com">Dmitry Gorohov</a>
 */
final class GameEngine implements GLSurfaceView.Renderer {

    static {
        System.loadLibrary("game-engine");
    }

    GameEngine(final Resources resources) {
        nativeOnStart();
        final AssetManager assetManager = resources.getAssets();
        nativeOnAssetManagerReady(assetManager);
    }

    void onDestroy() {
        nativeOnDestroy();
    }

    static native void nativeOnStart();

    static native void nativeOnRender();

    static native void nativeOnDestroy();

    static native void nativeOnSurfaceCreated(final int width, final int height);

    static native void nativeOnAssetManagerReady(final AssetManager assetManager);

    @Override
    public void onSurfaceCreated(final GL10 gl, final EGLConfig config) {}

    @Override
    public void onSurfaceChanged(final GL10 gl, final int width, final int height) {
        nativeOnSurfaceCreated(width, height);
    }

    @Override
    public void onDrawFrame(final GL10 gl) {
        nativeOnRender();
    }
}
