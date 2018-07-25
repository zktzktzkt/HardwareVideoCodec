/*
 * Copyright (c) 2018-present, lmyooyo@gmail.com.
 *
 * This source code is licensed under the GPL license found in the
 * LICENSE file in the root directory of this source tree.
 */
#include "Java_com_lmy_rtmp_RtmpClient.h"
#include "RtmpClient.h"

static RtmpClient *client = NULL;
#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_lmy_rtmp_RtmpClient_init
        (JNIEnv *env, jobject thiz) {
    if (NULL == client) {
        client = new RtmpClient();
    }
}

JNIEXPORT void JNICALL Java_com_lmy_rtmp_RtmpClient_connect
        (JNIEnv *env, jobject thiz, jstring url, jint width, jint height, jint timeOut) {
    char *urlTmp = (char *) env->GetStringUTFChars(url, NULL);
    client->connect(urlTmp, width, height, timeOut);
    env->ReleaseStringUTFChars(url, urlTmp);
}

JNIEXPORT jint JNICALL
Java_com_lmy_rtmp_RtmpClient_sendSpsAndPps(JNIEnv *env, jobject thiz, jbyteArray sps, jint spsLen,
                                           jbyteArray pps, jint ppsLen, jlong timestamp) {
    jbyte *spsBuffer = env->GetByteArrayElements(sps, JNI_FALSE);
    jbyte *ppsBuffer = env->GetByteArrayElements(pps, JNI_FALSE);
    int ret = client->sendSpsAndPps((char *) spsBuffer, spsLen, (char *) ppsBuffer, ppsLen,
                                    timestamp);
    env->ReleaseByteArrayElements(sps, spsBuffer, JNI_FALSE);
    env->ReleaseByteArrayElements(pps, ppsBuffer, JNI_FALSE);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_lmy_rtmp_RtmpClient_sendVideoData(JNIEnv *env, jobject thiz, jbyteArray data, jint len, jlong timestamp) {
    jbyte *buffer = env->GetByteArrayElements(data, JNI_FALSE);
    int ret = client->sendVideoData((char *) buffer, len, timestamp);
    env->ReleaseByteArrayElements(data, buffer, JNI_FALSE);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_lmy_rtmp_RtmpClient_sendAacSpec(JNIEnv *env, jobject thiz, jbyteArray data, jint len) {
    jbyte *buffer = env->GetByteArrayElements(data, JNI_FALSE);
    int ret = client->sendAacSpec((char *) buffer, len);
    env->ReleaseByteArrayElements(data, buffer, JNI_FALSE);
    return ret;
}

JNIEXPORT jint JNICALL
Java_com_lmy_rtmp_RtmpClient_sendAacData(JNIEnv *env, jobject thiz, jbyteArray data, jint len, jlong timestamp) {
    jbyte *buffer = env->GetByteArrayElements(data, JNI_FALSE);
    int ret = client->sendAacData((char *) buffer, len, timestamp);
    env->ReleaseByteArrayElements(data, buffer, JNI_FALSE);
    return ret;
}

JNIEXPORT void JNICALL
Java_com_lmy_rtmp_RtmpClient_stop(JNIEnv *env, jobject thiz) {
    client->stop();
}

#ifdef __cplusplus
}
#endif