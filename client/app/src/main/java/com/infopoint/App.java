/*
 * Scritto da Valentino Bocchetti il 6/3/2023 alle ore 11:11
 *
 * Copyright © 2023 InfoPoint
*/

package com.infopoint;

import android.app.Application;
import android.util.Log;

import dagger.hilt.android.HiltAndroidApp;

@HiltAndroidApp
public class App extends Application {
    private static final String _TAG = "[App] ";

    @Override
    public void onCreate() {
        Log.d(_TAG, "Starting application");
        super.onCreate();
    }
}