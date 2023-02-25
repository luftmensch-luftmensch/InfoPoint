/*
 * Scritto da Valentino Bocchetti il 25/2/2023 alle ore 14:42
 *
 * Copyright © 2023 InfoPoint
*/

package com.infoPoint.utils.constants;

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
}