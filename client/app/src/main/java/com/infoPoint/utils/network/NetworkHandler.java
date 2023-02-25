/*
 * Scritto da Valentino Bocchetti il 25/2/2023 alle ore 14:41
 *
 * Copyright © 2023 InfoPoint
*/

package com.infoPoint.utils.network;

import com.infoPoint.model.ArtWork;
import com.infoPoint.model.Client;

import java.util.List;

public class NetworkHandler {
    private static final String _TAG = "[NetworkHandler] ";
    public boolean networkAvailable(){
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