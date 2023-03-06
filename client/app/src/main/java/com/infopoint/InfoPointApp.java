/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:51
 *
 * Copyright © 2023 InfoPoint
*/
package com.infopoint;

import android.animation.ObjectAnimator;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.animation.AnticipateInterpolator;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.splashscreen.SplashScreen;

import com.infopoint.core.preferences.PreferencesManager;
import com.infopoint.core.utils.Constants;
import com.infopoint.ui.intro.InfoPointIntro;

import dagger.hilt.android.AndroidEntryPoint;
import dagger.hilt.android.HiltAndroidApp;

@AndroidEntryPoint
public class InfoPointApp extends AppCompatActivity {

    private static final String _TAG = "[InfoPointApplication] ";

    private static InfoPointApp instance;

    public static InfoPointApp getInstance() { return instance; }

    @Override
    public void onCreate(Bundle savedInstanceState){
        SplashScreen splashScreen = SplashScreen.installSplashScreen(this);
        super.onCreate(savedInstanceState);
        instance = this;

        PreferencesManager.init(getApplicationContext());

        // Keep the splash screen visible for this Activity
        splashScreen.setKeepOnScreenCondition(() -> true );

        //handleUserStatus();
        finish();

    }

    private void handleUserStatus(){
        Log.d(_TAG, "Handle route");
        if(PreferencesManager.contains(Constants.FIRST_RUN)){
            Log.d(_TAG, "First run! Move view to intro");
            Intent intent;
            intent = new Intent(InfoPointApp.this, InfoPointIntro.class);
        } else {
            Log.d(_TAG, "Not first run! Checking stored credential...");
        }

    }
}