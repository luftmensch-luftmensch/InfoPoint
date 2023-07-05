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

import android.accessibilityservice.GestureDescription;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.appbar.MaterialToolbar;
import com.google.android.material.bottomsheet.BottomSheetDialog;
import com.google.android.material.chip.Chip;
import com.google.android.material.dialog.MaterialAlertDialogBuilder;
import com.google.android.material.imageview.ShapeableImageView;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.ui.activity.MainActivity;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

/** Fragment used to show info about the current user logged */
public class ProfileFragment extends Fragment {
    private final static String _TAG = "[ProfileFragment] ";
    private Chip chip;
    private MaterialToolbar toolbar;

    private ActivityResultLauncher<Intent> selectImageLauncher;
    private ShapeableImageView selectImage, profilePic;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.profile_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);
        chip = view.findViewById(R.id.about_us_chip);
        chip.setOnClickListener(click -> showDialog());

        toolbar = view.findViewById(R.id.top_app_bar_profile);

        toolbar.setOnMenuItemClickListener(item -> {
            new MaterialAlertDialogBuilder(requireContext())
                    .setTitle(R.string.confirm_logout)
                    .setMessage(R.string.confirm_logout_body)
                    .setPositiveButton(R.string.confirm_request, (dialogInterface, i) -> {
                        Log.d(_TAG, "Logout request confirmed");
                        StorageManager.with(requireContext()).clear();
                        // TODO: Handle backstack clear
                        MainActivity main = (MainActivity) requireActivity();
                        main.navController.navigate(R.id.nav_logout);

                    })
                    .setNegativeButton(R.string.cancel_request, (dialogInterface, i) -> Log.d(_TAG, "Logout request cancelled"))
                    .show();
            return false;
        });

        profilePic = view.findViewById(R.id.profile_fragment_profile_photo);

        selectImage = view.findViewById(R.id.profile_fragment_change_photo);

        if (StorageManager.with(requireContext()).contains(Constants.PROFILE_PIC))
            profilePic.setImageBitmap(stringToBitmap(StorageManager.with(requireContext()).read(Constants.PROFILE_PIC, Constants.PROFILE_PIC)));

        selectImage.setOnClickListener(click -> {
            Log.d(_TAG, "Change photo");
            selectImageLauncher.launch(Intent.createChooser(
                    new Intent().setType("image/*").setAction(Intent.ACTION_GET_CONTENT),
                    "Seleziona la foto per il profilo"));
        });

        selectImageLauncher = registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {
            if ((result.getResultCode() == -1) && (result.getData() != null)) {
                loadImageFromURI(result.getData().getData());
            }
        });
    }


    private void loadImageFromURI(Uri u) {
        try {
            InputStream input = requireActivity().getContentResolver().openInputStream(u);
            Bitmap bitmap = BitmapFactory.decodeStream(input);
            input.close();
            StorageManager.with(requireContext()).write(Constants.PROFILE_PIC, bitmapToString(bitmap));
            profilePic.setImageBitmap(bitmap);
        } catch (Exception e) {
            Log.d(_TAG, "Failed to open/close InputStream: " + e.getMessage());
        }
    }

    private String bitmapToString(Bitmap bitmap) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bitmap.compress(Bitmap.CompressFormat.PNG,100, baos);
        byte[] b = baos.toByteArray();
        return Base64.encodeToString(b, Base64.DEFAULT);
    }

    private Bitmap stringToBitmap(String s) {
        byte[] bytes = Base64.decode(s,Base64.DEFAULT);
        return BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
    }

    // Custom dialog used to show Authors info & Github links
    private void showDialog() {
        Log.d(_TAG, "Calling About Us dialog");
        final BottomSheetDialog dialog = new BottomSheetDialog(requireContext());
        dialog.setContentView(R.layout.about_us_modal);
        dialog.getBehavior().setMaxWidth(8000);
        dialog.findViewById(R.id.about_us_team_card_author_1_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/luftmensch-luftmensch/"))));
        dialog.findViewById(R.id.about_us_team_card_author_2_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/saltyDario/"))));
        dialog.findViewById(R.id.about_us_team_card_author_3_github_link).setOnClickListener(v -> startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("https://github.com/lbrando/"))));
        dialog.findViewById(R.id.about_us_report_bug).setOnClickListener(v -> {
            Intent intent = new Intent(Intent.ACTION_SENDTO);
            intent.setData(Uri.parse("mailto:"));
            intent.putExtra(Intent.EXTRA_EMAIL, "infopoint@info.com");
            requireActivity().startActivity(Intent.createChooser(intent, "Seleziona client di posta elettronica"));
        });
        dialog.show();
    }
}