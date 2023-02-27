/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:30
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.network;

import android.content.Context;
import android.net.ConnectivityManager;

import com.infoPoint.model.ArtWork;
import com.infoPoint.model.Client;

import java.util.List;

public class NetworkHandler {
    private static final String _TAG = "[NetworkHandler] ";

    public boolean networkAvailable(Context context){
        ConnectivityManager connectivityManager = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
        if (connectivityManager.getActiveNetworkInfo() != null) {
            return connectivityManager.getActiveNetworkInfo().isConnected();
        }
        return false;
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