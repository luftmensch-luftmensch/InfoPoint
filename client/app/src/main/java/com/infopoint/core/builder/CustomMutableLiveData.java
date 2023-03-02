/*
 * Scritto da Valentino Bocchetti il 2/3/2023 alle ore 11:55
 *
 * Copyright © 2023 InfoPoint
 */

package com.infopoint.core.builder;

import androidx.databinding.BaseObservable;
import androidx.databinding.Observable;
import androidx.lifecycle.MutableLiveData;

public class CustomMutableLiveData<T extends BaseObservable> extends MutableLiveData<T> {

    @Override
    public void setValue(T value) {
        super.setValue(value);
        //listen to property changes
        value.addOnPropertyChangedCallback(callback);
    }

    Observable.OnPropertyChangedCallback callback = new Observable.OnPropertyChangedCallback() {
        @Override
        public void onPropertyChanged(Observable sender, int propertyId) {
            //Trigger LiveData observer on change of any property in object
            setValue(getValue());
        }
    };
}
