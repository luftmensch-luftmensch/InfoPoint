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
 *   First written in 5/7/2023 at 18:4
 *
 */

package com.infopoint.ui.fragment;


import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.appbar.MaterialToolbar;
import com.google.android.material.imageview.ShapeableImageView;
import com.infopoint.R;

public class ArtWorkFragment extends Fragment {
    private final static String _TAG = "[ArtWorkFragment] ";
    private MaterialToolbar toolbar;
    private ShapeableImageView artWorkImage;

    private TextView titleTextView, descriptionTextView;
    private Button moreActions;


    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.art_work_details, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);

        toolbar = view.findViewById(R.id.top_app_bar_art_work_item);
        toolbar.setNavigationOnClickListener(click -> {
            Log.d(_TAG, "Navigation Icon clicked");

        });

        toolbar.setTitle("HELLO"); // TODO: Update from the current value

        artWorkImage = view.findViewById(R.id.art_work_item_image_view);
        titleTextView = view.findViewById(R.id.art_work_item_title_text_view);
        descriptionTextView = view.findViewById(R.id.art_work_item_description_text_view);

        moreActions = view.findViewById(R.id.art_work_item_button);

        moreActions.setOnClickListener(click -> {
            // TODO: Exec research on click for the current art work
        });
    }
}