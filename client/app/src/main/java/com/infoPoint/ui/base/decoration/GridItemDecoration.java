/*
 * Scritto da Valentino Bocchetti il 27/2/2023 alle ore 14:8
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.ui.base.decoration;

import android.graphics.Rect;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

public class GridItemDecoration extends RecyclerView.ItemDecoration {
    private Integer spanCount, spacing;
    private Boolean includeEdges;

    public GridItemDecoration(Integer spanCount, Integer spacing, Boolean includeEdges) {
        this.spanCount = spanCount;
        this.spacing = spacing;
        this.includeEdges = includeEdges;
    }

    @Override
    public void getItemOffsets(@NonNull Rect outRect, @NonNull View view,
                               @NonNull RecyclerView parent, @NonNull RecyclerView.State state){
        Integer position = parent.getChildAdapterPosition(view);
        Integer column = position % spanCount;
        if (includeEdges) {
            outRect.left = spacing - column * spacing / spanCount;
            outRect.right = (column + 1) * spacing / spanCount;

            if (position < spanCount) {
                outRect.top = spacing;
            }
            outRect.bottom = spacing;
        } else {
            outRect.left = column * spacing / spanCount;
            outRect.right = spacing - (column + 1) * spacing / spanCount;
            if (position >= spanCount) {
                outRect.top = spacing;
            }

        }

    }
}