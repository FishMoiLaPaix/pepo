<<<<<<< HEAD
# Proguard rules to preserve Cardboard OSS as a dependency.

# Keep classes, methods, and fields that are accessed with JNI.
-keep class com.google.cardboard.sdk.UsedByNative
-keepclasseswithmembers,includedescriptorclasses class ** {
  @com.google.cardboard.sdk.UsedByNative *;
}

# According to the ProGuard version being used, `-shrinkunusedprotofields`
# flag can be added to enable protobuf-related optimizations.
-keep class com.google.cardboard.proto.** { *; }
=======
# Add project specific ProGuard rules here.
# You can control the set of applied configuration files using the
# proguardFiles setting in build.gradle.
#
# For more details, see
#   http://developer.android.com/guide/developing/tools/proguard.html

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface
# class:
#-keepclassmembers class fqcn.of.javascript.interface.for.webview {
#   public *;
#}

# Uncomment this to preserve the line number information for
# debugging stack traces.
#-keepattributes SourceFile,LineNumberTable

# If you keep the line number information, uncomment this to
# hide the original source file name.
#-renamesourcefileattribute SourceFile
>>>>>>> 5f55cf9 (Cardboard SDK initial release.)
