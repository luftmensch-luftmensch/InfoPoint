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

    /** Address of the server */
    public static final String SERVER_ADDR = "192.168.1.203";

    /** Port of the server */
    public static final int SERVER_PORT = 9090;

    /** Timeout for the server */
    public static final int SERVER_TIMEOUT = 2000;

    /** Delimiter used to distinguish blocks */
    public static final String OUTER_DELIMITER = "<>";

    /** Delimiter used to distinguish items iside a block */
    public static final String INNER_DELIMITER = ":";

    public static String FIRST_RUN = "FIRST_RUN";

    /** Key to inform that artworks are loaded into the devices */
    public static String ARTWORKS_RETRIEVED = "ARTWORKS_RETRIEVED";

    /** Access key for the artworks on the devices */
    public static String ARTWORKS_LIST = "ARTWORKS_LIST";

    public static String ARTWORK_ITEM_NAME = "ARTWORK_ITEM_NAME";
    public static String ARTWORK_ITEM_AUTHOR = "ARTWORK_ITEM_AUTHOR";
    public static String ARTWORK_ITEM_DATE = "ARTWORK_ITEM_DATE";
    public static String ARTWORK_ITEM_DESCRIPTION = "ARTWORK_ITEM_DESCRIPTION";

    /** Access key for the user username */
    public static String USERNAME = "USERNAME";

    /** Access key for the user password */
    public static String PASSWORD = "PASSWORD";

    /** Access key for the user token */
    public static String TOKEN = "TOKEN";

    /** Access key for the user profile pic */
    public static String PROFILE_PIC = "PROFILE_PIC";

    /** Access key for the user level */
    public static String LEVEL = "LEVEL";
}