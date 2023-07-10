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
 *   First written in 14/6/2023 at 20:52
 *
*/

package com.infopoint.ui.fragment;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.widget.SearchView;
import androidx.fragment.app.Fragment;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.appbar.MaterialToolbar;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.model.ArtWork;
import com.infopoint.model.properties.ArtworkUtil;
import com.infopoint.ui.adapters.ArtWorkAdapter;
import com.infopoint.ui.adapters.ItemSelector;

import java.util.ArrayList;
import java.util.List;

import es.dmoral.toasty.Toasty;

/** Fragment used to perform search operation about a specific {@link com.infopoint.model.ArtWork ArtWork} */
public class SearchFragment extends Fragment {
    private final static String _TAG = "[SearchFragment] ";

    private ArtWorkAdapter adapter;

    private List<ArtWork> itemsRetrieved;

    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
    }

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.search_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);

        itemsRetrieved = ArtworkUtil.retrieveArtWorks(requireContext());

        MaterialToolbar toolbar = view.findViewById(R.id.top_app_bar_search);
        toolbar.setOnMenuItemClickListener(item -> {
            Log.d(_TAG, "Item: " + item);
            return false;
        });


        SearchView searchView = view.findViewById(R.id.search_fragment_search_view);
        searchView.clearFocus();
        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) { return false; }
            @Override
            public boolean onQueryTextChange(String text) {
                filter(text);
                return false;
            }
        });

        RecyclerView rv = view.findViewById(R.id.recycler_view_search);
        adapter = new ArtWorkAdapter(itemsRetrieved);
        rv.setHasFixedSize(true);
        rv.setLayoutManager(new LinearLayoutManager(getContext()));
        rv.setAdapter(adapter);

        // Add a way to show the single item
        rv.addOnItemTouchListener(
                new ItemSelector(requireContext(), rv, new ItemSelector.OnItemClickListener() {
                    @Override
                    public void onItemClick(View view, int position) {
                        Log.d(_TAG, "Artwork selected: " + itemsRetrieved.get(position).getName());
                        moveToSingleItemView(itemsRetrieved.get(position));
                    }

                    @Override
                    public void onLongItemClick(View view, int position) {
                        Toasty.info(requireContext(), "Per visualizzare le informazioni sull'opera " +
                                        itemsRetrieved.get(position).getName() +
                                        " clicca senza tenere premuto",
                                Toast.LENGTH_SHORT, true).show();

                    }
                })
        );

    }


    private void filter(String s) {
        List<ArtWork> filtered = new ArrayList<>();
        for (ArtWork a : itemsRetrieved) {
            if (a.getName().toLowerCase().contains(s.toLowerCase()))
                filtered.add(a);
            Log.d(_TAG, "NAME: " + a.getName());
        }

        if (filtered.isEmpty()) {
            Toasty.info(requireContext(), "La tua ricerca non ha prodotto risultati!\nProva con altre parole chiave",
                    Toast.LENGTH_SHORT, true).show();
        } else {
            adapter.useFilter(filtered);
        }
    }

    private void moveToSingleItemView(ArtWork artWork) {
        Bundle bundle = new Bundle();
        bundle.putString(Constants.ARTWORK_ITEM_NAME, artWork.getName());
        bundle.putString(Constants.ARTWORK_ITEM_AUTHOR, artWork.getAuthor());
        bundle.putString(Constants.ARTWORK_ITEM_DATE, artWork.getDateOfProduction());
        bundle.putString(Constants.ARTWORK_ITEM_DESCRIPTION, artWork.getDescription());

        NavController navigator = Navigation.findNavController(requireActivity(), R.id.nav_host_fragment);
        navigator.navigate(R.id.nav_art_work_item, bundle, null);
    }

    @Override
    public void onPause() { super.onPause(); }

    @Override
    public void onResume() { super.onResume(); }

}