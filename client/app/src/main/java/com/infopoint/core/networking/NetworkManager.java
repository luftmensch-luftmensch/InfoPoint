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
import com.infopoint.core.preferences.StorageManager;
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

    /** Helper method used to check Network Capabilities needed for the app to work correctly */
    public static Boolean checkConnection(Context context) {
        ConnectivityManager manager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        Network network = manager.getActiveNetwork();
        if (network == null) return false;
        NetworkCapabilities capabilities = manager.getNetworkCapabilities(network);
        return capabilities != null && (capabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI) || capabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR));
    }

    /** Retrieve the artworks from the server */
    public static ArrayList<ArtWork> retrieveArtwork(String username, String password, String token) {
        ArrayList<ArtWork> result = new ArrayList<>();
        try {
            InetAddress address = InetAddress.getByName(Constants.SERVER_ADDR);
            if(address.isReachable(2000)){ // Check if the server is reachable
                Socket s = new Socket(address, Constants.SERVER_PORT);
                // Read the response received from the server
                BufferedReader reader = new BufferedReader(new InputStreamReader(s.getInputStream()));

                // Wait until the server inform us that is ready to perform communication
                while(s.getInputStream().available() < 1) {
                    Log.d(_TAG, "Waiting...");
                }

                String serverReady = reader.readLine();
                Log.d(_TAG, "Message: " + serverReady);

                // Create the writer in order to write to the socket just opened
                PrintWriter out = new PrintWriter(new BufferedWriter( new OutputStreamWriter(s.getOutputStream())), true);

                out.println(String.format("<>REQUEST:RETRIEVE<>USERNAME:%s<>PASSWORD:%s<>TOKEN:%s\n", username, password, token));
                out.println("\n");

                String buffer;
                while (true) {
                    buffer = reader.readLine();
                    buffer = buffer.replace("\u0000", "");
                    if (buffer.isEmpty() || buffer.equals("<>RESPONSE:SUCCESS<>")) {
                        Log.d(_TAG, "Finished artwork collection");
                        break;
                    }

                    if (buffer.equals("<>RESPONSE:Invalid token<>") || buffer.equals("<>RESPONSE:FAILED<>")) {
                        Log.d(_TAG, "An error as occurred while retrieving");
                        return null;
                    }

                    // Log.d(_TAG, "Buffer: " + buffer);
                    String[] fields = buffer.split(Constants.OUTER_DELIMITER);
                    // Log.d(_TAG, "Fields: " + Arrays.toString(fields));
                    Log.d(_TAG, "Name: " + fields[1].replace("NAME:", "") +
                            " Author: " + fields[2].replace("AUTHOR:", "") +
                            " Date: " + fields[3].replace("DATE:", "") +
                            " Description" + fields[4].replace("DESCRIPTION:", ""));

                    result.add(new ArtWork(fields[1].replace("NAME:", ""),
                            fields[2].replace("AUTHOR:", ""),
                            fields[3].replace("DATE:", ""),
                            fields[4].replace("DESCRIPTION:", "")));
                }

                Log.d(_TAG, "Closing socket");
                s.close();
            }
        } catch (IOException e){
            Log.d(_TAG, "Cause: " + e.getLocalizedMessage());
        }
        return result;
    }

    public static boolean user_operation(String requestType, String username, String password, String token, Context ctx) {
        try {
            InetAddress address = InetAddress.getByName(Constants.SERVER_ADDR);
            if (address.isReachable(Constants.SERVER_TIMEOUT)) { // Check if the server is reachable
                Socket s = new Socket(address, Constants.SERVER_PORT);

                // Reader of the socket
                BufferedReader reader = new BufferedReader(new InputStreamReader(s.getInputStream()));

                // Wait until the server inform us that is ready to perform communication
                while(s.getInputStream().available() < 1) {
                    Log.d(_TAG, "Waiting...");
                }

                String msg = reader.readLine();
                Log.d(_TAG, "Message: " + msg);

                // Create the writer in order to write to the socket just opened
                PrintWriter out = new PrintWriter(new BufferedWriter( new OutputStreamWriter(s.getOutputStream())), true);

                // Control switch to select the actual request to perform
                String actualRequestType = switch (requestType) {
                    case "LOGIN" -> "LOGIN";
                    case "REGISTRATION" -> "REGISTRATION";
                    case "DELETE" -> "DELETE";
                    default -> "";
                };

                out.println(String.format("<>REQUEST:%s<>USERNAME:%s<>PASSWORD:%s<>TOKEN:%s\n", actualRequestType, username, password, token));
                out.println("\n");

                String buffer = reader.readLine();
                buffer = buffer.replace("\u0000", "");
                String[] fields = buffer.split(Constants.OUTER_DELIMITER);
                Log.d(_TAG, "[RESPONSE]: " + fields[1].replace("RESPONSE:", ""));

                if (fields[1].replace("RESPONSE:", "").equals("SUCCESS")) {

                    // Save crendials and then move to HomePage
                    StorageManager.with(ctx).write(Constants.USERNAME, username);
                    StorageManager.with(ctx).write(Constants.PASSWORD, password);
                    StorageManager.with(ctx).write(Constants.TOKEN, token);
                } else {
                    return false;
                }

                if (actualRequestType.equals("REGISTRATION")) {
                    buffer = reader.readLine();
                    buffer = buffer.replace("\u0000", "");
                    fields = buffer.split(Constants.OUTER_DELIMITER);
                    // Log.d(_TAG, "[TOKEN]: " + fields[1].replace("TOKEN:", ""));

                    if (!fields[1].replace("TOKEN:", "").isEmpty()){
                        // Save crendials and then move to HomePage
                        StorageManager.with(ctx).write(Constants.TOKEN, fields[1].replace("TOKEN:", ""));
                    } else {
                        return false;
                    }
                }

                Log.d(_TAG, "Closing socket");
                s.close();
                return true;
            }
        } catch (IOException e){
            Log.d(_TAG, "Cause: " + e.getLocalizedMessage());
        }
        return false;
    }
}