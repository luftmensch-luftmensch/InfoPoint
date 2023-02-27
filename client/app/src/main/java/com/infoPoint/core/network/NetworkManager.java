/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:30
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.network;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.util.Log;

import com.infoPoint.model.ArtWork;
import com.infoPoint.model.Client;

import java.util.List;

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