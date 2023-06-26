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
 *   @author Valentino Bocchetti
 *   First written in 14/6/2023 at 20:50
 *
*/

package com.infopoint.ui.fragment;


import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.model.ArtWork;

import java.util.List;

public class HomeFragment extends Fragment {
    private final static String _TAG = "[HomeFragment] ";

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.home_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);
    }

}