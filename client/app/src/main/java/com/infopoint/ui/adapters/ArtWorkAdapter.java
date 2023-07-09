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
 *   First written in 20/6/2023 at 17:25
 *
*/

package com.infopoint.ui.adapters;


import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.cardview.widget.CardView;
import androidx.recyclerview.widget.RecyclerView;
import com.bumptech.glide.Glide;
import com.infopoint.R;
import com.infopoint.model.ArtWork;

import java.util.List;

/** Helper Adapter Class used for the {@link com.infopoint.ui.fragment.HomeFragment HomeFragment} */
public class ArtWorkAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
    private List<ArtWork> items;

    public ArtWorkAdapter(List<ArtWork> items) { this.items = items; }

    public void useFilter(List<ArtWork> filtered) {
        this.items = filtered;
        notifyDataSetChanged();
    }


    private static class ViewHolder extends RecyclerView.ViewHolder {
        private final ImageView image;
        private final TextView name, author, date;

        private final CardView card;

        public ViewHolder(@NonNull View v) {
            super(v);
            image = v.findViewById(R.id.art_work_card_image);
            name = v.findViewById(R.id.art_work_card_name);
            author = v.findViewById(R.id.art_work_card_author);
            date = v.findViewById(R.id.art_work_card_date);
            card = v.findViewById(R.id.art_work_card);
        }
        void bind(ArtWork art) {
            int imageId = switch (art.getName()) {
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

            Glide.with(image.getContext()).load(imageId).centerCrop().into(image);
            name.setText(art.getName());
            author.setText(art.getAuthor());
            date.setText((art.getDateOfProduction().length() > 4 ? "Data di produzione: " : "Periodo di produzione: ") + art.getDateOfProduction());
            card.startAnimation(AnimationUtils.loadAnimation(card.getContext(), R.anim.scrolling_animation));
        }
    }


    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new ViewHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.art_work_card, parent, false));
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        ArtWork item = items.get(position);
        ((ViewHolder) holder).bind(item);
    }

    @Override
    public int getItemCount() { return items.size(); }
}