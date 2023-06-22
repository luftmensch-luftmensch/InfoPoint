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
 *   First written in 22/6/2023 at 10:36
 *
 */

package com.infopoint.ui.activity.intro;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
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
    private Button nextButton, gettingStartedButton, skipButton;
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
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.intro_activity);
        setUI();
    }

    private void setUI() {
        nextButton = findViewById(R.id.intro_activity_next_button);
        gettingStartedButton = findViewById(R.id.intro_activity_getting_started_button);
        skipButton = findViewById(R.id.intro_activity_skip_button);

        layout = findViewById(R.id.intro_activity_tab_layout);

        pager = findViewById(R.id.intro_activity_view_pager);
        pager.setAdapter(new IntroAdapter(this, items));
        layout.setupWithViewPager(pager);

        nextButton.setOnClickListener(click -> {
            currPos = pager.getCurrentItem();
            if (currPos < items.size()) {
                currPos++;
                pager.setCurrentItem(currPos);
            }

            if (currPos == items.size() - 1) {
                loadLastScreen();
            }

        });

        gettingStartedButton.setOnClickListener(click -> {
            StorageManager.with(this).write(Constants.INTRO_VIEWED, true);
            startActivity(new Intent(IntroActivity.this, LoginActivity.class));
            finish();
        });

        skipButton.setOnClickListener(v -> {
            Log.d(_TAG, "Skipping intro");
            StorageManager.with(this).write(Constants.INTRO_VIEWED, true);
            startActivity(new Intent(IntroActivity.this, LoginActivity.class));
            finish();
        });

    }
    private void loadLastScreen() {
        nextButton.setVisibility(View.INVISIBLE);
        skipButton.setVisibility(View.INVISIBLE);
        gettingStartedButton.setVisibility(View.VISIBLE);
        gettingStartedButton.setAnimation(AnimationUtils.loadAnimation(this, R.anim.intro_animation));
    }

}