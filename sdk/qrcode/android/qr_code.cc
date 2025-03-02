/*
<<<<<<< HEAD
 * Copyright 2019 Google LLC
=======
 * Copyright 2019 Google Inc. All Rights Reserved.
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "qr_code.h"

<<<<<<< HEAD
#include <jni.h>

#include <array>
#include <atomic>

#include "jni_utils/android/jni_utils.h"

#define JNI_METHOD(return_type, clazz, method_name) \
  JNIEXPORT return_type JNICALL                     \
      Java_com_google_cardboard_sdk_##clazz##_##method_name

extern "C" {

JNI_METHOD(void, QrCodeCaptureActivity, nativeIncrementDeviceParamsChangedCount)
(JNIEnv* /*env*/, jobject /*obj*/);

}  // extern "C"

namespace cardboard::qrcode {
=======
namespace cardboard {
namespace qrcode {
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

namespace {
JavaVM* vm_;
jobject context_;
<<<<<<< HEAD
jclass cardboard_params_utils_class_;
jclass intent_class_;
jclass component_name_class_;
std::atomic<int> device_params_changed_count_(0);

static const std::array<JNINativeMethod, 1>
    kMethods_com_google_cardboard_sdk_QrCodeCaptureActivity = {
        {{"nativeIncrementDeviceParamsChangedCount", "()V",
          reinterpret_cast<void*>(
              Java_com_google_cardboard_sdk_QrCodeCaptureActivity_nativeIncrementDeviceParamsChangedCount)}},
};

// TODO(b/180938531): Release these global references.
void LoadJNIResources(JNIEnv* env) {
  cardboard_params_utils_class_ =
      reinterpret_cast<jclass>(env->NewGlobalRef(cardboard::jni::LoadJClass(
          env, "com/google/cardboard/sdk/qrcode/CardboardParamsUtils")));
  intent_class_ = reinterpret_cast<jclass>(env->NewGlobalRef(
      cardboard::jni::LoadJClass(env, "android/content/Intent")));
  component_name_class_ = reinterpret_cast<jclass>(env->NewGlobalRef(
      cardboard::jni::LoadJClass(env, "android/content/ComponentName")));

  // Registering native methods used within the SDK by the Java class
  // QrCodeCaptureActivity. See
  // https://developer.android.com/training/articles/perf-jni#native-libraries
  jclass qr_code_scanner_activity_name_class =
      reinterpret_cast<jclass>(cardboard::jni::LoadJClass(
          env, "com/google/cardboard/sdk/QrCodeCaptureActivity"));
  env->RegisterNatives(
      qr_code_scanner_activity_name_class,
      kMethods_com_google_cardboard_sdk_QrCodeCaptureActivity.data(),
      kMethods_com_google_cardboard_sdk_QrCodeCaptureActivity.size());
}

void IncrementDeviceParamsChangedCount() { device_params_changed_count_++; }

=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}  // anonymous namespace

void initializeAndroid(JavaVM* vm, jobject context) {
  vm_ = vm;
  context_ = context;
<<<<<<< HEAD

  JNIEnv* env;
  cardboard::jni::LoadJNIEnv(vm_, &env);
  LoadJNIResources(env);
=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
}

std::vector<uint8_t> getCurrentSavedDeviceParams() {
  JNIEnv* env;
<<<<<<< HEAD
  cardboard::jni::LoadJNIEnv(vm_, &env);

  jmethodID readDeviceParams =
      env->GetStaticMethodID(cardboard_params_utils_class_, "readDeviceParams",
                             "(Landroid/content/Context;)[B");
  jbyteArray byteArray = static_cast<jbyteArray>(env->CallStaticObjectMethod(
      cardboard_params_utils_class_, readDeviceParams, context_));
=======
  vm_->GetEnv((void**)&env, JNI_VERSION_1_6);

  jclass cardboardParamsUtilsClass =
      env->FindClass("com/google/cardboard/qrcode/CardboardParamsUtils");
  jmethodID readDeviceParamsFromExternalStorage = env->GetStaticMethodID(
      cardboardParamsUtilsClass, "readDeviceParamsFromExternalStorage", "()[B");
  jbyteArray byteArray = (jbyteArray)env->CallStaticObjectMethod(
      cardboardParamsUtilsClass, readDeviceParamsFromExternalStorage);

>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  if (byteArray == nullptr) {
    return {};
  }

<<<<<<< HEAD
  const int length = env->GetArrayLength(byteArray);

=======
  int length = env->GetArrayLength(byteArray);
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  std::vector<uint8_t> buffer;
  buffer.resize(length);
  env->GetByteArrayRegion(byteArray, 0, length,
                          reinterpret_cast<jbyte*>(&buffer[0]));
  return buffer;
}

void scanQrCodeAndSaveDeviceParams() {
  // Get JNI environment pointer
  JNIEnv* env;
<<<<<<< HEAD
  cardboard::jni::LoadJNIEnv(vm_, &env);

  // Get instance of Intent
  jmethodID newIntent = env->GetMethodID(intent_class_, "<init>", "()V");
  jobject intentObject = env->NewObject(intent_class_, newIntent);

  // Get instance of ComponentName
  jmethodID newComponentName =
      env->GetMethodID(component_name_class_, "<init>",
                       "(Landroid/content/Context;Ljava/lang/String;)V");
  jstring className =
      env->NewStringUTF("com.google.cardboard.sdk.QrCodeCaptureActivity");
  jobject componentNameObject = env->NewObject(
      component_name_class_, newComponentName, context_, className);

  // Set component in intent
  jmethodID setComponent = env->GetMethodID(
      intent_class_, "setComponent",
=======
  vm_->GetEnv((void**)&env, JNI_VERSION_1_6);

  // Get instance of Intent
  jclass intentClass = env->FindClass("android/content/Intent");
  jmethodID newIntent = env->GetMethodID(intentClass, "<init>", "()V");
  jobject intentObject = env->NewObject(intentClass, newIntent);

  // Get instance of ComponentName
  jclass componentNameClass = env->FindClass("android/content/ComponentName");
  jmethodID newComponentName = env->GetMethodID(
      componentNameClass, "<init>", "(Landroid/content/Context;Ljava/lang/String;)V");
  jstring className =
      env->NewStringUTF("com.google.cardboard.QrCodeCaptureActivity");
  jobject componentNameObject = env->NewObject(
      componentNameClass, newComponentName, context_, className);

  // Set component in intent
  jmethodID setComponent = env->GetMethodID(
      intentClass, "setComponent",
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
      "(Landroid/content/ComponentName;)Landroid/content/Intent;");
  env->CallObjectMethod(intentObject, setComponent, componentNameObject);

  // Start activity using intent
  jclass activityClass = env->GetObjectClass(context_);
  jmethodID startActivity = env->GetMethodID(activityClass, "startActivity",
                                             "(Landroid/content/Intent;)V");
  env->CallVoidMethod(context_, startActivity, intentObject);
}

<<<<<<< HEAD
void saveDeviceParams(const uint8_t* uri, int size) {
  // Get JNI environment pointer
  JNIEnv* env;
  cardboard::jni::LoadJNIEnv(vm_, &env);

  // Allocate memory for uri_jbyte_array
  jbyteArray uri_jbyte_array = env->NewByteArray(size);

  // Copy the uint8_t* to a jbyteArray
  jbyte* java_data_ptr = env->GetByteArrayElements(uri_jbyte_array, 0);
  memcpy(java_data_ptr, uri, size);
  env->SetByteArrayRegion(uri_jbyte_array, 0, size, java_data_ptr);

  // Get the Java class method to be called
  jmethodID save_params_from_uri_method =
      env->GetStaticMethodID(cardboard_params_utils_class_, "saveParamsFromUri",
                             "([BLandroid/content/Context;)V");

  // Call the Java class method
  env->CallStaticVoidMethod(cardboard_params_utils_class_,
                            save_params_from_uri_method, uri_jbyte_array,
                            context_);

  // Release memory allocated by uri_jbyte_array
  env->ReleaseByteArrayElements(uri_jbyte_array, java_data_ptr, 0);

  IncrementDeviceParamsChangedCount();
}

int getDeviceParamsChangedCount() { return device_params_changed_count_; }

}  // namespace cardboard::qrcode

extern "C" {

JNI_METHOD(void, QrCodeCaptureActivity, nativeIncrementDeviceParamsChangedCount)
(JNIEnv* /*env*/, jobject /*obj*/) {
  cardboard::qrcode::IncrementDeviceParamsChangedCount();
}

}  // extern "C"
=======
}  // namespace qrcode
}  // namespace cardboard
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
