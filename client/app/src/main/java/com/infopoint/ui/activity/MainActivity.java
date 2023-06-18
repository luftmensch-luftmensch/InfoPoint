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
 *   First written in 15/6/2023 at 15:18
 *
*/

package com.infopoint.ui.activity;

import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;
import androidx.navigation.NavController;
import androidx.navigation.NavOptions;
import androidx.navigation.Navigation;

import com.infopoint.R;
import com.ismaeldivita.chipnavigation.ChipNavigationBar;


public class MainActivity extends AppCompatActivity {
    private final static String _TAG = "[MainActivity] ";
    public NavController navController;
    public NavOptions.Builder leftToRightBuilder, rightToLeftBuilder;
    private ChipNavigationBar bar;

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        Log.d(_TAG, "onCreate: Starting...");
        setContentView(R.layout.main_activity);
        setUI();
    }

    private void setUI() {
        bar = findViewById(R.id.bottom_bar);
        bar.setItemSelected(R.id.nav_home, true);

        navController = Navigation.findNavController(this, R.id.nav_host_fragment);

        leftToRightBuilder = new NavOptions.Builder();
        leftToRightBuilder.setEnterAnim(R.anim.slide_in_right);
        leftToRightBuilder.setExitAnim(R.anim.slide_out_left);
        leftToRightBuilder.setPopEnterAnim(R.anim.slide_in_left);
        leftToRightBuilder.setPopExitAnim(R.anim.slide_out_right);
        leftToRightBuilder.setLaunchSingleTop(true);

        rightToLeftBuilder = new NavOptions.Builder();
        rightToLeftBuilder.setEnterAnim(R.anim.slide_in_left);
        rightToLeftBuilder.setExitAnim(R.anim.slide_out_right);
        rightToLeftBuilder.setPopEnterAnim(R.anim.slide_in_right);
        rightToLeftBuilder.setPopExitAnim(R.anim.slide_out_left);
        rightToLeftBuilder.setLaunchSingleTop(true);

        bar.setOnItemSelectedListener(item -> {
            if (item == R.id.nav_home) {
                if (navController.getCurrentDestination().getId() != R.id.nav_home) navController.navigate(R.id.nav_home, null, rightToLeftBuilder.build());
            } else if (item == R.id.nav_search) {
                if (navController.getCurrentDestination().getId() != R.id.nav_search) navController.navigate(R.id.nav_search, null, leftToRightBuilder.build());
            } else if (item == R.id.nav_starred) {
                if (navController.getCurrentDestination().getId() != R.id.nav_starred) navController.navigate(R.id.nav_starred, null, leftToRightBuilder.build());
            } else if (item == R.id.nav_profile) {
                if (navController.getCurrentDestination().getId() != R.id.nav_profile) navController.navigate(R.id.nav_profile, null, leftToRightBuilder.build());
            }
        });
    }

    @Override
    public void onBackPressed() {
        Log.d(_TAG, "onBackPressed");
        if (bar.getSelectedItemId() == R.id.nav_home) {
            Log.d(_TAG, "onBackPressed: Current destination Home -> Closing the app");
            finishAffinity();
            overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
        } else {
            navController.navigate(R.id.nav_home, null, rightToLeftBuilder.build());
            bar.setItemSelected(R.id.nav_home, true);
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        // TODO: Add SharedPreferences Logic
    }
}