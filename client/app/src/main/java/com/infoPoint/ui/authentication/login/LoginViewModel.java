/*
 * Scritto da Valentino Bocchetti il 27/2/2023 alle ore 14:15
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.ui.authentication.login;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

import com.infoPoint.core.builders.CustomMutableLiveData;
import com.infoPoint.model.Client;

public class LoginViewModel extends ViewModel {
    private static final String _TAG = "[LoginViewModel] ";

    CustomMutableLiveData<Client> client = new CustomMutableLiveData<>();

    public LiveData<Client> getClientState(){
        return client;
    }

}