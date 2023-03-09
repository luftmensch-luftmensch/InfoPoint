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
 * First written in 2/3/2023 at 12:05
*/

package com.infopoint.ui.base.decoration;

import android.graphics.Rect;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

/**
 * Decoration utility for Grid
 * @author valentino
*/
public class GridItemDecoration extends RecyclerView.ItemDecoration {
    private final Integer spanCount, spacing;
    private final Boolean includeEdges;

    public GridItemDecoration(Integer spanCount, Integer spacing, Boolean includeEdges) {
        this.spanCount = spanCount;
        this.spacing = spacing;
        this.includeEdges = includeEdges;
    }

    @Override
    public void getItemOffsets(@NonNull Rect outRect, @NonNull View view,
                               @NonNull RecyclerView parent, @NonNull RecyclerView.State state){
        Integer position = parent.getChildAdapterPosition(view);
        int column = position % spanCount;
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
