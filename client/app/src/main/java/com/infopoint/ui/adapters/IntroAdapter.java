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
 *   First written in 16/6/2023 at 12:09
 *
*/

package com.infopoint.ui.adapters;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.PagerAdapter;

import com.infopoint.R;
import com.infopoint.ui.activity.intro.IntroActivity;
import com.infopoint.ui.activity.intro.SlideItem;

import java.util.List;

/** Helper Adapter Class used for the {@link IntroActivity} */
public class IntroAdapter extends PagerAdapter {
    private final Context context;
    private final List<SlideItem> items;
    public IntroAdapter(Context ctx, List<SlideItem> slides) {
        context = ctx;
        items = slides;
    }

    @NonNull
    @Override
    public Object instantiateItem(@NonNull ViewGroup container, int position) {
        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View view = inflater.inflate(R.layout.intro_page_layout, container, false);

        ImageView image = view.findViewById(R.id.intro_slide_item_image);
        TextView title = view.findViewById(R.id.intro_slide_item_title);

        title.setText(items.get(position).getTitle());
        image.setImageResource(items.get(position).getImage());

        container.addView(view);

        return view;
    }

    @Override
    public int getCount() { return items.size(); }
    @Override
    public boolean isViewFromObject(@NonNull View view, @NonNull Object object) { return view == object; }
    @Override
    public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) { container.removeView((View) object); }
}