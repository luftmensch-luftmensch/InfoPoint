/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 12:0
 *
 * Copyright © 2023 InfoPoint
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