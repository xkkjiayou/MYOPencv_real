#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>

extern "C"{
    using namespace cv;
    JNIEXPORT jstring JNICALL
Java_com_findai_xkk_myopencv_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from ssssssssC++";
    Mat mat = Mat::zeros(100,100,CV_8UC1);
    return env->NewStringUTF(hello.c_str());
}
}
