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
 *   First written in 13/6/2023 at 21:35
 *
 */

package com.infopoint.core.networking;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.util.Log;

import com.infopoint.core.config.Constants;
import com.infopoint.model.ArtWork;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.ArrayList;

/** Utility class used to perform Network operations */
public class NetworkManager {
    private static final String _TAG = "[NetworkManager] ";

    public static Boolean checkConnection(Context context) {
        ConnectivityManager manager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        Network network = manager.getActiveNetwork();
        if (network == null) return false;
        NetworkCapabilities capabilities = manager.getNetworkCapabilities(network);
        return capabilities != null && (capabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) || capabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR));
    }

    public static ArrayList<ArtWork> retrieveArtwork(String fmt) {
        ArrayList<ArtWork> artworks = new ArrayList<>();
        try {
            InetAddress address = InetAddress.getByName(Constants.SERVER_ADDR);
            if(address.isReachable(2000)){ // Check if the server is reachable
                Socket s = new Socket(address, Constants.SERVER_PORT);
                // Create the writer in order to write to the socket just opened
                PrintWriter out = new PrintWriter(new BufferedWriter( new OutputStreamWriter(s.getOutputStream())), true);
                // Write the request
                out.println(fmt);

                // Read the response received from the server
                BufferedReader reader = new BufferedReader(new InputStreamReader(s.getInputStream()));

                // TODO: Handle read

                Log.d(_TAG, "Closing socket");
                s.close();
            }
        }catch (IOException e){
            Log.d(_TAG, e.getLocalizedMessage());
        }
        return artworks;
    }

    public static boolean login(String username, String password) {

        return false;
    }
}