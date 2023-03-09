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
 * First written in 2/3/2023 at 12:00
*/

package com.infopoint.core.network;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.util.Log;
import java.util.List;

import com.infopoint.model.ArtWork;
import com.infopoint.model.Client;

/**
 * <strong>Manager</strong> for <strong>Network</strong>  operations
 * @author valentino
 */
public class NetworkManager {

    private static final String _TAG = "[NetworkHandler] ";

    public Boolean isNetworkAvailable(Context context){
        Log.d(_TAG, "Checking if network is available");
        ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        Network network = connectivityManager.getActiveNetwork();
        if (network == null) return false;
        NetworkCapabilities networkCapabilities = connectivityManager.getNetworkCapabilities(network);
        return networkCapabilities != null && (networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) || networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR));
    }
    public boolean isServerRunning(){ return false; }

    public boolean register(Client client){
        return false;
    }
    public boolean login(Client client){
        return false;
    }

    public List<ArtWork> retrieveArtwork(){ return  null; }
}