[TOC]


# GameV4

Game with Cocos2d-x V4 [commit](https://github.com/cocos2d/cocos2d-x/commit/95e5d868ce5958c0dadfc485bdda52f1bc404fe0)


# ENV

## iOS/macOS

```
open frameworks/runtime-src/proj.ios_mac/gamev4.xcodeproj
```

1. macOS 10.15.7
2. Xcode 12.4


## Android

Use [`Android Studio`](https://developer.android.com/studio) import the `frameworks/runtime-src/proj.android` project file.

NDK version: r16b, [Windows 64-bit](https://dl.google.com/android/repository/android-ndk-r16b-windows-x86_64.zip), [Mac OS X](https://dl.google.com/android/repository/android-ndk-r16b-darwin-x86_64.zip)

1. [Settings for Android Studio 4.1.2](https://github.com/c0i/GameV4/commit/10b1b9ea13755bec157c190ea029f681788cd9c0):
    - Gradle Plugin Version 4.0.0
    - Gradle Version 6.1.1

2. [Settings for Android Studio 3.5.1](https://github.com/c0i/GameV4/commit/71b9fae1324394e3f9db6ee4f794d3b3a296bc75):
    - Gradle Plugin Version 3.1.0
    - Gradle Version 5.1.1

### Fix NDK when macOS >= 10.15

1. Trust it

    ```
    xattr -rd com.apple.quarantine android-ndk-r16b
    ```

2. or Download it from Android Studio -> SDK Manager


## Windows


Use `Visual Studio` to open `frameworks/runtime-src/proj.win32/gamev4.sln`.

1. Visual Studio 2019


## Command line

```
# build mac
frameworks/cocos2d-x/tools/cocos2d-console/bin/cocos compile -p mac

# build ios
frameworks/cocos2d-x/tools/cocos2d-console/bin/cocos compile -p ios

# build android
frameworks/cocos2d-x/tools/cocos2d-console/bin/cocos compile -p android

# win32
python -m pip install vswhere # to find vs 2019
frameworks\cocos2d-x\tools\cocos2d-console\bin\cocos.bat compile -p win32 --vs 2019

# win32-android
set ANDROID_SDK_ROOT=D:/sdk/android/android-ndk-r18b
set JAVA_HOME=D:/app/jdk-15.0.1
frameworks\cocos2d-x\tools\cocos2d-console\bin\cocos.bat compile -p android
```

