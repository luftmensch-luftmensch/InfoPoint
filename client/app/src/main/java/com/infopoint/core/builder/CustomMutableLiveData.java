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
 * First written in 2/3/2023 at 11:55
*/

package com.infopoint.core.builder;

import androidx.databinding.BaseObservable;
import androidx.databinding.Observable;
import androidx.lifecycle.MutableLiveData;

/**
 * Wrapper for <strong>MutableLiveData</strong>
 * @param <T> This class use Generic
 * @author valentino
 */
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
