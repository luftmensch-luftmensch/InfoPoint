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

import android.util.Log;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * Utility class for managing Dates
 * @author valentino
*/
public class DateUtil {
    private static final String _TAG = "[DateUtil] ";

    private static final DateTimeFormatter dateFormatter = DateTimeFormatter.ofPattern("dd-MM-yyyy");
    private static final DateTimeFormatter timeFormatter = DateTimeFormatter.ofPattern("HH:mm:ss");

    LocalDateTime parseDate(String s){
        try {
            LocalDateTime.parse(s);
        } catch (Exception e) {
            Log.d(_TAG, "Failed to parse [" + s + "]. Cause [" + e.getLocalizedMessage() + "]");
        }
        return LocalDateTime.parse(s, dateFormatter);
    }

    LocalDateTime parseTime(String s){
        try {
            LocalDateTime.parse(s);
        } catch (Exception e) {
            Log.d(_TAG, "Failed to parse [" + s + "]. Cause [" + e.getLocalizedMessage() + "]");
        }
        return LocalDateTime.parse(s, timeFormatter);
    }
}
