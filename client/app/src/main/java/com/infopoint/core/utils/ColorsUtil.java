/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:57
 *
 * Copyright © 2023 InfoPoint
*/

package com.infopoint.core.utils;

import android.graphics.Color;

public class ColorsUtil {

    private static final String _TAG = "[ColorsUtil] ";

    private ColorsUtil() { }

    private static final int COLOR_DARK = 0;
    private static final int COLOR_LIGHT = 1;
    private static final double CONTRAST_THRESHOLD = 100;

    public static double calculateColorLuminance(int color) {
        return 0.2126 * Color.red(color) + 0.7152 * Color.green(color) + 0.0722 * Color.blue(color);
    }


    public static int getContrastedColor(int color) {
        double luminance = calculateColorLuminance(color);
        return luminance > CONTRAST_THRESHOLD ? COLOR_DARK : COLOR_LIGHT;
    }
}