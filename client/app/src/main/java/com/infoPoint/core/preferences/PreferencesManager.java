/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:29
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.preferences;

import android.content.Context;
import android.content.SharedPreferences;
import android.util.Log;

import javax.inject.Singleton;

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