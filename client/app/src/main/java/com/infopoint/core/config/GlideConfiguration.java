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
 *   First written in 13/6/2023 at 21:34
 *
*/

package com.infopoint.core.config;

import android.content.Context;

import androidx.annotation.NonNull;

import com.bumptech.glide.GlideBuilder;
import com.bumptech.glide.load.engine.cache.LruResourceCache;
import com.bumptech.glide.load.engine.cache.MemorySizeCalculator;
import com.bumptech.glide.module.AppGlideModule;

/** Glide configuration */
public class GlideConfiguration extends AppGlideModule {
    /*
        By default, Glide uses LruResourceCache, a default implementation of the MemoryCache interface that uses a fixed amount of memory with LRU eviction.
        The size of the LruResourceCache is determined by Glide’s MemorySizeCalculator class, which looks at the device memory class,
        whether or not the device is low ram and the screen resolution. Applications can customize the MemoryCache size in their AppGlideModule
        with the applyOptions(Context, GlideBuilder) method by configuring MemorySizeCalculator
    */
    @Override
    public void applyOptions(@NonNull Context context, GlideBuilder builder) {
        MemorySizeCalculator calculator = new MemorySizeCalculator.Builder(context)
                .setMemoryCacheScreens(2)
                .build();
        builder.setMemoryCache(new LruResourceCache(calculator.getMemoryCacheSize()));
    }
}