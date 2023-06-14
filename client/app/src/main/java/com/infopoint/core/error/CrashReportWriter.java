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
 *   @author Valentino Bocchetti
 *   First written in 13/6/2023 at 21:40
 *
*/

package com.infopoint.core.error;

import android.os.Build;
import android.util.Log;
import androidx.annotation.NonNull;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class CrashReportWriter implements Thread.UncaughtExceptionHandler {
    private static final String _TAG = "[CrashReportWriter] ";

    @Override
    public void uncaughtException(@NonNull Thread t, @NonNull Throwable e) { write(e); }

    public static void write(Throwable e){
        Log.d(_TAG, "## Crash info");
        Log.d(_TAG, "Time: " + new SimpleDateFormat("dd-MM-yyyy HH:mm:ss", Locale.getDefault()).format(new Date()));
        Log.d(_TAG, "InfoPoint version: " );
        Log.d(_TAG, "### StackTrace");
        Log.d(_TAG, "```");
        Log.d(_TAG, "Cause: " + e.getLocalizedMessage());
    }

    public static String getSystemInfo() {
        return "## Environment"
                + "\nAndroid version: " + Build.VERSION.RELEASE
                + "\nOS version: " + System.getProperty("os.version")
                + "\nModel: " + Build.MODEL
                + "\nDevice: " + Build.DEVICE
                + "\nProduct: " + Build.PRODUCT;
    }
}