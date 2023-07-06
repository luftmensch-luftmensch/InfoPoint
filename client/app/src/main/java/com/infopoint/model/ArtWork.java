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

/** Model representing artwork properties */
public class ArtWork {
    private String name;
    private String author;
    private String description;

    public ArtWork(String name, String author, String description) {
        this.name = name;
        this.author = author;
        this.description = description;
    }

    public String getName() { return name; }
    public String getAuthor() { return author; }
    public String getDescription() { return description; }
    public void setName(String name) { this.name = name; }
    public void setAuthor(String author) { this.author = author; }
    public void setDescription(String description) { this.description = description; }

    @NonNull
    @Override
    public String toString() {
        return "ArtWork{" +
                "name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", description='" + description + '\'' +
                '}';
    }
}