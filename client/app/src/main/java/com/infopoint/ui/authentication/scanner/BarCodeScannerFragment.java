/*
 * Scritto da Valentino Bocchetti il 6/3/2023 alle ore 15:18
 *
 * Copyright © 2023 InfoPoint
*/

package com.infopoint.ui.authentication.scanner;

import android.view.View;
import android.widget.AdapterView;
import androidx.core.app.ActivityCompat.OnRequestPermissionsResultCallback;
import android.widget.AdapterView.OnItemSelectedListener;


import androidx.core.app.ActivityCompat;
import androidx.fragment.app.Fragment;

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