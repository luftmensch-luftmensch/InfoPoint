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
 *   First written in 16/6/2023 at 11:28
 *
 */

package com.infopoint.ui.activity.intro;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import com.google.android.material.tabs.TabLayout;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.ui.activity.authentication.login.LoginActivity;

import java.util.List;

public class IntroActivity extends AppCompatActivity {
    private final static String _TAG = "[IntroActivity] ";

    private ViewPager pager;
    private TabLayout layout;

    private Button nextButton, prevButton, gettingStartedButton, skipButton;
    private Animation animation;
    private int currPos = 0;

    // TODO: Update values diplayed in the intro
    private static final List<SlideItem> items = List.of(
            new SlideItem("Un nuovo strumento", "per la conoscenza", R.drawable.avatar_icon),
            new SlideItem("Scopri tutti i segreti", "delle opere", R.drawable.avatar_icon),
            new SlideItem("TODO", "TODO", R.drawable.avatar_icon)
    );

    @Override
    protected void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        Log.d(_TAG, "onCreate: Starting...");
        setContentView(R.layout.intro_activity);
        setUI();

    }
    private void setUI() {
        nextButton = findViewById(R.id.intro_next_button);
        prevButton = findViewById(R.id.intro_prev_button);
        skipButton = findViewById(R.id.intro_skip_button);
        gettingStartedButton = findViewById(R.id.intro_getting_started_button);
        animation = AnimationUtils.loadAnimation(this, R.anim.intro_animation);

        layout = findViewById(R.id.intro_tab_layout);
        pager = findViewById(R.id.intro_view_pager);
        pager.setAdapter(new IntroAdapter(this, items));
        layout.setupWithViewPager(pager);

        // Button Handler setup
        nextButton.setOnClickListener(v -> {
            prevButton.setVisibility(View.VISIBLE);
            currPos = pager.getCurrentItem();

            if (currPos < items.size()) {
                currPos++;
                pager.setCurrentItem(currPos);
            }

            if (currPos < items.size() - 1) {
                loadLast();
            }
        });

        prevButton.setOnClickListener(v -> {
            currPos = pager.getCurrentItem();

            nextButton.setVisibility(View.VISIBLE);
            skipButton.setVisibility(View.VISIBLE);
            layout.setVisibility(View.VISIBLE);
            gettingStartedButton.setVisibility(View.INVISIBLE);
            if (currPos > 0) {
                currPos--;
                pager.setCurrentItem(currPos);
            }

            if (currPos == 0)
                loadFirst();

        });

        skipButton.setOnClickListener(v -> {
            StorageManager.with(this).write(Constants.INTRO_VIEWED, true);
            startActivity(new Intent(IntroActivity.this, LoginActivity.class));
            overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            finish();
        });

        gettingStartedButton.setOnClickListener(v -> {
            StorageManager.with(this).write(Constants.INTRO_VIEWED, true);
            startActivity(new Intent(IntroActivity.this, LoginActivity.class));
            overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            finish();
        });

        layout.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {
                if (tab.getPosition() == items.size() - 1)
                    loadLast();
                else if (tab.getPosition() == 0)
                    loadFirst();
                else {
                    nextButton.setVisibility(View.VISIBLE);
                    skipButton.setVisibility(View.VISIBLE);
                    layout.setVisibility(View.VISIBLE);
                    gettingStartedButton.setVisibility(View.INVISIBLE);
                    prevButton.setVisibility(View.VISIBLE);
                }
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) { }

            @Override
            public void onTabReselected(TabLayout.Tab tab) { }
        });
    }

    private void loadFirst() {
        Log.d(_TAG, "loadFirst:");
        nextButton.setVisibility(View.VISIBLE);
        skipButton.setVisibility(View.VISIBLE);
        layout.setVisibility(View.VISIBLE);
        gettingStartedButton.setVisibility(View.INVISIBLE);
        prevButton.setVisibility(View.INVISIBLE);
    }

    private void loadLast() {
        Log.d(_TAG, "loadLast");
        nextButton.setVisibility(View.INVISIBLE);
        skipButton.setVisibility(View.INVISIBLE);
        layout.setVisibility(View.INVISIBLE);
        gettingStartedButton.setVisibility(View.VISIBLE);
        prevButton.setVisibility(View.VISIBLE);
        gettingStartedButton.setAnimation(animation);
    }
}