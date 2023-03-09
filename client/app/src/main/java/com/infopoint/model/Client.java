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
 * First written in 2/3/2023 at 12:00
*/

package com.infopoint.model;

import androidx.annotation.NonNull;
import androidx.databinding.BaseObservable;
import androidx.databinding.Bindable;

import com.infopoint.BR;

/**
 * Model class for <strong>client</strong>
 * @author valentino
*/
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