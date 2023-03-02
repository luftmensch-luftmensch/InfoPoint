/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 12:7
 *
 * Copyright © 2023 InfoPoint
 */

package com.infopoint.ui.intro;

import android.os.Bundle;

import androidx.annotation.Nullable;


import com.github.appintro.AppIntro2;
import com.github.appintro.AppIntroFragment;
import com.github.appintro.AppIntroPageTransformerType;
import com.infopoint.R;

public class InfoPointIntro extends AppIntro2 {
    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // TODO: Update Drawable icons
        addSlide(AppIntroFragment.createInstance("Welcome!",
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

        // Fade Transition
        setTransformer(AppIntroPageTransformerType.Fade.INSTANCE);

        // Show/hide status bar
        showStatusBar(true);

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

    }
}