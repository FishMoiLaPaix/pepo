package com.google.cardboard;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.os.Bundle;
import android.view.ScaleGestureDetector;
import android.view.TextureView;
import android.view.View;
import android.view.WindowManager;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.io.IOException;

public class StereoCameraActivity extends AppCompatActivity implements TextureView.SurfaceTextureListener {
    private static final int CAMERA_PERMISSION_REQUEST = 100;
    private Camera camera;
    private TextureView leftTextureView;
    private TextureView rightTextureView;
    private ScaleGestureDetector scaleGestureDetector;
    private float zoomLevel = 1.0f;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_stereo_camera);

        leftTextureView = findViewById(R.id.left_texture_view);
        rightTextureView = findViewById(R.id.right_texture_view);
        leftTextureView.setSurfaceTextureListener(this);
        rightTextureView.setSurfaceTextureListener(this);

        scaleGestureDetector = new ScaleGestureDetector(this, new ScaleListener());

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, CAMERA_PERMISSION_REQUEST);
        } else {
            openCamera();
        }

        // Empêcher l'écran de s'éteindre
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode == CAMERA_PERMISSION_REQUEST) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                openCamera();
            } else {
                Toast.makeText(this, "Permission caméra refusée", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void openCamera() {
        try {
            camera = Camera.open();
            Camera.Parameters params = camera.getParameters();
            if (params.isZoomSupported()) {
                params.setZoom((int) zoomLevel);
            }
            camera.setParameters(params);

            SurfaceTexture leftSurface = leftTextureView.getSurfaceTexture();
            SurfaceTexture rightSurface = rightTextureView.getSurfaceTexture();

            if (leftSurface != null) {
                camera.setPreviewTexture(leftSurface);
            }
            if (rightSurface != null) {
                camera.setPreviewTexture(rightSurface);
            }

            camera.startPreview();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        openCamera();
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {}

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        if (camera != null) {
            camera.stopPreview();
            camera.release();
            camera = null;
        }
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {}

    @Override
    public boolean onTouchEvent(android.view.MotionEvent event) {
        scaleGestureDetector.onTouchEvent(event);
        return true;
    }

    private class ScaleListener extends ScaleGestureDetector.SimpleOnScaleGestureListener {
        @Override
        public boolean onScale(ScaleGestureDetector detector) {
            if (camera != null) {
                Camera.Parameters params = camera.getParameters();
                if (params.isZoomSupported()) {
                    zoomLevel += detector.getScaleFactor() - 1;
                    zoomLevel = Math.max(0, Math.min(zoomLevel, params.getMaxZoom()));
                    params.setZoom((int) zoomLevel);
                    camera.setParameters(params);
                }
            }
            return true;
        }
    }
}
