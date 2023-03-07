/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:51
 *
 * Copyright © 2023 InfoPoint
*/
package com.infopoint.ui.main;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.splashscreen.SplashScreen;
import androidx.core.view.WindowCompat;
import androidx.navigation.fragment.NavHostFragment;


import com.infopoint.core.preferences.PreferencesManager;
import com.infopoint.core.utils.Constants;
import com.infopoint.databinding.MainActivityBinding;
import com.infopoint.ui.intro.InfoPointIntro;

import dagger.hilt.android.AndroidEntryPoint;

@AndroidEntryPoint
public class MainActivity extends AppCompatActivity {

    private static final String _TAG = "[InfoPointApplication] ";


    private static MainActivity instance;

    public static MainActivity getInstance() { return instance; }

    private MainActivityBinding binding;


    @Override
    public void onCreate(Bundle savedInstanceState){
        SplashScreen splashScreen = SplashScreen.installSplashScreen(this);
        super.onCreate(savedInstanceState);
        instance = this;

        PreferencesManager.init(getApplicationContext());

        binding = MainActivityBinding.inflate(getLayoutInflater());

        setContentView(binding.getRoot());

        setupUi();
        // Keep the splash screen visible for this Activity
        //splashScreen.setKeepOnScreenCondition(() -> true );

        //handleUserStatus();
        //finish();

    }

    private void setupUi(){
        WindowCompat.setDecorFitsSystemWindows(getWindow(), false);

        //NavHostFragment navHostFragment = getSupportFragmentManager().findFragmentById(binding.navHostFragmentActivityMain.getId());
        NavHostFragment navHostFragment;
        //navHostFragment = getSupportFragmentManager().findFragmentById(binding.navHostFragmentActivityMain.getId());
    }

    private void setListeners(){

    }

    private void handleUserStatus(){
        Log.d(_TAG, "Handle route");
        if(PreferencesManager.contains(Constants.FIRST_RUN)){
            Log.d(_TAG, "First run! Move view to intro");
            Intent intent;
            intent = new Intent(MainActivity.this, InfoPointIntro.class);
        } else {
            Log.d(_TAG, "Not first run! Checking stored credential...");
        }

    }
}