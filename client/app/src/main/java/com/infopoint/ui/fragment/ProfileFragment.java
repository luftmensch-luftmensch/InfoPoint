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
import android.widget.TextView;
import android.widget.Toast;

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
import com.infopoint.core.networking.NetworkManager;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.ui.activity.MainActivity;
import com.infopoint.ui.activity.authentication.login.LoginActivity;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;

import es.dmoral.toasty.Toasty;

/** Fragment used to show info about the current user logged */
public class ProfileFragment extends Fragment {
    private final static String _TAG = "[ProfileFragment] ";
    private final String _REQUEST_TYPE = "DELETE";

    private ActivityResultLauncher<Intent> selectImageLauncher;
    private ShapeableImageView profilePic;
    private Chip userLevel;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle bundle) {
        Log.d(_TAG, "onCreateView: Starting...");
        return inflater.inflate(R.layout.profile_fragment, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle bundle) {
        super.onViewCreated(view, bundle);

        userLevel = view.findViewById(R.id.profile_fragment_user_level);

        Chip retrieveToken = view.findViewById(R.id.profile_fragment_retrieve_token);
        retrieveToken.setOnClickListener(click -> showTokenDialog(StorageManager.with(requireContext()).read(Constants.TOKEN, "")));

        Chip deleteUser = view.findViewById(R.id.profile_fragment_delete_user);
        deleteUser.setOnClickListener(click -> deleteAccountDialog(
                StorageManager.with(requireContext()).read(Constants.USERNAME, ""),
                StorageManager.with(requireContext()).read(Constants.PASSWORD, ""),
                StorageManager.with(requireContext()).read(Constants.USERNAME, ""),
                requireContext()
        ));


        if (StorageManager.with(requireContext()).read(Constants.LEVEL, "").equals("")) {
            userLevel.setText(R.string.edit_user_level);
        } else {
            userLevel.setText(StorageManager.with(requireContext()).read(Constants.LEVEL, ""));
        }
        userLevel.setOnClickListener(click -> showUserLevelDialog());

        MaterialToolbar toolbar = view.findViewById(R.id.top_app_bar_profile);

        toolbar.setOnMenuItemClickListener(item -> {
            if (item.getItemId() == R.id.menu_item_info) {
                showAboutUsDialog();
            } else if (item.getItemId() == R.id.menu_item_exit) {
                new MaterialAlertDialogBuilder(requireContext())
                        .setTitle(R.string.confirm_logout)
                        .setMessage(R.string.confirm_logout_body)
                        .setPositiveButton(R.string.confirm_request, (dialogInterface, i) -> {
                            Log.d(_TAG, "Logout request confirmed");
                            StorageManager.with(requireContext()).clear();
                            MainActivity main = (MainActivity) requireActivity();
                            main.navController.navigate(R.id.nav_logout);
                        })
                        .setNegativeButton(R.string.cancel_request, (dialogInterface, i) -> Log.d(_TAG, "Logout request cancelled"))
                        .show();
            } else {
                Log.d(_TAG, "Unknown item clicked");
            }

            return false;
        });

        profilePic = view.findViewById(R.id.profile_fragment_profile_photo);
        TextView username = view.findViewById(R.id.profile_fragment_username_text_view);
        username.setText(StorageManager.with(requireContext()).read(Constants.USERNAME, ""));

        ShapeableImageView selectImage = view.findViewById(R.id.profile_fragment_change_photo);

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
    private void showAboutUsDialog() {
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

    private void showUserLevelDialog() {
        Log.d(_TAG, "Calling User Level dialog");
        final MaterialAlertDialogBuilder builder = new MaterialAlertDialogBuilder(requireContext());
        builder
                .setTitle(R.string.edit_user_level)
                .setItems(R.array.user_level_options, (dialog, which) -> {
                    String[] value = this.getResources().getStringArray(R.array.user_level_options);
                    StorageManager.with(requireContext()).write(Constants.LEVEL, value[which]);
                    userLevel.setText(value[which]);
                })
                .setNegativeButton(R.string.cancel_request, (dialogInterface, i) -> Log.d(_TAG, "Logout request cancelled"))
                .create();
        builder.show();
    }

    private void showTokenDialog(String token) {
        Log.d(_TAG, "Calling Token dialog");
        final MaterialAlertDialogBuilder builder = new MaterialAlertDialogBuilder(requireContext(), R.style.MaterialAlertDialog__Center);
        builder
                .setTitle(R.string.token_showed)
                .setMessage(getString(R.string.show_token, token))
                .setPositiveButton(R.string.confirm_request, (dialogInterface, i) -> Log.d(_TAG, "Hide token showed"))
                .create();
        builder.show();

    }

    private void deleteAccountDialog(String username, String password, String token, Context ctx) {
        Log.d(_TAG, "Calling Delete Account dialog");

        final MaterialAlertDialogBuilder builder = new MaterialAlertDialogBuilder(requireContext(), R.style.MaterialAlertDialog__Center);
        builder
                .setTitle(R.string.confirm_delete_account)
                .setMessage(R.string.confirm_delete_account_body)
                .setPositiveButton(R.string.confirm_request, (dialogInterface, i) -> {
                    Log.d(_TAG, "Logout request confirmed");

                    Thread task = new Thread(() -> {
                        if (NetworkManager.user_operation(_REQUEST_TYPE, username, password, token, ctx)) {
                            Log.d(_TAG, "Successfull delete! Moving to Login...");
                            StorageManager.with(requireContext()).clear();
                            startActivity(new Intent(requireActivity(), LoginActivity.class).addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP));
                        } else {
                            requireActivity().runOnUiThread(() ->
                                    Toasty.info(requireContext(), "Attenzione! Non siamo riusciti a soddisfare la richiesta\nRiprova più tardi",
                                            Toast.LENGTH_LONG, true).show());
                        }
                    });
                    task.setPriority(10);
                    task.start();
                })
                .setNegativeButton(R.string.cancel_request, (dialogInterface, i) -> Toasty.info(requireContext(), "Siamo contenti che ci hai ripensato!", Toast.LENGTH_SHORT, true).show())
                .create();
        builder.show();
    }
}