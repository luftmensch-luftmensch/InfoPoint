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
 *   First written in 13/6/2023 at 20:59
 *
 */

package com.infopoint.model;

import androidx.annotation.NonNull;

/** Model representing user properties */
public class User {
    private String id;
    private String name;
    private String password;

    @NonNull
    @Override
    public String toString() {
        return "User{" +
                "id='" + id + '\'' +
                ", name='" + name + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    public String validateName(String name) {
        if (name.trim().length() == 0) {
            return "Name cannot be empty";
        } else if (name.trim().matches("^[0-9]+$")) {
            return "Name cannot have numbers in it";
        } else if (!name.trim().matches("^[a-zA-Z][a-zA-Z ]++$")) {
            return "Invalid Name";
        }
        return null;
    }

    public String validatePassword(String password, String confirmPassword) {
        if (password.trim().length() == 0) {
            return "Passwords cannot be empty";
        } else if (confirmPassword.trim().length() == 0) {
            return "Passwords cannot be empty";
        } else if (!confirmPassword.trim().matches(password.trim())) {
            return "Passwords do not match";
        } else if (password.trim().length() < 8) {
            return "Password too small. Minimum length is 8";
        } else if (password.trim().length() > 15) {
            return "Password too long. Maximum length is 15";
        } else if (password.trim().contains(" ")) {
            return "Password cannot contain spaces";
        } else if (!(password.trim().contains("@") || password.trim().contains("#")) || password.trim().contains("$") || password.trim().contains("%") || password.trim().contains("*") || password.trim().contains(".") || password.trim().matches("(((?=.*[a-z])(?=.*[A-Z]))|((?=.*[a-z])(?=.*[0-9]))|((?=.*[A-Z])(?=.*[0-9])))")) {
            return "Password should contain atleast one uppercase character or one number or any of the special characters from (@, #, $, %, *, .)";
        }
        return null;
    }
}
