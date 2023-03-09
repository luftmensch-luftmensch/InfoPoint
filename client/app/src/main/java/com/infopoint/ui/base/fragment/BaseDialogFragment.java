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
 * First written in 2/3/2023 at 12:06
*/

package com.infopoint.ui.base.fragment;

import androidx.appcompat.app.AlertDialog;
import android.app.Dialog;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.DialogFragment;
import androidx.lifecycle.ViewModel;
import androidx.viewbinding.ViewBinding;

import com.google.android.material.dialog.MaterialAlertDialogBuilder;

/**
 * This class extending {@link DialogFragment DialogFragment} provides basic functionality
 * for Fragments which extends it
 * @author valentino
*/
public abstract class BaseDialogFragment<VB extends ViewBinding, VM extends ViewModel> extends DialogFragment {

    /** This property serves as ViewModel generalization */
    protected VM viewModel;
    /** This property is valid only until onDestroyView is called */
    protected VB viewBinding;

    @NonNull
    protected abstract VM createViewModel();

    @NonNull
    protected abstract VB createViewBinding();

    protected Boolean shouldSetCustomView = false;

    protected Integer baseTitle;
    protected abstract Integer getDialogTitle();

    protected Integer baseMessage;
    protected abstract Integer getDialogMessage();

    protected Integer baseIcon;
    protected abstract Integer getDialogIcon();

    protected Integer basePositive;
    protected abstract Integer getDialogPositive();

    protected Integer baseNegative;
    protected abstract Integer getDialogNegative();

    public void init(){
        viewBinding = createViewBinding();
        viewModel = createViewModel();
        baseTitle = getDialogTitle();
        baseIcon = getDialogIcon();
        baseMessage = getDialogMessage();
        basePositive = getDialogPositive();
        baseNegative = getDialogNegative();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState){
        return viewBinding.getRoot();
    }

    public void onDestroyView(){
        super.onDestroyView();
        viewBinding = null; // Help the gc
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState){
        super.onViewCreated(view, savedInstanceState);
        setupUi();
        setupListeners();
        setTextChangedListeners();
        initRecycler();
        collectState();
    }

    @NonNull
    public Dialog onCreateDialog(@Nullable Bundle savedInstanceState){
        init();
        AlertDialog dialog = initDialog();
        return dialog;
    }

    public AlertDialog initDialog(){
        MaterialAlertDialogBuilder baseDialog = new MaterialAlertDialogBuilder(requireContext())
                .setTitle(baseTitle)
                .setMessage(baseMessage)
                .setCancelable(false);
        if (shouldSetCustomView) baseDialog.setView(viewBinding.getRoot());
        // TODO: add Icon & Buttons
        return baseDialog.create();
    }

    /** This function setups every View */
    public void setupUi(){ }

    /**  This function sets any kind of listener */
    public void setupListeners(){ }

    /** This function sets any kind of text listener */
    public void setTextChangedListeners(){ }

    /** This function initialize any recycler view */
    public void initRecycler(){ }

    /** This function serves as a way to collect states from ViewModel */
    public void collectState(){ }

}
