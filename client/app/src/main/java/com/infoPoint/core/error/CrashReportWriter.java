/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:30
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.error;

import android.os.Build;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.multidex.BuildConfig;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class CrashReportWriter implements Thread.UncaughtExceptionHandler {
    private static final String _TAG = "[CrashReportWriter] ";
    private final Thread.UncaughtExceptionHandler defaultHandler;

    public CrashReportWriter(Thread.UncaughtExceptionHandler defaultHandler) {
        this.defaultHandler = defaultHandler;
    }

    @Override
    public void uncaughtException(@NonNull Thread t, @NonNull Throwable e) {
        write(e);

    }

    public static void write(Throwable e){
        // TODO: Move to a proper log file
        Log.d(_TAG, "## Crash info");
        Log.d(_TAG, "Time: " + new SimpleDateFormat("dd-MM-yyyy HH:mm:ss", Locale.getDefault()).format(new Date()));
        Log.d(_TAG, "InfoPoint version: " + BuildConfig.VERSION_NAME);
        Log.d(_TAG, "### StackTrace");
        Log.d(_TAG, "```");
        Log.d(_TAG, "Cause: " + e.getLocalizedMessage());
    }

    public static String getSystemInfo() {
        return "## Environment"
                + "\nAndroid version: " + Build.VERSION.RELEASE
                + "\nOS version: " + System.getProperty("os.version")
                + "\nAntennaPod version: " + BuildConfig.VERSION_NAME
                + "\nModel: " + Build.MODEL
                + "\nDevice: " + Build.DEVICE
                + "\nProduct: " + Build.PRODUCT;
    }
}
