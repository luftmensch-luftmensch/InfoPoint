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
 *   First written in 4/7/2023 at 17:18
 *
 */

package com.infopoint.core.validator;

public class Validator {

    public static Boolean validate(String s) {
        if (s.trim().length() == 0) {
            return false;
        } else if (!s.trim().matches("^[a-zA-Z0-9]+[_@#]?[a-zA-Z0-9]+$")) {
            return false;
        } else if ((s.trim().length() < 8) || (s.trim().length() > 15) || s.trim().contains(" ")) {
            return false;
        }

        return true;
    }
}