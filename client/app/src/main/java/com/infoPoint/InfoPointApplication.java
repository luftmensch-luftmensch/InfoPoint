/*
 * Scritto da Valentino Bocchetti il 25/2/2023 alle ore 14:42
 *
 * Copyright © 2023 InfoPoint
*/

package com.infoPoint;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import androidx.core.splashscreen.SplashScreen;

import com.infoPoint.core.util.Constants;
import com.infoPoint.core.preferences.PreferencesManager;

public class InfoPointApplication extends AppCompatActivity { // MultiDexApplication
    private static final String _TAG = "[InfoPointApplication] ";
    @Override
    public void onCreate(Bundle savedInstanceState){
        SplashScreen splashScreen = SplashScreen.installSplashScreen(this);
        super.onCreate(savedInstanceState);

        PreferencesManager.init(getApplicationContext());

        // Keep the splash screen visible for this Activity
        splashScreen.setKeepOnScreenCondition(() -> true );

        handleUserStatus();
        finish();

    }

    private static void handleUserStatus(){
        Log.d(_TAG, "Handle route");
        if(PreferencesManager.contains(Constants.FIRST_RUN)){
        } else {

        }

    }
}