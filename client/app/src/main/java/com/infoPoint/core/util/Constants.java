/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:30
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.util;

public class Constants {
    // Server Related
    public static final String SERVER_ADDR = "";
    public static final int SERVER_PORT = 0;

    // Network Related
    public static final String NETWORK_REQUEST = "Network Request Status";
    public static final String NETWORK_ERROR = "Network Error";
    public static final String SERVER_ERROR = "Server unreachable";

    // Storage Related
    public static final String DATASTORE_STATE = "Datastore Status";
    public static final String STORAGE = "Storage request";

    // Login/Registration Related
    public static final String LOGIN_STATE = "Login process";
    public static final String REGISTRATION_STATE = "Sign Up process";
    public static final String PASSWORD_RESET = "Password reset process";

    // Model Related
    public static final String USER_MODEL = "User request status";
    public static final String ARTWORK_MODEL = "Artwork request status";

    // Form validation
    public static final int PASSWORD_LENGTH = 8;
    public static final int CODE_LENGTH = 6;

    // Comunication tokens
    public static final String LOGIN = "<LOGIN>";
    public static final String REGISTRATION = "<REGISTRATION>";
    public static final String USERNAME = "<USERNAME>";
    public static final String PASSWORD = "<PASSWORD>";

    // MIME_TYPES
    public static String MIME_TYPE_IMAGE = "image/jpeg";
    public static String MIME_TYPE_AUDIO = "audio/amr";
    public static String MIME_TYPE_VIDEO = "video/mp4";
    public static String MIME_TYPE_SKETCH = "image/png";
    public static String MIME_TYPE_FILES = "file/*";

    public static String MIME_TYPE_IMAGE_EXT = ".jpeg";
    public static String MIME_TYPE_AUDIO_EXT = ".amr";
    public static String MIME_TYPE_VIDEO_EXT = ".mp4";
    public static String MIME_TYPE_SKETCH_EXT = ".png";
    public static String MIME_TYPE_CONTACT_EXT = ".vcf";

    // SHARED_PREFERENCES KEY
    public static String FIRST_RUN = "first_run";
}