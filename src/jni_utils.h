//
// Created by biquaternions on 3/12/26.
//

#ifndef CTSA_JNI_UTILS_H
#define CTSA_JNI_UTILS_H


#include <jni.h>


#ifdef __cplusplus
extern "C" {
#endif


void JNICALL
initJniUtils(JNIEnv *env);

void JNICALL
destroyJniUtils(JNIEnv *env);

void JNICALL
throwIllegalArgumentException(JNIEnv *env, const char *message);

void JNICALL
throwArimaInitializationException(JNIEnv *env, const char *message);

void JNICALL
throwArimaExecutionException(JNIEnv *env, const char *message);

void JNICALL
throwArimaPredictionException(JNIEnv *env, const char *message);


#ifdef __cplusplus
}
#endif


#endif //CTSA_JNI_UTILS_H