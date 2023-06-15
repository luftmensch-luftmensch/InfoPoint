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
 *   First written in 15/6/2023 at 14:55
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

import androidx.activity.OnBackPressedCallback;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.infopoint.R;
import com.infopoint.ui.activity.MainActivity;

public class AboutUsFragment extends Fragment {
    private final static String _TAG = "[AboutUsFragment] ";

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        requireActivity().getOnBackPressedDispatcher().addCallback(new OnBackPressedCallback(true) {
            @Override
            public void handleOnBackPressed() {
                Log.d(_TAG, "Moving to home...");
                MainActivity main = (MainActivity) requireActivity();
                main.navController.navigate(R.id.action_nav_about_us_to_nav_home);
            }
        });
        return inflater.inflate(R.layout.about_us_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);
        view.findViewById(R.id.about_us_team_card_author_1_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/luftmensch-luftmensch/"))));
        view.findViewById(R.id.about_us_team_card_author_2_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/saltyDario/"))));
        view.findViewById(R.id.about_us_team_card_author_3_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/lbrando/"))));

        view.findViewById(R.id.about_us_contact).setOnClickListener(v -> {
            Intent intent = new Intent(Intent.ACTION_SENDTO);
            intent.setData(Uri.parse("mailto:"));
            intent.putExtra(Intent.EXTRA_EMAIL, "infopoint@info.com");
            requireActivity().startActivity(Intent.createChooser(intent, "Seleziona client di posta elettronica"));
        });
    }
}