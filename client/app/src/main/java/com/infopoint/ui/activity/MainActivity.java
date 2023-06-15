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

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.MenuItem;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.navigation.NavController;
import androidx.navigation.NavDestination;
import androidx.navigation.NavOptions;
import androidx.navigation.Navigation;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import com.google.android.material.bottomappbar.BottomAppBar;
import com.google.android.material.bottomnavigation.BottomNavigationView;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.navigation.NavigationBarView;
import com.google.android.material.navigation.NavigationView;
import com.infopoint.R;

public class MainActivity extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener, NavigationBarView.OnItemReselectedListener, NavController.OnDestinationChangedListener {

    private final static String _TAG = "[MainActivity] ";
    public NavController navController;
    public BottomAppBar bottomAppBar;
    public DrawerLayout drawerLayout;

    public FloatingActionButton fab;
    public Toolbar toolbar;
    public NavOptions.Builder leftToRightBuilder, rightToLeftBuilder;
    private AppBarConfiguration appBarConfiguration;
    private BottomNavigationView bottomNavigationView;
    private NavigationView navigationView;

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        Log.d(_TAG, "onCreate: Starting...");
        setContentView(R.layout.main_activity);
        setUI();
    }

    private void setUI() {
        toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawerLayout = findViewById(R.id.drawer_layout);

        bottomAppBar = findViewById(R.id.bottom_app_bar);
        bottomNavigationView = findViewById(R.id.bottom_nav_view);
        navigationView = findViewById(R.id.nav_view);
        fab = findViewById(R.id.fab);

        navController = Navigation.findNavController(this, R.id.nav_host_fragment);
        navController.addOnDestinationChangedListener(this);
        appBarConfiguration = new AppBarConfiguration.Builder(R.id.nav_home, R.id.nav_starred, R.id.search, R.id.nav_profile, R.id.nav_about_us, R.id.nav_logout)
                .setOpenableLayout(drawerLayout)
                .build();

        NavigationUI.setupActionBarWithNavController(this, navController, appBarConfiguration);
        NavigationUI.setupWithNavController(navigationView, navController);
        NavigationUI.setupWithNavController(bottomNavigationView, navController);

        navigationView.setCheckedItem(R.id.nav_home);
        bottomNavigationView.setSelectedItemId(R.id.nav_home);

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



        // Specific handler
        toolbar.setNavigationOnClickListener(v -> {
            if (drawerLayout.isDrawerVisible(GravityCompat.START))
                drawerLayout.closeDrawer(GravityCompat.START);
            else
                drawerLayout.openDrawer(GravityCompat.START);
        });

    }

    @Override
    public void onDestinationChanged(@NonNull NavController navController, @NonNull NavDestination destination, @Nullable Bundle bundle) {
        Log.d(_TAG, "onDestinationChanged: starts");

    }

    @Override
    public void onNavigationItemReselected(@NonNull MenuItem item) {

    }

    @SuppressLint("NonConstantResourceId")
    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem item) {
        if (drawerLayout.isDrawerVisible(GravityCompat.START))
            drawerLayout.closeDrawer(GravityCompat.START);

        if (item.getItemId() == R.id.nav_home) {
            Log.d(_TAG, "onNavigationItemSelected: Opening Home Fragment");
            navController.navigate(R.id.nav_home, null, rightToLeftBuilder.build());
        } else if (item.getItemId() == R.id.nav_starred) {

            Log.d(_TAG, "onNavigationItemSelected: Opening Starred Fragment");
            navController.navigate(R.id.nav_starred, null, leftToRightBuilder.build());

        }

        return false;
    }
    @Override
    public void onBackPressed() {
        Log.d(_TAG, "onBackPressed: back pressed");
        if (drawerLayout.isDrawerVisible(GravityCompat.START))
            drawerLayout.closeDrawer(GravityCompat.START);
        else if (navController.getCurrentDestination().getId() == R.id.nav_home) {
            finishAffinity();
            overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
        } else
            super.onBackPressed();
    }
}