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
 * First written in 2/3/2023 at 11:51
*/

package com.infopoint.ui.main;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.splashscreen.SplashScreen;
import androidx.core.view.WindowCompat;
import androidx.navigation.NavController;
import androidx.navigation.fragment.NavHostFragment;

import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.infopoint.core.preferences.PreferencesManager;
import com.infopoint.core.utils.Constants;
import com.infopoint.databinding.MainActivityBinding;
import com.infopoint.ui.intro.InfoPointIntro;

import dagger.hilt.android.AndroidEntryPoint;

/**
 * Main Activity for the application
 * @author valentino
*/
@AndroidEntryPoint
public class MainActivity extends AppCompatActivity {

    private static final String _TAG = "[InfoPointApplication] ";


    private static MainActivity instance;

    public static MainActivity getInstance() { return instance; }

    private MainActivityBinding binding;
    // NavView & NavController
    private NavHostFragment navHostFragment;
    private BottomNavigationView navView;
    private NavController navController;


    @Override
    public void onCreate(Bundle savedInstanceState) {
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

    private void setupUi() {
        WindowCompat.setDecorFitsSystemWindows(getWindow(), false);
        navHostFragment = (NavHostFragment) getSupportFragmentManager().findFragmentById(binding.navHostFragmentActivityMain.getId());
        navController = navHostFragment.getNavController();
        navView = binding.navView;
    }

    private void setListeners() {

    }

    private void checkClientStatus() {

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