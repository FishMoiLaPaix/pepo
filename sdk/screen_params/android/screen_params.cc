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
#include "screen_params.h"

#include <jni.h>

<<<<<<< HEAD
#include "jni_utils/android/jni_utils.h"

namespace cardboard::screen_params {
=======
namespace cardboard {
namespace screen_params {
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

namespace {
JavaVM* vm_;
jobject context_;

<<<<<<< HEAD
jclass screen_pixel_density_class_;
jclass screen_params_utils_class_;

=======
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
struct DisplayMetrics {
  float xdpi;
  float ydpi;
};

<<<<<<< HEAD
// TODO(b/180938531): Release these global references.
void LoadJNIResources(JNIEnv* env) {
  screen_params_utils_class_ =
      reinterpret_cast<jclass>(env->NewGlobalRef(cardboard::jni::LoadJClass(
          env, "com/google/cardboard/sdk/screenparams/ScreenParamsUtils")));
  screen_pixel_density_class_ = reinterpret_cast<jclass>(env->NewGlobalRef(
      cardboard::jni::LoadJClass(env,
                                 "com/google/cardboard/sdk/screenparams/"
                                 "ScreenParamsUtils$ScreenPixelDensity")));
}

DisplayMetrics getDisplayMetrics() {
  JNIEnv* env;
  cardboard::jni::LoadJNIEnv(vm_, &env);

  const jmethodID get_screen_pixel_density_method = env->GetStaticMethodID(
      screen_params_utils_class_, "getScreenPixelDensity",
      "(Landroid/content/Context;)Lcom/google/cardboard/sdk/screenparams/"
      "ScreenParamsUtils$ScreenPixelDensity;");
  const jobject screen_pixel_density = env->CallStaticObjectMethod(
      screen_params_utils_class_, get_screen_pixel_density_method, context_);
  const jfieldID xdpi_id =
      env->GetFieldID(screen_pixel_density_class_, "xdpi", "F");
  const jfieldID ydpi_id =
      env->GetFieldID(screen_pixel_density_class_, "ydpi", "F");

  const float xdpi = env->GetFloatField(screen_pixel_density, xdpi_id);
  const float ydpi = env->GetFloatField(screen_pixel_density, ydpi_id);
=======
DisplayMetrics getDisplayMetrics() {
  JNIEnv* env;
  vm_->GetEnv((void**)&env, JNI_VERSION_1_6);

  jclass display_metrics_cls = env->FindClass("android/util/DisplayMetrics");
  jmethodID display_metrics_constructor =
      env->GetMethodID(display_metrics_cls, "<init>", "()V");
  jclass activity_cls = env->FindClass("android/app/Activity");
  jmethodID get_window_manager = env->GetMethodID(
      activity_cls, "getWindowManager", "()Landroid/view/WindowManager;");
  jclass window_manager_cls = env->FindClass("android/view/WindowManager");
  jmethodID get_default_display = env->GetMethodID(
      window_manager_cls, "getDefaultDisplay", "()Landroid/view/Display;");
  jclass display_cls = env->FindClass("android/view/Display");
  jmethodID get_metrics = env->GetMethodID(display_cls, "getRealMetrics",
                                           "(Landroid/util/DisplayMetrics;)V");

  jobject display_metrics =
      env->NewObject(display_metrics_cls, display_metrics_constructor);
  jobject window_manager = env->CallObjectMethod(context_, get_window_manager);
  jobject default_display =
      env->CallObjectMethod(window_manager, get_default_display);
  env->CallVoidMethod(default_display, get_metrics, display_metrics);

  jfieldID xdpi_id = env->GetFieldID(display_metrics_cls, "xdpi", "F");
  jfieldID ydpi_id = env->GetFieldID(display_metrics_cls, "ydpi", "F");

  float xdpi = env->GetFloatField(display_metrics, xdpi_id);
  float ydpi = env->GetFloatField(display_metrics, ydpi_id);

>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
  return {xdpi, ydpi};
}

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

void getScreenSizeInMeters(int width_pixels, int height_pixels,
                           float* out_width_meters, float* out_height_meters) {
<<<<<<< HEAD
  const DisplayMetrics display_metrics = getDisplayMetrics();
=======
  DisplayMetrics display_metrics = getDisplayMetrics();
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)

  *out_width_meters = (width_pixels / display_metrics.xdpi) * kMetersPerInch;
  *out_height_meters = (height_pixels / display_metrics.ydpi) * kMetersPerInch;
}

<<<<<<< HEAD
}  // namespace cardboard::screen_params
=======
}  // namespace screen_params
}  // namespace cardboard
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
