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
 *   @author Valentino Bocchetti
 *   First written in 13/6/2023 at 21:36
 *
 */

package com.infopoint.core.config;

public class Constants {
    public static final String SERVER_ADDR = "";
    public static final int SERVER_PORT = 0;

    // Network Related
    public static final String NETWORK_REQUEST = "Network Request Status";
    public static final String NETWORK_ERROR = "Network Error";
    public static final String SERVER_ERROR = "Server unreachable";

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
    public static String MIME_TYPE_SKETCH = "image/png";
    public static String MIME_TYPE_FILES = "file/*";

    public static String IS_LOGGED = "IS_LOGGED";
    public static String INTRO_VIEWED = "INTRO_VIEWED";
}