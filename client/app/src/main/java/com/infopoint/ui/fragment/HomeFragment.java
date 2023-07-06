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


import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.facebook.shimmer.ShimmerFrameLayout;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.core.networking.NetworkManager;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.model.ArtWork;
import com.infopoint.ui.adapters.ArtWorkAdapter;

import java.util.ArrayList;
import java.util.List;
import java.util.WeakHashMap;

import es.dmoral.toasty.Toasty;

/** Home of the InfoPoint application (where all the artworks are displayed) */
public class HomeFragment extends Fragment {
    private final static String _TAG = "[HomeFragment] ";

    private List<ArtWork> artWorks;

    private ShimmerFrameLayout shimmer;
    private ArtWorkAdapter adapter;
    private RecyclerView rv;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.home_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);
        shimmer = view.findViewById(R.id.home_fragment_shimmer_container);
        shimmer.startShimmer();

        rv = view.findViewById(R.id.recycler_view_home);
        retrieveArtWorks("u", "p", "token");
        // retrieveArtWorks(
        //         StorageManager.with(requireContext()).read(Constants.USERNAME, ""),
        //         StorageManager.with(requireContext()).read(Constants.PASSWORD, ""),
        //         StorageManager.with(requireContext()).read(Constants.TOKEN, "")
        // );
    }

    private void retrieveArtWorks(String username, String password, String token) {
        Toasty.info(requireContext(), "Recupero delle opere in corso...", Toasty.LENGTH_LONG, true).show();
        Thread task = new Thread(() -> {
            artWorks = NetworkManager.retrieveArtwork(username, password, token);
            if (artWorks.size() == 0) {
                Log.d(_TAG, "Failed to retrieve artworks");
                requireActivity().runOnUiThread(() ->
                        Toasty.info(requireContext(), "Attenzione! Non sono state ritrovate opere! Controlla più tardi",
                                Toast.LENGTH_LONG, true).show());
            } else {
                requireActivity().runOnUiThread(this::loadView);
            }
        });
        task.setPriority(10);
        task.start();
    }

    private void loadView() {
        Log.d(_TAG, "Loading view...");
        shimmer.stopShimmer();
        shimmer.setVisibility(View.GONE);
        RecyclerView.LayoutManager manager = new LinearLayoutManager(getContext());
        rv.setLayoutManager(manager);

        adapter = new ArtWorkAdapter(artWorks, requireActivity());
        rv.setAdapter(adapter);
    }

    private void getSelectedItem(List<ArtWork> items) {
    }
}