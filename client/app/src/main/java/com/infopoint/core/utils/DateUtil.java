/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:57
 *
 * Copyright © 2023 InfoPoint
 */

package com.infopoint.core.utils;

import android.util.Log;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

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
