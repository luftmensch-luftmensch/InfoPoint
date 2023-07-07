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
 *   First written in 26/6/2023 at 16:27
 *
 */

package com.infopoint.model.properties;

import static com.infopoint.core.networking.NetworkManager.retrieveArtwork;

import android.content.Context;
import android.util.Log;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.model.ArtWork;

import java.lang.reflect.Array;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/** Utility class used to perform operation on artwork (retrieve, load, ...) */
public class ArtworkUtil {
    private final static String _TAG = "[ArtworkUtil] ";

    /** Helper method used to retrieve the ArtWorks from Shared Preferences */
    public static ArrayList<ArtWork> retrieveArtWorks(Context ctx) {
        Log.d(_TAG, "Retrieving artworks...");
        String key = StorageManager.with(ctx).read(Constants.ARTWORKS_LIST, "");
        Gson gson = new GsonBuilder().create();
        return gson.fromJson(key, new TypeToken<ArrayList<ArtWork>>() {}.getType());
    }

    /** Helper method used to save the retrieved artworks from the Shared Preferences */
    public static void saveArtworks(Context context, List<ArtWork> artworks) {
        Log.d(_TAG, "Saving artworks... " + artworks.get(1).getDateOfProduction());
        Gson gson = new GsonBuilder().create();
        String value = gson.toJson(artworks);
        StorageManager.with(context).write(Constants.ARTWORKS_LIST, value);
        StorageManager.with(context).write(Constants.ARTWORKS_RETRIEVED, true);
    }
}