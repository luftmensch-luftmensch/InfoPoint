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

/** Utility class used to define constants around the Application */
public class Constants {
    public static final String SERVER_ADDR = "192.168.1.171";
    public static final int SERVER_PORT = 9090;

    public static final int SERVER_TIMEOUT = 2000;

    public static final String BLOCK_DELIMITER = "<>";
    public static final String SINGLE_DELIMITER = ",";

    public static final int PASSWORD_LENGTH = 8;

    public static String IS_LOGGED = "IS_LOGGED";
    public static String INTRO_VIEWED = "INTRO_VIEWED";

    public static String ARTWORKS_RETRIEVED = "ARTWORKS_RETRIEVED";
    public static String ARTWORKS_LIST = "ARTWORKS_LIST";


    public static String USERNAME = "USERNAME";
    public static String PASSWORD = "PASSWORD";
}