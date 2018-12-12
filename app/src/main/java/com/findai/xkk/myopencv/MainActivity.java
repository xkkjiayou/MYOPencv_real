package com.findai.xkk.myopencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import org.opencv.android.OpenCVLoader;
import org.opencv.android.Utils;
import org.opencv.core.Mat;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //非常重要，启动opencv，必须写在最前面
        OpenCVLoader.initDebug();
        setContentView(R.layout.activity_main);
        Bitmap bmp = BitmapFactory.decodeResource(getResources(),R.mipmap.eye);
        ImageView imageView = findViewById(R.id.iv_pro_img);

        int w = bmp.getWidth();
        int h = bmp.getHeight();
//        System.out.println(w);
//        System.out.println(h);
        int[] pixels = new int[w*h];
        bmp.getPixels(pixels, 0, w, 0, 0, w, h);

        long startTime = System.currentTimeMillis();
        int[] resultInt = stringFromJNI(pixels, w, h);
        long endTime = System.currentTimeMillis();

        Log.e("JNITime",""+(endTime-startTime));
        Bitmap resultImg = Bitmap.createBitmap(w/2,h/2, Bitmap.Config.ARGB_8888);

        //(@ColorInt int[] pixels, int offset, int stride,int x, int y, int width, int height)
//        System.out.println(w/2);
//        System.out.println(h/2);
        resultImg.setPixels(resultInt, 0, w/2, 0, 0, w/2,h/2);
        imageView.setImageBitmap(resultImg);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native int[] stringFromJNI(int[] pixels, int w, int h);
}
