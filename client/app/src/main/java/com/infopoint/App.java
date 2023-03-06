/*
 * Scritto da Valentino Bocchetti il 6/3/2023 alle ore 11:11
 *
 * Copyright © 2023 InfoPoint
*/

package com.infopoint;

import android.app.Application;
import android.util.Log;

import dagger.hilt.android.HiltAndroidApp;

/*
    All apps using Hilt must contain an Application class annotated with @HiltAndroidApp.
    @HiltAndroidApp kicks off the code generation of the Hilt components and also generates a base class
    for your application that uses those generated components. Because the code generation needs access to all of your modules,
    the target that compiles your Application class also needs to have all of your Dagger modules in its transitive dependencies.
*/
@HiltAndroidApp
public class App extends Application {
    private static final String _TAG = "[App] ";

    @Override
    public void onCreate() {
        Log.d(_TAG, "Starting application");
        super.onCreate();
    }
}