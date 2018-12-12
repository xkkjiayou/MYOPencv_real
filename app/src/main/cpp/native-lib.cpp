#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <android/log.h>
#include <iostream>
#include <stdio.h>

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "keymatch", __VA_ARGS__)
extern "C"{
    using namespace cv;
    using namespace std;

void printMAtMessage(Mat &mat);
    JNIEXPORT jintArray  JNICALL
Java_com_findai_xkk_myopencv_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */,jintArray pixels_
        , jint w
        , jint h) {
        jint* pixels = env->GetIntArrayElements(pixels_, NULL);
        if (pixels==NULL){
            return 0;
        }

//图片一进来时是ARGB  通过mat转换BGRA
        Mat img(h,w,CV_8UC4,(uchar *)pixels);  //pixels 操作的是同一份数据
        h = h/2,w = w/2;
        resize(img,img,Size(w,h));
        printMAtMessage(img);
        Mat temp;
//转化为单通道灰度图，并打印信息
        cvtColor(img,temp,COLOR_RGBA2GRAY);
//        printMAtMessage(temp);

        int summat[h][w] ;

//        Mat cal_mat = temp.clone();
        int max_cha = 0;
//        LOGD("rows: %d",temp.rows);
//        LOGD("cols: %d",temp.cols);
//        LOGD("w: %d",w);
//        LOGD("h: %d",h);
//        int kk=0;
        for(int i =6 ;i<h-6;i++){
//            int sum_d = 0;
            for(int j =6;j<w-6;j++){
//                LOGD("DDD %d",temp.at<uchar >(i,j));
                int sum_s = temp.at<uchar >(i-1,j)+temp.at<uchar >(i-2,j)+temp.at<uchar >(i-3,j)+temp.at<uchar >(i-4,j)+temp.at<uchar >(i-5,j);
//                LOGD("------================211111111111111111111111111===------------ %d %s",i,j);
                int sum_x = temp.at<uchar >(i+1,j)+temp.at<uchar >(i+2,j)+temp.at<uchar >(i+3,j)+temp.at<uchar >(i+4,j)+temp.at<uchar >(i+5,j);
//                LOGD("------==============22222222222222222222=====------------");
                int cha = sum_s - sum_x;
//                LOGD("------===============3333333333333333333333333====------------");
                summat[i][j] = abs(cha);
//                LOGD("------===============33333333333 %d 33333333333333====------------",summat[i][j]);
//                temp.at<uchar >(i,j)=255;
//                kk++;
//                LOGD("i: %d",i);
//                LOGD("j: %d",j);
//                LOGD("------==============444444444444444444444444=====------------");
                if(max_cha<cha){
                    max_cha = cha;
//                    LOGD("max %d",max_cha);
//                    LOGD("------============44666666666666666666666666666666666=======------------");
                }
//                sum_d = sum_d + ;

            }
        }

        int std_max = max_cha*0.4;
//        LOGD("------=========== %d ========------------",max_cha);
        for(int i =6 ;i<h-6;i++){
//            int max_col = 0;
//            int max_i = 0;
//            int max_j = 0;
            for(int j =6;j<w-6;j++){
//                LOGD("DDD %d",temp.at<uchar >(i,j));
//                int sum_s = temp.at<uchar >(i-1,j)+temp.at<uchar >(i-2,j)+temp.at<uchar >(i-3,j)+temp.at<uchar >(i-4,j)+temp.at<uchar >(i-5,j);
//                int sum_x = temp.at<uchar >(i+1,j)+temp.at<uchar >(i+2,j)+temp.at<uchar >(i+3,j)+temp.at<uchar >(i+4,j)+temp.at<uchar >(i+5,j);
//                int cha = sum_s - sum_x;
//                int cur_gray  = summat[i][j];
//                    LOGD("------=======cur_gray==== %d ========------------",cur_gray);
                if(summat[i][j] > std_max){

//                    LOGD("------=======cur_gray==== %d ========------------",cal_mat.at<int>(i,j));
                    temp.at<uchar>(i,j)=255;
                }
//                if(max_cha<cha){
//                    max_cha = cha;
//                }
//                sum_d = sum_d + ;

            }



        }


//转化为四通道。特别注意：在调用ov图像处理函数时，一定要好好考虑一下图片的位数和通道.否则可能出现各种问题.
        cvtColor(temp,temp,COLOR_GRAY2BGRA);
//        printMAtMessage(temp);

        uchar* tempData = temp.data;

//对应数据指针
        int size = w*h;
        jintArray result = env->NewIntArray(size);
//env->SetIntArrayRegion(result,0,size,pixels);
        env->SetIntArrayRegion(result, 0, size, (const jint *) tempData);

        env->ReleaseIntArrayElements(pixels_, pixels, 0);

        return result;
}
void printMAtMessage(Mat &mat) {
    LOGD("***************************Mat信息开始************************");
    LOGD("mat.rows %d",mat.rows);
    LOGD("mat.cols %d",mat.cols);
    LOGD("mat.total %d",mat.total());
    LOGD("mat.channels %d",mat.channels());
    LOGD("mat.depth %d",mat.depth());
    LOGD("mat.type %d",mat.type());
    LOGD("mat.flags %d",mat.flags);
    LOGD("mat.elemSize %d",mat.elemSize());
    LOGD("mat.elemSize1 %d",mat.elemSize1());
    LOGD("***************************Mat信息结束************************");
}

}
