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
 * First written in 9/3/2023 at 7:23
*/

package com.infopoint.core.scanner;

/**
 * Describes a frame info
 * @author valentino
*/
public class FrameMetadata {
    private final int width;
    private final int height;
    private final int rotation;

    // Constructor
    private FrameMetadata(int width, int height, int rotation) {
        this.width = width;
        this.height = height;
        this.rotation = rotation;
    }

    public int getWidth() { return width; }
    public int getHeight() { return height; }
    public int getRotation() { return rotation; }

    /** Builder for {@link com.infopoint.core.scanner.FrameMetadata FrameMetadata} */
    public static class Builder {
        private int width;
        private int height;
        private int rotation;

        public Builder setWidth(int width) {
            this.width = width;
            return this;
        }

        public Builder setHeight(int height) {
            this.height = height;
            return this;
        }

        public Builder setRotation(int rotation) {
            this.rotation = rotation;
            return this;
        }

        public FrameMetadata build() {
            return new FrameMetadata(width, height, rotation);
        }

    }
}