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
 * First written in 6/3/2023 at 15:18
*/

package com.infopoint.ui.authentication.scanner;

import android.view.View;
import android.widget.AdapterView;
import androidx.core.app.ActivityCompat.OnRequestPermissionsResultCallback;
import android.widget.AdapterView.OnItemSelectedListener;


import androidx.fragment.app.Fragment;

/**
 * Scanner ui interface for registration and retrieval of the info of a specific {@link com.infopoint.model.ArtWork ArtWork}
 * @author valentino
*/
public class BarCodeScannerFragment extends Fragment implements OnRequestPermissionsResultCallback, OnItemSelectedListener  {
    private static final String _TAG = "[BarCodeScannerFragment] ";

    private static final int PERMISSION_REQUESTS = 1;

    private static final String OBJECT_DETECTION = "Object Detection";
    private static final String OBJECT_DETECTION_CUSTOM = "Custom Object Detection (Bird)";
    private static final String FACE_DETECTION = "Face Detection";
    private static final String TEXT_RECOGNITION = "Text Recognition";
    private static final String BARCODE_SCANNING = "Barcode Scanning";
    private static final String IMAGE_LABELING = "Image Labeling";
    private static final String IMAGE_LABELING_CUSTOM = "Custom Image Labeling (Bird)";
    private static final String AUTOML_LABELING = "AutoML Image Labeling";
    private static final String POSE_DETECTION = "Pose Detection";

    private static final String STATE_SELECTED_MODEL = "selected_model";
    private static final String STATE_LENS_FACING = "lens_facing";

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {

    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }
}