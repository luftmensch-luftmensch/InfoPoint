/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 12:0
 *
 * Copyright © 2023 InfoPoint
*/

package com.infopoint.model;

import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

import com.infopoint.BR;

public class ArtWork extends BaseObservable  {
    private String title;
    private String comment;

    /*
        Data binding generates a class named BR (BindingResources) in the module package which contains the IDs of the resources used for data binding.
        The Bindable annotation generates an entry in the BR class file during compilation. If the base class for data classes cannot be changed,
        the Observable interface can be implemented using a PropertyChangeRegistry object to register and notify listeners efficiently.
    */

    @Bindable
    public String getTitle() { return title; }
    @Bindable
    public String getComment() { return comment; }

    public void setTitle(String title) {
        this.title = title;
        notifyPropertyChanged(BR.title);
    }

    public void setComment(String comment) {
        this.comment = comment;
        notifyPropertyChanged(BR.comment);
    }
}