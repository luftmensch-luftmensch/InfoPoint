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

package com.infopoint.ui.activity.authentication.registration;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputLayout;
import com.infopoint.R;
import com.infopoint.core.networking.NetworkManager;
import com.infopoint.core.validator.Validator;
import com.infopoint.ui.activity.MainActivity;
import com.infopoint.ui.activity.authentication.login.LoginActivity;

import es.dmoral.toasty.Toasty;

/** Activity used to perform authentication operation [registration] */
public class RegistrationActivity extends AppCompatActivity {
    private final static String _TAG = "[RegistrationActivity] ";

    private final static String _REQUEST_TYPE = "REGISTRATION";

    private TextInputLayout usernameTextInputLayout, passwordTextInputLayout, confirmPasswordTextInputLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(_TAG, "Starting Activity...");
        setContentView(R.layout.registration_activity);

        Log.d(_TAG, "Checking internet connection...");
        if (!NetworkManager.checkConnection(this))
            Toasty.error(this, "Nessun connessione ad internet!\nRiprova più tardi", Toasty.LENGTH_LONG).show();
        setUI();
    }

    private void setUI() {
        usernameTextInputLayout = findViewById(R.id.registration_username_text_input_layout);
        passwordTextInputLayout = findViewById(R.id.registration_password_text_input_layout);
        confirmPasswordTextInputLayout = findViewById(R.id.registration_confirm_password_text_input_layout);

        TextView registrationToLoginTextView = findViewById(R.id.signup_login_text_view);


        registrationToLoginTextView.setOnClickListener(click -> {
            Log.d(_TAG, "Moving to Login");
            startActivity(new Intent(RegistrationActivity.this, LoginActivity.class));
            finishAffinity();
            overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
        });

        findViewById(R.id.registration_button).setOnClickListener(click -> handleRegistration(
                usernameTextInputLayout.getEditText().getText().toString(),
                passwordTextInputLayout.getEditText().getText().toString(),
                confirmPasswordTextInputLayout.getEditText().getText().toString()
        ));
    }

    @Override
    public void onBackPressed() {
        Log.d(_TAG, "Creating animation...");
        finish();
        overridePendingTransition(R.anim.slide_in_left, R.anim.slide_in_right);
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(_TAG, "onResume: Checking internet connection");
        NetworkManager.checkConnection(this);
    }

    private void handleRegistration(String username, String password, String confirmPassword) {
        if (!Validator.validate(username) || !Validator.validate(password)) {
            Toasty.error(this, "Attenzione!\nI campi inseriti non rispettano i requisiti richiesti!", Toasty.LENGTH_LONG).show();
            return;
        }

        if (!password.equals(confirmPassword)) {
            Toasty.error(this, "Attenzione!\nLe password inserite non corrispondono!", Toasty.LENGTH_LONG).show();
            return;
        }

        Thread task = new Thread(() -> {
            if (NetworkManager.user_operation(_REQUEST_TYPE, username, password, "dummy_token", this)) {
                Log.d(_TAG, "Successfull registration! Moving to HomePage...");
                startActivity(new Intent(RegistrationActivity.this, MainActivity.class));
                finishAffinity();
                overridePendingTransition(R.anim.slide_in_left, R.anim.slide_out_right);
            } else {
                runOnUiThread(() -> Toasty.error(this, "Attenzione! L'username selezionato è già esistente!", Toast.LENGTH_LONG, true).show());
            }
        });

        // The higher the better
        task.setPriority(10);
        task.start();

    }
}