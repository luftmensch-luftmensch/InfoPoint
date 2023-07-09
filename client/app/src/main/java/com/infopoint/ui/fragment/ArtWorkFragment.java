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


import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.navigation.Navigation;

import com.bumptech.glide.Glide;
import com.google.android.material.appbar.MaterialToolbar;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.model.ArtWork;

public class ArtWorkFragment extends Fragment {
    private final static String _TAG = "[ArtWorkFragment] ";

    private ArtWork item;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.art_work_details, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);

        item = new ArtWork(
                getArguments().getString(Constants.ARTWORK_ITEM_NAME),
                getArguments().getString(Constants.ARTWORK_ITEM_AUTHOR),
                getArguments().getString(Constants.ARTWORK_ITEM_DATE),
                getArguments().getString(Constants.ARTWORK_ITEM_DESCRIPTION)
        );

        MaterialToolbar toolbar = view.findViewById(R.id.top_app_bar_art_work_item);
        toolbar.setTitle(item.getName());
        toolbar.setOnClickListener(click -> Navigation.findNavController(requireActivity(), R.id.nav_host_fragment).navigate(R.id.nav_home, null, null));

        int imageId = switch (item.getName()) {
            case "Amore e Psiche" -> R.drawable.amore_e_psiche;
            case "Cristo Velato" -> R.drawable.cristo_velato;
            case "Il David" -> R.drawable.david;
            case "Gli Amanti" -> R.drawable.gli_amanti;
            case "Il Bacio" -> R.drawable.il_bacio;
            case "La Danza" -> R.drawable.la_danza;
            case "La Giuditta" -> R.drawable.la_giuditta;
            case "La Nascita di Venere" -> R.drawable.nascita_di_venere;
            case "La Notte Stellata" -> R.drawable.notte_stellata;
            case "La persistenza della memoria" -> R.drawable.persistenza_della_memoria;
            case "Apollo e Dafne" -> R.drawable.apollo_e_dafne;
            default -> R.drawable.logo_no_background;
        };

        ImageView image = view.findViewById(R.id.art_work_item_image_view);

        Glide.with(image.getContext()).load(imageId).centerCrop().into(image);

        TextView author = view.findViewById(R.id.art_work_item_author_text_view);
        TextView description = view.findViewById(R.id.art_work_item_description_text_view);
        TextView date = view.findViewById(R.id.art_work_item_date_text_view);

        author.setText(item.getAuthor());
        date.setText(item.getDateOfProduction());
        description.setText(item.getDescription());

        Button moreActions = view.findViewById(R.id.art_work_item_button);

        moreActions.setOnClickListener(click -> requireActivity().startActivity(Intent.createChooser(
                new Intent(Intent.ACTION_VIEW).setData(Uri.parse("https://www.google.com/search?q=" + item.getName())),
                "Ricerca aggiuntiva"
        )));
    }
}