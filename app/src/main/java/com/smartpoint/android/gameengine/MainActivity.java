package com.smartpoint.android.gameengine;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {

    private GameEngine mainEngine;
    private GLSurfaceView glSurface;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(
                WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN
        );

        mainEngine = new GameEngine(getResources());
        glSurface = new GLSurfaceView(this);

        // window format
        if (getWindowManager().getDefaultDisplay().getPixelFormat() == 1) {
            glSurface.setEGLConfigChooser(8, 8, 8, 0, 24, 8);
        } else if (getWindowManager().getDefaultDisplay().getPixelFormat() == 4) {
            glSurface.setEGLConfigChooser(5, 6, 5, 0, 24, 8);
        }

        // OpenGl context version
        glSurface.setEGLContextClientVersion(2);
        // preserve egl context on pausing
        // glSurface.setPreserveEGLContextOnPause(true);
        // set renderer
        glSurface.setRenderer(mainEngine);
        // add touch listener
        // glSurface.setOnTouchListener(this);

        // add view to layout
        setContentView(glSurface);
    }

    @Override
    protected void onDestroy() {
        mainEngine.onDestroy();
        super.onDestroy();
    }
}
