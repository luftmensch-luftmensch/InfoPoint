/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:57
 *
 * Copyright © 2023 InfoPoint
 */

package com.infopoint.core.utils;

import android.content.res.AssetManager;

import java.io.IOException;
import java.util.Arrays;
public class AssetUtil {
    private static final String _TAG = "[AssetUtil] ";

    // hides public constructor
    private AssetUtil() { }

    public static boolean exists(String fileName, String path, AssetManager assetManager) throws IOException {
        for (String currentFileName : assetManager.list(path)) {
            if (currentFileName.equals(fileName)) {
                return true;
            }
        }
        return false;
    }

    public static String[] list(String path, AssetManager assetManager) throws IOException {
        String[] files = assetManager.list(path);
        Arrays.sort(files);
        return files;
    }
}
