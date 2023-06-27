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
 *   First written in 16/6/2023 at 12:9
 *
 */

package com.infopoint.ui.activity.intro;

/** Utility class representing the data of a single page inside the {@link IntroActivity} */
public class SlideItem {
    private final String title;
    private final int image;

    public SlideItem(String title, int image) {
        this.title = title;
        this.image = image;
    }

    public String getTitle() { return title; }

    public int getImage() { return image; }
}