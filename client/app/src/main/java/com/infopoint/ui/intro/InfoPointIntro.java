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
 * First written in 2/3/2023 at 12:07
*/

package com.infopoint.ui.intro;

import android.Manifest;
import android.os.Bundle;

import androidx.annotation.Nullable;


import com.github.appintro.AppIntro2;
import com.github.appintro.AppIntroFragment;
import com.github.appintro.AppIntroPageTransformerType;
import com.infopoint.R;

import dagger.hilt.android.AndroidEntryPoint;

/**
 * Presentation ui to describe the app to the final client
 * @author valentino
*/
@AndroidEntryPoint
public class InfoPointIntro extends AppIntro2 {

    private static final String _TAG = "[InfoPointIntro] ";
    private static final String[] permissions = new String[]{Manifest.permission.CAMERA, Manifest.permission.USE_BIOMETRIC};
    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // TODO: Update Drawable icons
        addSlide(AppIntroFragment.createInstance(
                "Benvenuto!",
                "This is a demo example in java of AppIntro library, with a custom background on each slide!",
                R.drawable.ic_avatar_icon
        ));

        addSlide(AppIntroFragment.createInstance(
                "Clean App Intros",
                "This library offers developers the ability to add clean app intros at the start of their apps.",
                R.drawable.ic_avatar_icon
        ));

        addSlide(AppIntroFragment.createInstance(
                "Simple, yet Customizable",
                "The library offers a lot of customization, while keeping it simple for those that like simple.",
                R.drawable.ic_avatar_icon
        ));

        addSlide(AppIntroFragment.createInstance(
                "Explore",
                "Feel free to explore the rest of the library demo!",
                R.drawable.ic_avatar_icon
        ));

        askForPermissions(
                permissions,
                3,
                true
        );

        // Fade Transition
        setTransformer(AppIntroPageTransformerType.Fade.INSTANCE);

        // Show/hide status bar
        showStatusBar(false);

        //Speed up or down scrolling
        setScrollDurationFactor(2);

        //Enable the color "fade" animation between two slides (make sure the slide implements SlideBackgroundColorHolder)
        setColorTransitionsEnabled(true);

        //Prevent the back button from exiting the slides
        setSystemBackButtonLocked(true);

        //Activate wizard mode (Some aesthetic changes)
        setWizardMode(true);

        //Enable immersive mode (no status and nav bar)
        setImmersiveMode();

        //Enable/disable page indicators
        setIndicatorEnabled(true);

        //Dhow/hide ALL buttons
        setButtonsEnabled(true);

        // Enable Vibration
        setVibrate(false);

        // Ask for permission

    }
}