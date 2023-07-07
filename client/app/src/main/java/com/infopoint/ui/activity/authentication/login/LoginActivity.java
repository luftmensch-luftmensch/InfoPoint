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
 *   First written in 14/6/2023 at 12:38
 *
 */

package com.infopoint.ui.activity.authentication.login;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputLayout;
import com.infopoint.R;
import com.infopoint.core.config.Constants;
import com.infopoint.core.networking.NetworkManager;
import com.infopoint.core.preferences.StorageManager;
import com.infopoint.core.validator.Validator;
import com.infopoint.ui.activity.MainActivity;
import com.infopoint.ui.activity.authentication.registration.RegistrationActivity;

import es.dmoral.toasty.Toasty;

/** Activity used to perform authentication operation [login] */
public class LoginActivity extends AppCompatActivity {
    private final static String _TAG = "[LoginActivity] ";
    private final static String _REQUEST_TYPE = "LOGIN";

    private TextInputLayout usernameTextInputLayout, passwordTextInputLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(_TAG, "Starting...");
        setContentView(R.layout.login_activity);

        Log.d(_TAG, "Checking internet connection...");
        if (!NetworkManager.checkConnection(this))
            Toasty.error(this, "Nessun connessione ad internet!\nRiprova più tardi", Toasty.LENGTH_LONG).show();

        StorageManager.with(this).write(Constants.FIRST_RUN, true);
        setUI();
    }

    private void setUI() {
        usernameTextInputLayout = findViewById(R.id.login_username_text_input_layout);
        passwordTextInputLayout = findViewById(R.id.login_password_text_input_layout);

        Button loginButton = findViewById(R.id.login_button);
        Button forgotPassword = findViewById(R.id.login_forgot_password_button);
        TextView loginToRegistrationTextView = findViewById(R.id.login_signup_text_view);

        loginToRegistrationTextView.setOnClickListener(click -> {
            Log.d(_TAG, "Moving to Registration");
            startActivity(new Intent(LoginActivity.this, RegistrationActivity.class));
            finishAffinity();
            overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
        });

        loginButton.setOnClickListener(view -> handleLogin(usernameTextInputLayout.getEditText().getText().toString(), passwordTextInputLayout.getEditText().getText().toString()));

        forgotPassword.setOnClickListener(view -> {
            Intent intent = new Intent(Intent.ACTION_SENDTO);
            intent.setData(Uri.parse("mailto:"));
            intent.putExtra(Intent.EXTRA_EMAIL, "infopoint@info.com");
            startActivity(Intent.createChooser(intent, "Seleziona client di posta elettronica"));
        });

    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(_TAG, "onResume: Checking internet connection");
        NetworkManager.checkConnection(this);
    }

    private void handleLogin(String username, String password) {
        if (!Validator.validate(username) || !Validator.validate(password)) {
            Toasty.error(this, "Attenzione!\nI campi inseriti non rispettano i requisiti richiesti!", Toasty.LENGTH_LONG).show();
            return;
        }

        Thread task = new Thread(() -> {
            if (NetworkManager.user_operation(_REQUEST_TYPE, username, password, "", this)) {
                Log.d(_TAG, "Successfull registration! Moving to HomePage...");
                startActivity(new Intent(LoginActivity.this, MainActivity.class));
                finishAffinity();
                overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
            } else {
                runOnUiThread(() -> Toasty.info(this, "Non sono state trovate buche nella zona intorno a te", Toast.LENGTH_LONG, true).show());
            }
        });

        task.setPriority(10);
        task.start();
    }
}