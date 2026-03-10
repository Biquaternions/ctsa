
#include "library.h"
#include "src/ctsa.h"

static jclass arima_result_class = nullptr;
static jmethodID arima_result_class_constructor = nullptr;

JNIEXPORT void JNICALL
Java_at_rafat_ctsa_CTSA_init(JNIEnv *env) {
    arima_result_class = (*env)->FindClass(env, "at/rafat/ctsa/types/ArimaResult");
    arima_result_class_constructor = (*env)->GetMethodID(env, arima_result_class, "<init>", "([D[D)V");
}

/**
 * Makes an estimation using auto_arima
 * It will automatically detect the appropriate (p, d, q)(P, D, Q) values within the provided range
 *
 * @param env JNI environment
 * @param ts time series double array
 * @param p p max
 * @param d d max
 * @param q q max
 * @param P P max
 * @param D D max
 * @param Q Q max
 * @param s seasonality
 * @param approximation approximation
 * @param stepwise stepwise
 * @param method method to use
 * @param opt optimization method
 * @param L periods to predict
 * @return arima result object
 */
JNIEXPORT jobject JNICALL
Java_at_rafat_ctsa_CTSA_exec(JNIEnv *env,

    const jdoubleArray ts,
    const jint p, const jint d, const jint q,
    const jint P, const jint D, const jint Q,
    const jint s,
    const jint approximation, const jint stepwise, const jint method, const jint opt,
    const jint L

    ) {

    int order[3] = {p, d, q};
    int seasonal[3] = {P, D, Q};

    const jsize N = (*env)->GetArrayLength(env, ts);
    auto_arima_object obj = auto_arima_init(order, seasonal, s, 0, N);

    auto_arima_setApproximation(obj, approximation);
    auto_arima_setStepwise(obj, stepwise);
    auto_arima_setVerbose(obj, 0);
    auto_arima_setMethod(obj, method);
    auto_arima_setOptMethod(obj, opt);

    // Allocate tsArray
    jdouble *tsArray = (*env)->GetDoubleArrayElements(env, ts, nullptr);
    auto_arima_exec(obj, tsArray, nullptr);

    const auto forecast = (double*)malloc(sizeof(double) * L);
    const auto errors = (double*)malloc(sizeof(double) * L);
    auto_arima_predict(obj, tsArray, nullptr, L, nullptr, forecast, errors);

    const jdoubleArray java_forecast = (*env)->NewDoubleArray(env, L);
    const jdoubleArray java_errors = (*env)->NewDoubleArray(env, L);
    (*env)->SetDoubleArrayRegion(env, java_forecast, 0, L, forecast);
    (*env)->SetDoubleArrayRegion(env, java_errors, 0, L, errors);

    // Allocate class reference
    // const jclass arima_result_class = (*env)->FindClass(env, "at/rafat/ctsa/types/ArimaResult");
    // jmethodID arima_result_class_constructor = (*env)->GetMethodID(env, arima_result_class, "<init>", "([D[D)V");
    jobject result = (*env)->NewObject(env, arima_result_class, arima_result_class_constructor, java_forecast, java_errors);

    // Release references
    (*env)->DeleteLocalRef(env, java_errors);
    (*env)->DeleteLocalRef(env, java_forecast);
    // (*env)->DeleteLocalRef(env, arima_result_class);
    (*env)->ReleaseDoubleArrayElements(env, ts, tsArray, 0);

    free(forecast);
    free(errors);

    auto_arima_free(obj);

    return result;
}

JNIEXPORT void JNICALL
Java_at_rafat_ctsa_CTSA_destroy(JNIEnv *env) {
    (*env)->DeleteLocalRef(env, arima_result_class);
}
