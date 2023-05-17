#include <jni.h>
#include "SkiaPainter.cpp"

#ifndef _Included_cn_treecat_skiapaint_SkPainter
#define _Included_cn_treecat_skiapaint_SkPainter
#ifdef __cplusplus
extern "C" {
#endif
	/*
	 * Class:     cn_treecat_skiapaint_SkPainter
	 * Method:    executeScript
	 * Signature: (Ljava/lang/String;)V
	 */
	JNIEXPORT void JNICALL Java_cn_treecat_skiapaint_SkPainter_executeScript
	(JNIEnv*, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif


JNIEXPORT void JNICALL Java_cn_treecat_skiapaint_SkPainter_executeScript
(JNIEnv* env, jobject obj, jstring filename) {
	const char* jnamestr = env->GetStringUTFChars(filename, NULL);
	draw(jnamestr);
}

