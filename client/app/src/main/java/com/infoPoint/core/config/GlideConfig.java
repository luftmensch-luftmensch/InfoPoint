/*
 * Scritto da Valentino Bocchetti il 26/2/2023 alle ore 23:30
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.core.config;

import android.content.Context;

import androidx.annotation.NonNull;

import com.bumptech.glide.GlideBuilder;
import com.bumptech.glide.annotation.GlideModule;
import com.bumptech.glide.load.engine.cache.LruResourceCache;
import com.bumptech.glide.load.engine.cache.MemorySizeCalculator;
import com.bumptech.glide.module.AppGlideModule;

@GlideModule
public class GlideConfig extends AppGlideModule {
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
        builder
                .setMemoryCache(new LruResourceCache(calculator.getMemoryCacheSize()));

    }
}