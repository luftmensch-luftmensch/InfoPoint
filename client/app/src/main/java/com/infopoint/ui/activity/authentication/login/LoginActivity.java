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

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;
import com.google.android.material.textfield.TextInputLayout;
import com.infopoint.R;
import com.infopoint.core.networking.NetworkManager;

public class LoginActivity extends AppCompatActivity {
    private final static String _TAG = "[LoginActivity] ";

    private TextInputLayout usernameTextInputLayout, passwordTextInputLayout;
    private TextInputEditText usernameEditText, passwordEditText;
    private CheckBox rememberMe;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(_TAG, "Starting...");
        setContentView(R.layout.login_activity);

        Log.d(_TAG, "Checking internet connection...");
        // TODO: Handle it
        NetworkManager.checkConnection(this);

        setUI();

    }

    private void setUI() {
        usernameTextInputLayout = findViewById(R.id.login_username_text_input_layout);
        passwordTextInputLayout = findViewById(R.id.login_password_text_input_layout);

        Button loginButton = findViewById(R.id.login_button);
        Button forgotPassword = findViewById(R.id.login_forgot_password_button);
        TextView registrationTextView = findViewById(R.id.login_signup_text_view);




        // TODO: Add Login logic
        loginButton.setOnClickListener(view -> {

        });

        // TODO: Add forgotPassword logic
        forgotPassword.setOnClickListener(view -> {

        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(_TAG, "onResume: Checking internet connection");

        NetworkManager.checkConnection(this);
    }
}