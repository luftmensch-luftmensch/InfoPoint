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

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.model.ArtWork;

import java.util.List;

/** Utility class used to perform operation on artwork (retrieve, load, ...) */
public class ArtworkUtil {
    /**
     * Helper method used to retrieve or load the ArtWorks
     * If the artwork are already retrieved load from Shared Preferences
     * Otherwise retrieve them from the network
    */
    public static void loadOrRetrieveArtWorks(Context context) {
        if (StorageManager.with(context).contains(Constants.ARTWORKS_RETRIEVED)) {
            String key = StorageManager.with(context).read(Constants.ARTWORKS_LIST, "");
            Gson gson = new GsonBuilder().create();
            ArtWork[] artworks = gson.fromJson(key, ArtWork[].class);
        } else {
            // retrieveArtwork();
        }
    }

    /** Helper method used to save the retrieved artworks from the Shared Preferences */
    public static void saveArtworks(Context context, List<ArtWork> artworks) {
        Gson gson = new GsonBuilder().create();
        String value = gson.toJson(artworks);
        StorageManager.with(context).write(Constants.ARTWORKS_LIST, value);
    }
}