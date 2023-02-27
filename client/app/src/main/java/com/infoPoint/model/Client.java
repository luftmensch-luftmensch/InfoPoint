/*
 * Scritto da Valentino Bocchetti il 25/2/2023 alle ore 14:42
 *
 * Copyright © 2023 InfoPoint
*/

package com.infoPoint.model;

import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

import com.infoPoint.BR;

public class Client extends BaseObservable {
    private String username;
    private String password;
    private ClientType type;

    /*
        Data binding generates a class named BR (BindingResources) in the module package which contains the IDs of the resources used for data binding.
        The Bindable annotation generates an entry in the BR class file during compilation. If the base class for data classes cannot be changed,
        the Observable interface can be implemented using a PropertyChangeRegistry object to register and notify listeners efficiently.
    */

    @Bindable
    public String getUsername() { return username; }
    @Bindable
    public String getPassword() { return password; }
    @Bindable
    public ClientType getType() { return type; }

    public void setUsername(String username) {
        this.username = username;
        notifyPropertyChanged(BR.username);
    }

    public void setPassword(String password) {
        this.password = password;
        notifyPropertyChanged(BR.password);
    }

    public void setType(ClientType type) {
        this.type = type;
        notifyPropertyChanged(BR.type);
    }

    @Override
    public String toString() {
        return "Client{" +
                "username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", type=" + type +
                '}';
    }
}