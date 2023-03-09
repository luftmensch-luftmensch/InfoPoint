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
 * First written in 2/3/2023 at 12:01
 */

package com.infopoint.core.preferences;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import javax.inject.Singleton;

/**
 * <strong>Manager</strong> for <strong>Shared Preferences</strong>
 * @author valentino
 */
@Singleton
public class PreferencesManager {
    private static final String _TAG = "[PreferencesManager] ";

    private static SharedPreferences preferences;

    private PreferencesManager(){}

    public static void init(Context context){
        Log.d(_TAG, "Initializing...");
        if(preferences == null)
            preferences = context.getSharedPreferences(context.getPackageName(), Context.MODE_PRIVATE);
    }

    public static String read(String key, String defaultValue){
        return preferences.getString(key, defaultValue);
    }

    public static boolean read(String key, boolean defaultValue){
        return preferences.getBoolean(key, defaultValue);
    }

    public static Long read(String key, Long defaultValue){
        return preferences.getLong(key, defaultValue);
    }

    public static Integer read(String key, Integer defaultValue){
        return preferences.getInt(key, defaultValue);
    }

    public static <T> void write(String key, T value){
        SharedPreferences.Editor editor = preferences.edit();

        // Retrieve the type of value using the simple name of the underlying class as given in the source code
        // avoiding using instanceof for each possible type (Supported type are String, Integer, Long, Boolean)
        switch (value.getClass().getSimpleName()) {
            case "String":
                editor.putString(key, (String) value);
                break;

            case "Integer":
                editor.putInt(key, (Integer) value);
                break;

            case "Long":
                editor.putLong(key, (Long) value);
                break;

            case "Boolean":
                editor.putBoolean(key, (Boolean) value);
                break;
            default:
                Log.d(_TAG, "Unkown type <" + value.getClass().getSimpleName() + "> was given");

                editor.apply();
        }
    }

    public static boolean contains(String key){ return preferences.contains(key); }
}
