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


import android.content.Context;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.infopoint.R;
import com.infopoint.model.ArtWork;

import java.util.List;

/** Helper Adapter Class used for the {@link com.infopoint.ui.fragment.HomeFragment HomeFragment} & {@link com.infopoint.ui.fragment.ProfileFragment ProfileFragment} */
public class ArtWorkAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
    private final List<ArtWork> items;
    private final Context ctx;

    public ArtWorkAdapter(List<ArtWork> items, Context context) {
        this.items = items;
        this.ctx = context;
    }


    private class ViewHolder extends RecyclerView.ViewHolder {
        private ImageView artWorkImageView;
        private TextView nameTextView, authorTextView, descriptionTextView, dateOfProductionTextView;
        public ViewHolder(@NonNull View v) {
            super(v);
            nameTextView = v.findViewById(R.id.art_work_card_name);
            authorTextView = v.findViewById(R.id.art_work_card_author);
            dateOfProductionTextView = v.findViewById(R.id.art_work_card_date);
        }
        void bind(ArtWork art) {
            nameTextView.setText(art.getName());
            authorTextView.setText(art.getAuthor());
            dateOfProductionTextView.setText("TEST");
            // TODO: Add others
        }
    }


    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new ViewHolder(LayoutInflater.from(parent.getContext()).inflate(R.layout.art_work_card, parent, false));
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, int position) {
        Log.d("T", "POS: " + position);
        ArtWork item = items.get(position);
        ((ViewHolder) holder).bind(item);
    }

    @Override
    public int getItemCount() { return items.size(); }
}