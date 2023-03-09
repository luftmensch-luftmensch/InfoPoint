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
 * First written in 2/3/2023 at 11:57
*/

package com.infopoint.core.utils;

import android.graphics.Color;


/**
 * @author valentino
 */
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