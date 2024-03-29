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
 *   First written in 13/6/2023 at 18:47
 *
*/

package com.infopoint;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.WindowManager;
import android.view.animation.AnimationUtils;
import androidx.appcompat.app.AppCompatActivity;

import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.ui.activity.MainActivity;
import com.infopoint.ui.activity.intro.IntroActivity;

/** Main Entry used to show the Splash Screen and  subsequently move to {@link MainActivity} if logged, {@link IntroActivity} otherwise */
public class App extends AppCompatActivity {
    private final static String _TAG = "[App] ";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        super.onCreate(savedInstanceState);
        Log.d(_TAG, "Starting application...");
        setContentView(R.layout.app_splash_screen);

        findViewById(R.id.splashscreen_logo).setAnimation(AnimationUtils.loadAnimation(this, R.anim.top_animation));
        findViewById(R.id.splashscreen_title_text).setAnimation(AnimationUtils.loadAnimation(this, R.anim.bottom_animation));
        findViewById(R.id.splashscreen_body_text).setAnimation(AnimationUtils.loadAnimation(this, R.anim.bottom_animation));

        new Handler().postDelayed(() -> {
            Log.d(_TAG, "Finished splashscreen...");

            // If this is not the first run (we are sure that's the user is logged) move the ui to the Homepage
            // Otherwise show the Intro
            if (!StorageManager.with(this).contains(Constants.FIRST_RUN)) {
                startActivity(new Intent(App.this, IntroActivity.class));
                finishAffinity();
            }  else {
                startActivity(new Intent(App.this, MainActivity.class));
                finishAffinity();
            }
        }, 2000);
    }
}