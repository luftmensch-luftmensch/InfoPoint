/*
 * Copyright © 2023 InfoPoint. All rights reserved.
 *
 * Licensed under the MIT License;
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://mit-license.org/
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * First written in 6/3/2023 at 11:11
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

/**
 * Main entry point for the application
 * @author valentino
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