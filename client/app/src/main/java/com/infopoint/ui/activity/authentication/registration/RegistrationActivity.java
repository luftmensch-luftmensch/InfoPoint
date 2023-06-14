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

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;

import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.textfield.TextInputEditText;
import com.google.android.material.textfield.TextInputLayout;
import com.infopoint.R;
public class RegistrationActivity extends AppCompatActivity {
    private final static String _TAG = "[RegistrationActivity] ";

    private TextInputLayout usernameTextInputLayout, passwordTextInputLayout, confirmPasswordTextInputLayout;

    private Button registrationButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.d(_TAG, "Starting Activity...");
        setContentView(R.layout.registration_activity);
        setUI();
    }

    @Override
    public void onBackPressed() {
        Log.d(_TAG, "Creating animation...");
        finish();
        overridePendingTransition(R.anim.slide_in_left, R.anim.slide_in_right);
    }

    private void setUI() {
        usernameTextInputLayout = findViewById(R.id.registration_username_text_input_layout);
        passwordTextInputLayout = findViewById(R.id.registration_password_text_input_layout);
        confirmPasswordTextInputLayout = findViewById(R.id.registration_confirm_password_text_input_layout);
    }
}