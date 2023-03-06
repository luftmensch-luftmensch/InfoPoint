/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 12:0
 *
 * Copyright © 2023 InfoPoint
 */

package com.infopoint.model;

import androidx.annotation.NonNull;
import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

import com.infopoint.BR;

public class Client extends BaseObservable {
    private String username;
    private String password;
    private ClientType type;

    private String email;

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
    public String getEmail() { return email; }

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

    public void setEmail(String email) {
        this.email = email;
        notifyPropertyChanged(BR.email);
    }

    public void setType(ClientType type) {
        this.type = type;
        notifyPropertyChanged(BR.type);
    }

    @NonNull
    @Override
    public String toString() {
        return "Client{" +
                "username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", type=" + type +
                '}';
    }
}