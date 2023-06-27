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
 *   First written in 16/6/2023 at 10:36
 *
*/

package com.infopoint.core.preferences;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import androidx.annotation.NonNull;

/** Wrapper class around {@link SharedPreferences} */
public class StorageManager {
    private static final String _TAG = "[StorageManager] ";
    private static final String PREF_NAME = "app_settings";

    private static StorageManager instance;
    private static SharedPreferences preferences;

    private StorageManager(@NonNull Context context) { preferences = context.getApplicationContext().getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE); }
    private StorageManager(@NonNull Context context, String key) { preferences = context.getApplicationContext().getSharedPreferences(key, Context.MODE_PRIVATE); }

    public static StorageManager with(@NonNull Context context) {
        if (instance == null)
            instance = new StorageManager(context);
        return instance;
    }

    public static StorageManager with(@NonNull Context context, boolean forceInstantiation) {
        if (forceInstantiation)
            instance = new StorageManager(context);
        return instance;
    }

    public static StorageManager with(@NonNull Context context, String preferencesName) {
        if (instance == null)
            instance = new StorageManager(context, preferencesName);
        return instance;
    }

    public String read(String key, String defaultValue) { return preferences.getString(key, defaultValue); }
    public Integer read(String key, Integer defaultValue) { return preferences.getInt(key, defaultValue); }
    public Long read(String key, Long defaultValue) { return preferences.getLong(key, defaultValue); }
    public Boolean read(String key, Boolean defaultValue) { return preferences.getBoolean(key, defaultValue); }

    public boolean contains(String key){ return preferences.contains(key); }

    public <T> void write(String key, T value) {
        SharedPreferences.Editor editor = preferences.edit();

        // Retrieve the type of value using the simple name of the underlying class as given in the source code
        // avoiding using instanceof for each possible type (Supported type are String, Integer, Long, Boolean)
        switch (value.getClass().getSimpleName()) {
            case "String" -> editor.putString(key, (String) value);
            case "Integer" -> editor.putInt(key, (Integer) value);
            case "Long" -> editor.putLong(key, (Long) value);
            case "Boolean" -> editor.putBoolean(key, (Boolean) value);
            default -> Log.d(_TAG, "Unknown type <" + value.getClass().getSimpleName() + "> was given");
        }
        editor.apply();
    }

    public void clear() { preferences.edit().clear().apply(); }
}