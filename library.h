#ifndef CTSA_LIBRARY_H
#define CTSA_LIBRARY_H

#include <jni.h>

JNIEXPORT void JNICALL
Java_at_rafat_ctsa_CTSA_init(JNIEnv *env, jclass clazz);

JNIEXPORT jobject JNICALL
Java_at_rafat_ctsa_CTSA_exec(JNIEnv *env, jclass clazz, jdoubleArray ts, jint p, jint d, jint q, jint P, jint D, jint Q, jint s, jint approximation, jint stepwise, jint method, jint opt, jint L);

JNIEXPORT void JNICALL
Java_at_rafat_ctsa_CTSA_destroy(JNIEnv *env, jclass clazz);

#endif

