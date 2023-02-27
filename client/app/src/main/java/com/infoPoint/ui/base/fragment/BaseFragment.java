/*
 * Scritto da Valentino Bocchetti il 27/2/2023 alle ore 14:8
 *
 * Copyright © 2023 InfoPoint
 */

package com.infoPoint.ui.base.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModel;
import androidx.viewbinding.ViewBinding;

/**
 * This class extending {@link Fragment Fragment} provides basic functionality
 * for Fragments which extends it
*/
public abstract class BaseFragment<VB extends ViewBinding, VM extends ViewModel> extends Fragment {
    /** This property serves as ViewModel generalization */
    protected VM viewModel;
    /** This property is valid only until onDestroyView is called */
    protected VB viewBinding;

    @NonNull
    protected abstract VM createViewModel();

    @NonNull
    protected abstract VB createViewBinding();

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState){
        viewBinding = createViewBinding();
        viewModel = createViewModel();
        return viewBinding.getRoot();
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

    public void onDestroyView(){
        super.onDestroyView();
        viewBinding = null; // Help the gc
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