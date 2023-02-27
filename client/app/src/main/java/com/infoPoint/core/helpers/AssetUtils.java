/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:29
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.helpers;

import android.content.res.AssetManager;

import java.io.IOException;
import java.util.Arrays;

public class AssetUtils {
    // hides public constructor
    private AssetUtils() { }

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