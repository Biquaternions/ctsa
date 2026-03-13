//
// Created by biquaternions on 3/12/26.
//

#include "jni_utils.h"

static jclass java_illegal_argument_exception_class = NULL;
static jclass arima_initialization_exception_class = NULL;
static jclass arima_execution_exception_class = NULL;
static jclass arima_prediction_exception_class = NULL;

void JNICALL
initJniUtils(JNIEnv *env) {
    const jclass local_java_illegal_argument_exception_class = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
    const jclass local_arima_initialization_exception_class = (*env)->FindClass(env, "at/rafat/ctsa/exceptions/ArimaExecutionException");
    const jclass local_arima_execution_exception_class = (*env)->FindClass(env, "at/rafat/ctsa/exceptions/ArimaExecutionException");
    const jclass local_arima_prediction_exception_class = (*env)->FindClass(env, "at/rafat/ctsa/exceptions/ArimaPredictionException");

    java_illegal_argument_exception_class = (*env)->NewGlobalRef(env, local_java_illegal_argument_exception_class);
    arima_initialization_exception_class = (*env)->NewGlobalRef(env, local_arima_initialization_exception_class);
    arima_execution_exception_class = (*env)->NewGlobalRef(env, local_arima_execution_exception_class);
    arima_prediction_exception_class = (*env)->NewGlobalRef(env, local_arima_prediction_exception_class);
}

void JNICALL
destroyJniUtils(JNIEnv *env) {
    if (java_illegal_argument_exception_class != NULL) {
        (*env)->DeleteGlobalRef(env, java_illegal_argument_exception_class);
        java_illegal_argument_exception_class = NULL;
    }

    if (arima_initialization_exception_class != NULL) {
        (*env)->DeleteGlobalRef(env, arima_initialization_exception_class);
        arima_initialization_exception_class = NULL;
    }

    if (arima_execution_exception_class != NULL) {
        (*env)->DeleteGlobalRef(env, arima_execution_exception_class);
        arima_execution_exception_class = NULL;
    }

    if (arima_prediction_exception_class != NULL) {
        (*env)->DeleteGlobalRef(env, arima_prediction_exception_class);
        arima_prediction_exception_class = NULL;
    }
}

void JNICALL
throwIllegalArgumentException(JNIEnv *env, const char *message) {
    (*env)->ThrowNew(env, java_illegal_argument_exception_class, message);
}

void JNICALL
throwArimaInitializationException(JNIEnv *env, const char *message) {
    (*env)->ThrowNew(env, arima_initialization_exception_class, message);
}

void JNICALL
throwArimaExecutionException(JNIEnv *env, const char *message) {
    (*env)->ThrowNew(env, arima_execution_exception_class, message);
}

void JNICALL
throwArimaPredictionException(JNIEnv *env, const char *message) {
    (*env)->ThrowNew(env, arima_prediction_exception_class, message);
}

